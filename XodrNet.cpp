#include "XodrNet.h"
#include "Plugin/_netitem.h"
#include "Plugin/_netitemtype.h"
#include "MapInfo.h"
#include <QVector3D>
#include <qmath.h>
#include <QDebug>
#include "netinterface.h"
#include "PrograssDlgForFloat.h"
#include "CreateJountion.h"
#include "guiinterface.h"
#include <QApplication>
#include <QTextCodec>
XodrNet::XodrNet() {
	m_showAll = false;
}

void XodrNet::beforeLoadNet()
{
}

void XodrNet::afterLoadNet()
{
}
void XodrNet::setShowAll(bool flag) {
	m_showAll = flag;
}
void XodrNet::labelNameAndFont(int itemType, long itemId, int& outPropName, qreal& outFontSize)
{
	outPropName = GraphicsItemPropName::Id;
	outFontSize = 6;
	if (itemType == NetItemType::GConnectorType) {
		outPropName = GraphicsItemPropName::Name;
	}
	else if (itemType == NetItemType::GLinkType) {
		if (itemId == 1 || itemId == 5 || itemId == 6) {
			outPropName = GraphicsItemPropName::Name;
		}
	}
}
void XodrNet::setNetAttrs(t_header* header, const QString& sourcePath) {
	if (nullptr == header) return;
	QJsonObject obj;
	{
		obj.insert("date", header->date.c_str());
		obj.insert("east", header->east);
		obj.insert("name", header->name.c_str());
		obj.insert("north", header->north);
		obj.insert("revMajor", header->revMajor);
		obj.insert("south", header->south);
		obj.insert("vendor", header->vendor.c_str());
		obj.insert("version", header->version.c_str());
		obj.insert("west", header->west);
	}

	gpTessInterface->netInterface()->setNetAttrs(header->name.c_str(), "OpenDriver", CreateLink::g_ScenceCenterPt,
		sourcePath, obj);
}
int XodrNet::getLaneIdFromSection(int sectionIndex, SectionLane& sectionLane) {
	if (sectionLane.empty()) return 0;
	if (nullptr != dynamic_cast<t_road_lanes_laneSection_left_lane*>(sectionLane[sectionIndex].get()))
		return  dynamic_cast<t_road_lanes_laneSection_left_lane*>(sectionLane[sectionIndex].get())->id;

	else if (nullptr != dynamic_cast<t_road_lanes_laneSection_center_lane*>(sectionLane[sectionIndex].get()))
		return dynamic_cast<t_road_lanes_laneSection_center_lane*>(sectionLane[sectionIndex].get())->id;

	else if (nullptr != dynamic_cast<t_road_lanes_laneSection_right_lane*>(sectionLane[sectionIndex].get()))
		return dynamic_cast<t_road_lanes_laneSection_right_lane*>(sectionLane[sectionIndex].get())->id;
	return 0;

}

void XodrNet::transferLanesList(const std::vector<std::shared_ptr<t_road> >& vecAllRoad, RoadMapLane& roadMapLane)
{
	for (auto& eachRoad : vecAllRoad)
	{
		RoadLane roadLane;

		for (auto& eachlaneSection : eachRoad->m_lanes->m_laneSections)
		{
			SectionLane sectionLane;

			if (eachlaneSection->m_left)
			{
				for (auto& eachLane : eachlaneSection->m_left->m_lanes)
				{
					sectionLane.append(std::shared_ptr<t_road_lanes_laneSection_lr_lane>(eachLane));
				}
			}

			if (eachlaneSection->m_center)
			{
				for (auto& eachLane : eachlaneSection->m_center->m_lanes)
				{
					sectionLane.append(std::shared_ptr<t_road_lanes_laneSection_lr_lane>(eachLane));
				}
			}

			if (eachlaneSection->m_right)
			{
				for (auto& eachLane : eachlaneSection->m_right->m_lanes)
				{
					sectionLane.append(std::shared_ptr<t_road_lanes_laneSection_lr_lane>(eachLane));
				}
			}

			roadLane.append(sectionLane);
		}

		roadMapLane.append(std::make_pair(eachRoad->id, roadLane));
	}
}

