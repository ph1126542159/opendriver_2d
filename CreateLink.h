﻿#pragma once
#include "Plugin/_netitem.h"
#include "Plugin/_netitemtype.h"
#include "ilink.h"
#include "IConnector.h"
#include "MapInfo.h"
#include <QVector3D>
#include <qmath.h>
#include <QPolygonF>


typedef QVector<QPointF> LanePaint;
typedef QVector<LanePaint> LaneSectionPaint;
typedef QVector<LaneSectionPaint> RoadPaint;
typedef QVector<RoadPaint> RoadMapPaint;
typedef QVector<std::shared_ptr<t_road_lanes_laneSection_lr_lane>> SectionLane;
typedef QVector<SectionLane> RoadLane;
typedef QVector<std::pair<std::string/*road id*/, RoadLane> > RoadMapLane;

class PrograssDlgForFloat;
class LinkerRoad;
class LinkerSection;
class RoadSection;

class ConnectorItem {
public:
	int from;
	int to;
	int fromLaneId;
	int toLaneId;

	std::string contactPointFrom;

	std::string contactPointTo;

	std::string roadId;

	ConnectorItem() {
		from = 0;
		to = 0;
		fromLaneId = 0;
		toLaneId = 0;
		contactPointFrom = "";
		contactPointTo = "";
		roadId = "";
	}

	bool operator==(const ConnectorItem& other)const {
		return from == other.from &&
			to == other.to &&
			fromLaneId == other.fromLaneId &&
			toLaneId == other.toLaneId;
	}
};
inline uint qHash(const ConnectorItem& key, uint seed) {
	return qHash(key.from, seed) ^ qHash(key.to, seed) ^
		qHash(key.fromLaneId, seed) ^ qHash(key.toLaneId, seed);
}
class SectionConnectItem {
public:
	std::string fromRoadId;
	std::string toRoadId;
	ConnectorItem xodrInfo;

	SectionConnectItem() {
		fromRoadId = "";
		toRoadId = "";
	}

	bool operator == (const SectionConnectItem& other)const {
		return  xodrInfo == other.xodrInfo &&
			((fromRoadId == other.fromRoadId && toRoadId == other.toRoadId) || (fromRoadId == other.toRoadId && toRoadId == other.fromRoadId));
	}
};

class LinkerLane {
public:
	int m_laneId;
	QMap<QString, QList<QVector3D>> initLanePoints(int roadIndex, int sectionIndex, int laneIndex, RoadMapPaint& roadMapPaint, bool isLeft);
private:
	bool m_isLeft;
};
class RoadSection {
public:
	void appendCenterPoint(const QPolygonF& pts);
protected:
	QList<QMap<QString, QList<QVector3D>>> lanesWithPointsForLeft;
	QList<QMap<QString, QList<QVector3D>>> lanesWithPointsForRight;
	QList<int> m_leftLaneIds;
	QList<int> m_RightLaneIds;
	QPolygonF m_centerLine;
};
class LinkerSection :public RoadSection {
public:
	int sectionIndex;
	LinkerSection(LinkerRoad* ptrRoad);
	void paint();
	void appendLanePoints(int laneId, const QMap<QString, QList<QVector3D>>& points, bool isLeft);
private:
	LinkerSection() = delete;
	void setLinkerData(ILink* linker, const QList<int>& laneIds);
	LinkerRoad* m_ptrRoad;
};

class LinkerRoad {
public:
	std::string m_strRoadId;
	int getIndexSection();
	int getFirstSectionIndex();
	int getLastSectionIndex();
	QList<std::shared_ptr<LinkerSection>> m_listSections;
	void paint();
};

class CreateLink {
public:
	static CreateLink* getInstance();
	void reset();
	void paint(PrograssDlgForFloat*);
	void appendRoads(std::shared_ptr<LinkerRoad>);
	void appendLinkerData(int roadId, int sectionIndex,int laneId, const QPair<int, int>& info);
	bool getTessngConnectorData(int& linkId, int& laneId,bool isFrom);
	int createRoadId();
	bool checkHasPatined(const ConnectorItem& item);
	void appendSectionConnectItems(const SectionConnectItem& item);
	bool checkConnectorItem(ConnectorItem& item);
	void filterLinkConnectOr(const SectionConnectItem& item);

	static QPointF g_ScenceCenterPt;
	static bool g_isReverse;
private:
	CreateLink();
	void createSectionConnector();
	bool getSectionConnInfo(SectionConnectItem& item);
	int getFirstSectionIndex(int);
	int getLastSectionIndex(int);
	static int userDefRoadId;
	QHash<int, std::shared_ptr<LinkerRoad>> m_mapRoads;
	QList<ConnectorItem> hasPaintedList;
	QList<SectionConnectItem> secConnItemList;
	QHash<int/*road id*/, QHash<int/*section index*/, QHash<int/*lane id*/, QPair<int/*tessng link id*/, int/*tessng lane id*/>>>> m_linkerData;
	PrograssDlgForFloat* m_ptrProDld;
};

