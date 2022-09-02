#include "CreateJountion.h"
#include <QDebug>
#include "netinterface.h"
#include "TessInterfaces.h"
#include "CreateLink.h"
#include "PrograssDlgForFloat.h"



CreateJountion::CreateJountion()
{

}


CreateJountion* CreateJountion::getInstance()
{
    static CreateJountion connector;
    return &connector;
}

void CreateJountion::reset()
{
    m_mapConnData.clear();
}

void CreateJountion::appendConnectData(int roadId , std::shared_ptr<JounctionRoad> ptr)
{
    m_mapConnData[roadId] = ptr;
}
void CreateJountion::paint(PrograssDlgForFloat* ptrProDlg)
{
    ptrProDlg->setInfo("阶段4,创建交叉口:", m_mapConnData.size());
    for (auto it : m_mapConnData) {
        it->paint2();
        ptrProDlg->addPrescent(1);
    }
}
void JounctionRoad::appendCenterPoint(const QPolygonF& pts)
{
    for (auto& it : pts) {
        m_centerLine.append(QVector3D(it.x() - CreateLink::g_ScenceCenterPt.x(), it.y() - CreateLink::g_ScenceCenterPt.y(), 0.0f));
    }
}
void JounctionRoad::appendLanePoints(const ConnectorItem& item, int laneId, const QMap<QString, QList<QVector3D>>& points) {
    if (!lanePtsHash.contains(item)) {
        lanePtsHash[item][laneId] = points;
        return;
    }
    if (!lanePtsHash[item].contains(laneId)) {
        lanePtsHash[item][laneId] = points;
        return;
    }
    lanePtsHash[item][laneId]["left" ]<< points["left"];
    lanePtsHash[item][laneId]["center"] << points["center"];
    lanePtsHash[item][laneId]["right"] << points["right"];
}
void JounctionRoad::createAreaSub(const QList<int>&, const QList<QVector3D>& centerPoints, 
    const QList<QMap<QString, QList<QVector3D>>>& lanesWithPointsForRight, int) {

    ILink* linker = gpTessInterface->netInterface()->createLink3DWithLanePoints(centerPoints, lanesWithPointsForRight);
    if (nullptr == linker) return;
    QList<ILane*> lanes = linker->lanes();
    for (int i = 0; i < lanes.size(); i++) {
        //CreateLink::getInstance()->appendLinkerData(roadId, laneIds[i], QPair<int, int>(linker->id(), lanes[i]->number() + 1));
    }
}
void JounctionRoad::createArea(const QList<int>& leftLaneIds, const QList<int>& rightLaneIds,
    const QList<QVector3D>& listCenter, const QList<QMap<QString, QList<QVector3D>>>& ptsLeft,
    const QList<QMap<QString, QList<QVector3D>>>& ptsRight, int roadId) {

    createAreaSub(rightLaneIds, listCenter, ptsRight, roadId);
    QList<QVector3D> listCenterTemp = listCenter;
    QList<int> leftIds = leftLaneIds;
    QList<QMap<QString, QList<QVector3D>>> listPts = ptsLeft;
    if (CreateLink::g_isReverse) {
        std::reverse(listCenterTemp.begin(), listCenterTemp.end());
        std::reverse(leftIds.begin(), leftIds.end());
        std::reverse(listPts.begin(), listPts.end());
    }
    createAreaSub(leftIds, listCenterTemp, listPts, roadId);
}

void JounctionRoad::createLinkerConnector(QList<ConnectorItem>& linkerConnect) {
    for (auto& item : linkerConnect) {
        if (CreateLink::g_isReverse) {
            CreateLink::getInstance()->checkConnectorItem(item);
        }
        else {

        }
        if (!CreateLink::getInstance()->getTessngConnectorData(item.from, item.fromLaneId,true)) continue;
        if (!CreateLink::getInstance()->getTessngConnectorData(item.to, item.toLaneId,false)) continue;

        if (CreateLink::getInstance()->checkHasPatined(item)) continue;
        QList<int> lFromLaneNumber, lToLaneNumber;
        lFromLaneNumber << item.fromLaneId; lToLaneNumber << item.toLaneId;

        gpTessInterface->netInterface()->createConnector(item.from, item.to, lFromLaneNumber, lToLaneNumber);
    }
}