void XodrNet::loadXodrNet(const QString& path) {
	std::string strPath(path.toLocal8Bit());
	std::shared_ptr<xodr> ptrXodr(new xodr());
	ptrXodr->load(strPath);
	ptrXodr->parse();
	if (!ptrXodr->m_OpenDRIVE) return;

	std::shared_ptr<PrograssDlgForFloat> ptrProDlg(new PrograssDlgForFloat(reinterpret_cast<QWidget*>(gpTessInterface->guiInterface()->mainWindow())));
	ptrProDlg->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	ptrProDlg->setWindowModality(Qt::WindowModal);
	QFont font = QApplication::font();
	font.setPointSizeF(12.5);
	ptrProDlg->setFont(font);
	ptrProDlg->setCancelButton(nullptr);
	ptrProDlg->autoClose();
	ptrProDlg->setFixedSize(QSize(320, 72));
	ptrProDlg->show();



	RoadMapPoint roadMapPoint;
	MapInfo::getInstance()->transferRoadMapInfo(ptrXodr->m_OpenDRIVE->m_roads, roadMapPoint);

	QVector<QVector<QVector<std::pair<QVector<QVector<QPointF> >, int> > > > roadMapLanePaint;
	MapInfo::getInstance()->getRoadGeometryPoint(roadMapPoint, roadMapLanePaint);


	RoadMapPaint roadMapPaint;
	MapInfo::getInstance()->getRoadLaneSectionPoint(roadMapPoint, roadMapPaint);      // 车道段的点

	RoadMapLane roadMapLane;
	transferLanesList(ptrXodr->m_OpenDRIVE->m_roads, roadMapLane);

	CreateLink::getInstance()->reset();
	CreateJountion::getInstance()->reset();

	CreateLink::g_ScenceCenterPt = MapInfo::getInstance()->getCenterPoint();
	QSizeF fSize = MapInfo::getInstance()->getGraphicsSize();
	gpTessInterface->netInterface()->setSceneSize(fSize.width(), fSize.height());

	bool showAll = m_showAll;
	auto contactPointType = enum_map_con();
	ptrProDlg->setInfo("阶段1,解析数据:", roadMapLanePaint.size());
	for (int i = 0; i < roadMapLanePaint.size(); ++i) {
		std::shared_ptr<t_road> ptrRoad = ptrXodr->m_OpenDRIVE->m_roads.at(i);
		QVector<QVector<std::pair<QVector<QVector<QPointF> >, int> > > roadPoint = roadMapLanePaint[i];
		RoadLane roadLane = roadMapLane[i].second;


		if ("-1" != ptrRoad->junction)
		{
			//if ("509" != ptrRoad->junction) continue;
			///交叉口路段
			std::shared_ptr<JounctionRoad> ptrJounctionRd(new JounctionRoad());
			ptrJounctionRd->m_strRoadId = ptrRoad->id;
			for (int j = 0; j < roadPoint.size(); ++j)
			{
				SectionLane sectionLane = roadLane[j];
				int startLaneIndex = getLaneIdFromSection(0, sectionLane);
				for (int n = 0; n < sectionLane.size(); ++n)
				{
					std::shared_ptr<LinkerLane> ptrLane(new LinkerLane());
					ptrLane->m_laneId = getLaneIdFromSection(n, sectionLane);
					if (0 == ptrLane->m_laneId) {
						///路段中心线
						ptrJounctionRd->appendCenterPoint(roadMapPaint[i][j][n]);
						continue;
					}

					if (!showAll && "driving" != enum2str<e_laneType>(sectionLane[n]->type)) continue;

					if (!sectionLane[n]->m_link) continue;
					if (0 == sectionLane[n]->m_link->m_predecessors.size()) continue;
					if (0 == sectionLane[n]->m_link->m_successors.size()) continue;

					ConnectorItem juncItem;
					juncItem.from = std::atoi(ptrRoad->m_link->m_predecessor->elementId.c_str());
					juncItem.to = std::atoi(ptrRoad->m_link->m_successor->elementId.c_str());
					juncItem.contactPointFrom = contactPointType[ptrRoad->m_link->m_predecessor->contactPoint];
					juncItem.contactPointTo = contactPointType[ptrRoad->m_link->m_successor->contactPoint];

					juncItem.fromLaneId = sectionLane[n]->m_link->m_predecessors[0]->id;
					juncItem.toLaneId = sectionLane[n]->m_link->m_successors[0]->id;

					ptrJounctionRd->appendLanePoints(juncItem, ptrLane->m_laneId, ptrLane->initLanePoints(i, j, n, roadMapPaint, n < startLaneIndex));
				}
			}
			CreateJountion::getInstance()->appendConnectData(std::atoi(ptrRoad->id.c_str()), ptrJounctionRd);
		}
		else {
			///直线型路段
			//if ("25" != ptrRoad->id && "30" != ptrRoad->id) continue;
			std::shared_ptr<LinkerRoad> ptrLinkerRoad(new LinkerRoad());
			ptrLinkerRoad->m_strRoadId = ptrRoad->id;
	
			for (int j = 0; j < roadPoint.size(); ++j)
			{
				std::shared_ptr<LinkerSection> ptrSection(new LinkerSection(ptrLinkerRoad.get()));
				ptrSection->sectionIndex = ptrLinkerRoad->getIndexSection();

				SectionLane sectionLane = roadLane[j];
				int startLaneIndex = getLaneIdFromSection(0, sectionLane);
				for (int n = 0; n < sectionLane.size(); ++n)
				{
					std::shared_ptr<LinkerLane> ptrLane(new LinkerLane());
					ptrLane->m_laneId = getLaneIdFromSection(n, sectionLane);
					if (0 == ptrLane->m_laneId) {
						///路段中心线
						ptrSection->appendCenterPoint(roadMapPaint[i][j][n]);
						continue;
					}

					if (!showAll && "driving" != enum2str<e_laneType>(sectionLane[n]->type)) continue;

					ptrSection->appendLanePoints(ptrLane->m_laneId, ptrLane->initLanePoints(i, j, n, roadMapPaint, n < startLaneIndex), n < startLaneIndex);

					SectionConnectItem sectionConnItem;
					sectionConnItem.xodrInfo.from = ptrSection->sectionIndex;
					sectionConnItem.fromRoadId = ptrRoad->id;

					if (sectionLane[n]->m_link && sectionLane[n]->m_link->m_successors.size() > 0) {
						sectionConnItem.xodrInfo.fromLaneId = ptrLane->m_laneId;
						sectionConnItem.xodrInfo.toLaneId = sectionLane[n]->m_link->m_successors[0]->id;
						//sectionConnItem.xodrInfo.contactPointFrom = "end";
						if (j + 1 < roadPoint.size()) {
							sectionConnItem.toRoadId = ptrRoad->id;
							sectionConnItem.xodrInfo.to = sectionConnItem.xodrInfo.from + 1;
							//sectionConnItem.xodrInfo.contactPointTo = "end";
							CreateLink::getInstance()->appendSectionConnectItems(sectionConnItem);
							continue;
						}

						sectionConnItem.toRoadId = ptrRoad->m_link->m_successor->elementId;
						sectionConnItem.xodrInfo.to = 0;
	
						//sectionConnItem.xodrInfo.contactPointTo = contactPointType[ptrRoad->m_link->m_successor->contactPoint];
						CreateLink::getInstance()->filterLinkConnectOr(sectionConnItem);
					}
				}
				
				ptrLinkerRoad->m_listSections.append(ptrSection);
			}
			CreateLink::getInstance()->appendRoads(ptrLinkerRoad);
		}
		ptrProDlg->addPrescent(1);
	}
	setNetAttrs(ptrXodr->m_OpenDRIVE->m_header.get(), path);


	CreateLink::getInstance()->paint(ptrProDlg.get());

	CreateJountion::getInstance()->paint(ptrProDlg.get());

	ptrProDlg->setValue(ptrProDlg->maximum());
}
