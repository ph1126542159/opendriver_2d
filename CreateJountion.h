#ifndef CREATEJOUNTION_H
#define CREATEJOUNTION_H
#include "CreateLink.h"
#include <QHash>


class JounctionRoad {
public:
    std::string m_strRoadId;
    void appendLanePoints(const ConnectorItem& item,int laneId, const QMap<QString, QList<QVector3D>>& points);
    void appendCenterPoint(const QPolygonF& pts);
    void paint();

    void paint2();
private:
    void createArea(const QList<int>& leftLaneIds, const QList<int>& rightLaneIds,
        const QList<QVector3D>& listCenter, const QList<QMap<QString, QList<QVector3D>>>& ptsLeft,
        const QList<QMap<QString, QList<QVector3D>>>& ptsRight,int roadId);


    void createAreaSub(const QList<int>& laneIds, const QList<QVector3D>& listCenter, const QList<QMap<QString, QList<QVector3D>>>& pts, int roadId);

    void createLinkerConnector(QList<ConnectorItem>& linkerConnect);

    void createJounctionConnector(QList<ConnectorItem>& linkerConnect, const QList<QMap<QString, QList<QVector3D>>>& map);


    QHash<ConnectorItem, QHash<int/*lane id*/, QMap<QString, QList<QVector3D>>>> lanePtsHash;
    QList<QVector3D> m_centerLine;
};
class CreateJountion
{
public:
    static CreateJountion* getInstance();
    void reset();
    void appendConnectData(int,std::shared_ptr<JounctionRoad> ptr);
    void paint(PrograssDlgForFloat*);
private:
    CreateJountion();
    QHash<int,std::shared_ptr<JounctionRoad>> m_mapConnData;
};

#endif // CREATEJOUNTION_H