void JounctionRoad::createJounctionConnector(QList<ConnectorItem>& linkerConnect, const QList<QMap<QString, QList<QVector3D>>>& map) {
    for (int i = 0; i < linkerConnect.size(); i++) {
        auto item = linkerConnect.at(i);
        QList<QMap<QString, QList<QVector3D>>> list;
        list.append(map.at(i));

        if (CreateLink::g_isReverse) {
            CreateLink::getInstance()->checkConnectorItem(item);
        }
        else {

        }
        if (!CreateLink::getInstance()->getTessngConnectorData(item.from, item.fromLaneId,true)) continue;
        if (!CreateLink::getInstance()->getTessngConnectorData(item.to, item.toLaneId,false)) continue;

        if (CreateLink::getInstance()->checkHasPatined(item)) continue;
        QList<int> lFromLaneNumber, lToLaneNumber;
        lFromLaneNumber << item.fromLaneId; lToLaneNumber << item.toLaneId;

        gpTessInterface->netInterface()->createConnector3DWithPoints(item.from, item.to, lFromLaneNumber, lToLaneNumber, list);
    }
}
void JounctionRoad::paint()
{
    QList<QMap<QString, QList<QVector3D>>> fist3PtsLeft, fist3PtsRight,last3PtsLeft, last3PtsRight, linkerConnectMap;
    QList<QVector3D> listCenterFirst, listCenterLast;
    QList<ConnectorItem> linkerConnectFirst, linkerConnectLast, linkerConnect;
    QList<int> leftLaneIds, rightLaneIds;
    const int ptN = 3;
    int M;

    int genRoadIdFirst = CreateLink::getInstance()->createRoadId();
    int genRoadIdLast = CreateLink::getInstance()->createRoadId();
    auto it = lanePtsHash.begin();
    for (; it != lanePtsHash.end(); ++it) {
        auto laneIt = it.value().begin();
        ConnectorItem item = it.key();
        for (; laneIt != it.value().end(); ++laneIt) {
            
            QMap<QString, QList<QVector3D>>& mapPts = laneIt.value();
            int laneId = laneIt.key();
            if (mapPts["left"].size() < 7) {
                continue;
            }
            
            ///保存前后3个点作为新的的 link 路段
            QMap<QString, QList<QVector3D>> first3, last3;
            first3["left"] = mapPts["left"].mid(0, ptN);
            first3["center"] = mapPts["center"].mid(0, ptN);
            first3["right"] = mapPts["right"].mid(0, ptN);


            last3["left"] = mapPts["left"].mid(mapPts["left"].size() - ptN, ptN);
            last3["center"] = mapPts["center"].mid(mapPts["center"].size() - ptN, ptN);
            last3["right"] = mapPts["right"].mid(mapPts["right"].size() - ptN, ptN);

            listCenterFirst = m_centerLine.mid(0, ptN);
            listCenterLast=m_centerLine.mid(m_centerLine.size() - ptN, ptN);
            M = ptN;
            while (M-->0)
            {
                mapPts["left"].takeFirst();
                mapPts["center"].takeFirst();
                mapPts["right"].takeFirst();

                mapPts["left"].takeLast();
                mapPts["center"].takeLast();
                mapPts["right"].takeLast();
            }


            if (laneId > 0) {
                fist3PtsLeft.append(first3);
                last3PtsLeft.append(last3);
                leftLaneIds.append(laneId);
            }
            else {
                fist3PtsRight.append(first3);
                last3PtsRight.append(last3);
                rightLaneIds.append(laneId);
            }

            ConnectorItem first;
            first.from = item.from;
            first.contactPointFrom = item.contactPointFrom;
            first.fromLaneId = item.fromLaneId;
            first.to = genRoadIdFirst;
            first.toLaneId = laneId;
            if (laneId > 0 && CreateLink::g_isReverse) {
                first.contactPointTo = "end";
            }
            else {
                first.contactPointTo = "start";
            }
            
            linkerConnectFirst.append(first);

            ConnectorItem last;
            last.from = genRoadIdLast;
            last.fromLaneId = laneId;
            if (laneId > 0 && CreateLink::g_isReverse) {
                last.contactPointFrom = "start";
            }
            else {
                last.contactPointFrom = "end";
            }
            
            last.to = item.to;
            last.toLaneId = item.toLaneId;
            last.contactPointTo = item.contactPointTo;
            linkerConnectLast.append(last);


            ConnectorItem lkConn;
            lkConn.from = genRoadIdFirst;
            lkConn.to = genRoadIdLast;
            if (laneId > 0 && CreateLink::g_isReverse) {
                lkConn.contactPointFrom = "start";
                lkConn.contactPointTo = "end";
            }
            else {
                lkConn.contactPointFrom = "end";
                lkConn.contactPointTo = "start";
            }
           
            lkConn.fromLaneId = laneId;
            lkConn.toLaneId = laneId;
            linkerConnect.append(lkConn);
            linkerConnectMap.append(mapPts);

        }
    }
    createArea(leftLaneIds, rightLaneIds, listCenterFirst, fist3PtsLeft, fist3PtsRight, genRoadIdFirst);
    createArea(leftLaneIds, rightLaneIds, listCenterLast, last3PtsLeft, last3PtsRight, genRoadIdLast);

    //createLinkerConnector(linkerConnectFirst);
    //createLinkerConnector(linkerConnectLast);

    createJounctionConnector(linkerConnect, linkerConnectMap);
}

void JounctionRoad::paint2() {
    auto it = lanePtsHash.begin();
    for (; it != lanePtsHash.end(); ++it) {
        auto laneIt = it.value().begin();
        ConnectorItem item = it.key();
        QList<QMap<QString, QList<QVector3D>>> list;
        for (; laneIt != it.value().end(); ++laneIt) {
            if (list.empty()) {
                list.append(laneIt.value());
                continue;
            }
            if (list[0]["center"].size() < laneIt.value()["center"].size()) {
                list[0] = laneIt.value();
            }
        }
        if (list.size() == 0) continue;
        
        if (CreateLink::g_isReverse) {
            if (!CreateLink::getInstance()->checkConnectorItem(item)) continue;
        }
        if (!CreateLink::getInstance()->getTessngConnectorData(item.from, item.fromLaneId,true)) continue;
        if (!CreateLink::getInstance()->getTessngConnectorData(item.to, item.toLaneId,false)) continue;

        if (CreateLink::getInstance()->checkHasPatined(item)) continue;
        QList<int> lFromLaneNumber, lToLaneNumber;
        lFromLaneNumber << item.fromLaneId; lToLaneNumber << item.toLaneId;
        gpTessInterface->netInterface()->createConnector3DWithPoints(item.from, item.to, lFromLaneNumber, lToLaneNumber, list);
        //gpTessInterface->netInterface()->createConnector(item.from, item.to, lFromLaneNumber, lToLaneNumber);
    }
}