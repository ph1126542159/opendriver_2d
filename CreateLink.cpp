#include "CreateLink.h"
#include "netinterface.h"
#include "TessInterfaces.h"
#include "PrograssDlgForFloat.h"

#include <QDebug>

bool CreateLink::g_isReverse = true;
int CreateLink::userDefRoadId = 0;
double CreateLink::m_minDis = 0.0001;
QPointF CreateLink::g_ScenceCenterPt = QPointF(0, 0);
CreateLink::CreateLink(){

}
bool CreateLink::checkConnectorItem(ConnectorItem& item) {
	if (item.fromLaneId < 0 && item.toLaneId < 0) {
		if ("end" == item.contactPointFrom && "end" == item.contactPointTo) {
			item.toLaneId = -item.toLaneId;
			//return false;///正确
		}
		if ("end" == item.contactPointFrom && "start" == item.contactPointTo) {
			//return false;///正确
		}
		if ("start" == item.contactPointFrom && "end" == item.contactPointTo) {
			std::swap(item.from, item.to);
			std::swap(item.fromLaneId, item.toLaneId);
			//return false;///正确
		}
		if ("start" == item.contactPointFrom && "start" == item.contactPointTo) {
			item.fromLaneId = -item.fromLaneId;
			//return false;///扭曲
		}

	}
	if (item.fromLaneId < 0 && item.toLaneId > 0) {
		if ("end" == item.contactPointFrom && "end" == item.contactPointTo) {
			//return false;///扭曲
		}
		if ("end" == item.contactPointFrom && "start" == item.contactPointTo) {
			//return false;///扭曲
		}
		if ("start" == item.contactPointFrom && "end" == item.contactPointTo) {
			item.fromLaneId = -item.fromLaneId;
			//return false;//正确
		}
		if ("start" == item.contactPointFrom && "start" == item.contactPointTo) {
			std::swap(item.from, item.to);
			std::swap(item.fromLaneId, item.toLaneId);
			//return false;///扭曲
		}
	}
	if (item.fromLaneId > 0 && item.toLaneId < 0) {
		if ("end" == item.contactPointFrom && "end" == item.contactPointTo) {
			std::swap(item.from, item.to);
			std::swap(item.fromLaneId, item.toLaneId);
			//return false;///扭曲
		}
		if ("end" == item.contactPointFrom && "start" == item.contactPointTo) {
			//return false;
			///暂时未有此类情况
		}
		if ("start" == item.contactPointFrom && "end" == item.contactPointTo) {
			item.toLaneId = -item.toLaneId;
			//return false;///扭曲
		}
		if ("start" == item.contactPointFrom && "start" == item.contactPointTo) {
			//return false;///扭曲
		}
	}
	if (item.fromLaneId > 0 && item.toLaneId > 0) {
		if ("end" == item.contactPointFrom && "end" == item.contactPointTo) {
			item.fromLaneId = -item.fromLaneId;
			//return false;///扭曲
		}
		if ("end" == item.contactPointFrom && "start" == item.contactPointTo) {
			std::swap(item.from, item.to);
			std::swap(item.fromLaneId, item.toLaneId);
			//return false;///正确
		}
		if ("start" == item.contactPointFrom && "end" == item.contactPointTo) {
			//return false;///正确
		}
		if ("start" == item.contactPointFrom && "start" == item.contactPointTo) {
			item.toLaneId = -item.toLaneId;
			//return false;///扭曲
		}
	}
	return true;
}
bool CreateLink::checkHasPatined(const ConnectorItem& item) {
	if (hasPaintedList.contains(item)) return true;
	hasPaintedList.append(item);
	return false;
}
CreateLink* CreateLink::getInstance()
{
	static CreateLink linkCreator;
	return &linkCreator;
}
void CreateLink::reset()
{
	m_mapRoads.clear();
	hasPaintedList.clear();
	userDefRoadId = 0;
	m_linkerData.clear();
	secConnItemList.clear();
}


void CreateLink::appendRoads(std::shared_ptr<LinkerRoad> ptrRoad)
{
	m_mapRoads[std::atoi(ptrRoad->m_strRoadId.c_str())] = ptrRoad;
}


void CreateLink::appendSectionConnectItems(const SectionConnectItem& item) {
	if (secConnItemList.contains(item)) return;
	secConnItemList.append(item);
}
void CreateLink::filterLinkConnectOr(const SectionConnectItem& item) {
	bool flag = false;
	for (auto& it : secConnItemList) {
		if (it.toRoadId == it.fromRoadId) continue;
		if (it.toRoadId == item.fromRoadId && it.fromRoadId == item.toRoadId) {
			flag = true;
			break;
		}
	}
	if (flag) return;
	secConnItemList.append(item);
}
LinkerSection::LinkerSection(LinkerRoad* ptrRoad) :RoadSection(), m_ptrRoad(ptrRoad)
{

}

void LinkerSection::setLinkerData(ILink* linker, const QList<int>& laneIds)
{
	if (nullptr == linker) return;
	QList<ILane*> lanes = linker->lanes();
	int roadId = std::atoi(m_ptrRoad->m_strRoadId.c_str());
	for (int i = 0; i < lanes.size(); i++) {
		CreateLink::getInstance()->appendLinkerData(roadId, sectionIndex, laneIds[i], QPair<int, int>(linker->id(), lanes[i]->number() + 1));
	}
}


void LinkerSection::appendLanePoints(int laneId, const QMap<QString, QList<QVector3D> >& points, bool isLeft)
{
	if (isLeft) {
		lanesWithPointsForLeft.append(points);
		m_leftLaneIds.append(laneId);
		return;
	}
	lanesWithPointsForRight.append(points);
	m_RightLaneIds.append(laneId);
}
void LinkerSection::arrangePoints() {
	for (auto& it : m_centerLine) {
		m_rightCentePts.append(QVector3D(it.x() - CreateLink::g_ScenceCenterPt.x(), it.y() - CreateLink::g_ScenceCenterPt.y(), 0.0f));
	}
	m_leftCentePts = m_rightCentePts;
	if (CreateLink::g_isReverse) {
		std::reverse(m_leftCentePts.begin(), m_leftCentePts.end());
		std::reverse(lanesWithPointsForLeft.begin(), lanesWithPointsForLeft.end());
		std::reverse(m_leftLaneIds.begin(), m_leftLaneIds.end());
	}
}
void LinkerSection::paint()
{
	ILink* linker = gpTessInterface->netInterface()->createLink3DWithLanePoints(m_rightCentePts, lanesWithPointsForRight);
	setLinkerData(linker, m_RightLaneIds);

	linker = gpTessInterface->netInterface()->createLink3DWithLanePoints(m_leftCentePts, lanesWithPointsForLeft);
	setLinkerData(linker, m_leftLaneIds);
}
QList<QVector3D>& RoadSection::getLeftCenterPoints() {
	return m_leftCentePts;
}
QList<QVector3D>& RoadSection::getRightCenterPoints() {
	return m_rightCentePts;
}
void RoadSection::removePtsFromList(int start, int removeCount, QList<QVector3D>& list) {
	if (list.size() - removeCount < 2) {
		int addNum = (list.size() + 1 - removeCount) * 2;
		float uint = 1.0 / (addNum);
		QVector3D uvec = uint * (list.last() - list.first());

		QVector3D begin = list.first();
		list.clear();
		for (int i = 0; i < addNum; i++) {
			list.append(begin + i * uvec);
		}
	}
	while (removeCount > 0)
	{
		if (0 == start) list.removeFirst();
		else list.removeLast();
		removeCount--;
	}
}
void RoadSection::removePointsByCount(int start, int removeCount, QList<QVector3D>& center, QList<QMap<QString, QList<QVector3D>>>& listPits) {
	removePtsFromList(start, removeCount, center);

	for (auto& it : listPits) {
		removePtsFromList(start, removeCount, it["left"]);
		removePtsFromList(start, removeCount, it["center"]);
		removePtsFromList(start, removeCount, it["right"]);
	}
}
void RoadSection::removePointsByCount(int start, int removeCount) {
	if (0 == start) {
		removePointsByCount(start, removeCount, m_leftCentePts, lanesWithPointsForLeft);
		removePointsByCount(m_rightCentePts.size()- removeCount, removeCount, m_rightCentePts, lanesWithPointsForRight);
	}
	else {
		removePointsByCount(0, removeCount, m_leftCentePts, lanesWithPointsForLeft);
		removePointsByCount(start, removeCount, m_rightCentePts, lanesWithPointsForRight);
	}
}
void RoadSection::appendCenterPoint(const QPolygonF& pts)
{
	m_centerLine << pts;
}
int LinkerRoad::getIndexSection() {
	return m_listSections.size();
}
void LinkerRoad::removePointsByCount(int index, int start, int removeCount) {
	m_listSections[index]->removePointsByCount(start, removeCount);
}
QMap<QString, QList<QVector3D>> LinkerLane::initLanePoints(int roadIndex, int sectionIndex, int laneIndex, RoadMapPaint& roadMapPaint, bool isLeft)
{
	QPolygonF qvecOutsideLaneData;
	QPolygonF qvecInsideLaneData;
	m_isLeft = isLeft;
	if (m_isLeft) {
		qvecOutsideLaneData = roadMapPaint[roadIndex][sectionIndex][laneIndex + 1];
		qvecInsideLaneData = roadMapPaint[roadIndex][sectionIndex][laneIndex];
	}
	else {
		qvecOutsideLaneData = roadMapPaint[roadIndex][sectionIndex][laneIndex];
		qvecInsideLaneData = roadMapPaint[roadIndex][sectionIndex][laneIndex - 1];
	}
	int ncounter = qvecOutsideLaneData.size() > qvecInsideLaneData.size() ? qvecInsideLaneData.size() : qvecOutsideLaneData.size();
	QList<QVector3D> laneCenterPoints, laneLeftPoints, laneRightPoints;
	for (int i = 0; i < ncounter; i++) {
		laneCenterPoints.append(QVector3D((qvecInsideLaneData[i].x() + qvecOutsideLaneData[i].x()) / 2.0f - CreateLink::g_ScenceCenterPt.x(),
			(qvecInsideLaneData[i].y() + qvecOutsideLaneData[i].y()) / 2.0f - CreateLink::g_ScenceCenterPt.y(), 0.0f));
		laneLeftPoints.append(QVector3D(qvecOutsideLaneData[i].x() - CreateLink::g_ScenceCenterPt.x(), qvecOutsideLaneData[i].y() - CreateLink::g_ScenceCenterPt.y(), 0.0f));
		laneRightPoints.append(QVector3D(qvecInsideLaneData[i].x() - CreateLink::g_ScenceCenterPt.x(), qvecInsideLaneData[i].y() - CreateLink::g_ScenceCenterPt.y(), 0.0f));
	}

	if (m_isLeft && CreateLink::g_isReverse) {
		std::reverse(laneCenterPoints.begin(), laneCenterPoints.end());
		std::reverse(laneLeftPoints.begin(), laneLeftPoints.end());
		std::reverse(laneRightPoints.begin(), laneRightPoints.end());
	}

	QMap<QString, QList<QVector3D>> map;
	map["center"] = laneCenterPoints;
	if (m_isLeft && CreateLink::g_isReverse) {
		map["left"] = laneRightPoints;
		map["right"] = laneLeftPoints;
	}
	else {
		map["left"] = laneLeftPoints;
		map["right"] = laneRightPoints;
	}

	return map;
}
void CreateLink::removeSectionConnPoints(const SectionConnectItem& item) {
	QList<QVector3D> fromCenterPts,toCenterPts;
	if (item.xodrInfo.fromLaneId > 0) {
		fromCenterPts = m_mapRoads[std::atoi(item.fromRoadId.c_str())]->getLeftCenterPoints(item.xodrInfo.from);
	}
	else {
		fromCenterPts = m_mapRoads[std::atoi(item.fromRoadId.c_str())]->getRightCenterPoints(item.xodrInfo.from);
	}

	if (item.xodrInfo.toLaneId > 0) {
		toCenterPts = m_mapRoads[std::atoi(item.toRoadId.c_str())]->getLeftCenterPoints(item.xodrInfo.to);
	}
	else {
		toCenterPts = m_mapRoads[std::atoi(item.toRoadId.c_str())]->getRightCenterPoints(item.xodrInfo.to);
	}
	int m= fromCenterPts.size()-1;
	int n=0;
	QVector3D fromPt, toPt;
	double dis=0;
	while (true)
	{
		if (m <= 0 || n >= toCenterPts.size() - 1) break;
		fromPt = fromCenterPts[m];
		toPt = toCenterPts[n];
		dis = std::sqrt(std::pow(fromPt.x()-toPt.x(), 2) + std::pow(fromPt.y()-toPt.y(), 2));
		int nRt = IsEqualZero(dis - CreateLink::m_minDis);
		if (nRt >= 0) break;
		m--;
		n++;
	}
	m_mapRoads[std::atoi(item.fromRoadId.c_str())]->removePointsByCount(item.xodrInfo.from, m, n);
	m_mapRoads[std::atoi(item.toRoadId.c_str())]->removePointsByCount(item.xodrInfo.to, 0, n);
}
void CreateLink::paint(PrograssDlgForFloat* ptrProDlg)
{
	QList<SectionFilterInfo> listSecCon;
	m_ptrProDld = ptrProDlg;
	m_ptrProDld->setInfo("阶段2,创建路段:", m_mapRoads.size());
	for (auto &item : secConnItemList) {
		swapSectionConnectorInfo(item);

		SectionFilterInfo con;
		con.fromRoadId = item.fromRoadId;
		con.toRoadId = item.toRoadId;
		con.fromSectionIndex = item.xodrInfo.from;
		con.toSectionIndex = item.xodrInfo.to;


		if (listSecCon.contains(con)) continue;
		removeSectionConnPoints(item);
		listSecCon.append(con);
	}
	for (auto it : m_mapRoads) {
		it->paint();
		m_ptrProDld->addPrescent(1.0);
	}
	createSectionConnector();
}
void LinkerRoad::paint()
{
	for (auto it : m_listSections) {
		it->paint();
	}
}
int LinkerRoad::getFirstSectionIndex() {
	return m_listSections.first()->sectionIndex;
}
int LinkerRoad::getLastSectionIndex() {
	return m_listSections.last()->sectionIndex;
}

QList<QVector3D>& LinkerRoad::getLeftCenterPoints(int index) {
	return m_listSections[index]->getLeftCenterPoints();
}
QList<QVector3D>& LinkerRoad::getRightCenterPoints(int index) {
	return m_listSections[index]->getRightCenterPoints();
}
void CreateLink::appendLinkerData(int roadId, int sectionIndex, int laneId, const QPair<int, int>& info) {
	m_linkerData[roadId][sectionIndex][laneId] = info;
}
bool CreateLink::getTessngConnectorData(int& linkId, int& laneId, bool isFrom)
{
	if (!m_linkerData.contains(linkId)) return false;
	auto it = m_linkerData[linkId].begin();
	if (isFrom) {
		it = m_linkerData[linkId].end();
		--it;
	}
	auto& likerData = it.value();
	if (!likerData.contains(laneId)) return false;
	QPair<int, int> info = likerData[laneId];
	linkId = info.first;
	laneId = info.second;
	return true;
}
int CreateLink::createRoadId() {
	while (!m_linkerData.contains(userDefRoadId++)) {
		break;
	}
	return userDefRoadId;
}
int CreateLink::getFirstSectionIndex(int id) {
	return m_mapRoads[id]->getFirstSectionIndex();
}
int CreateLink::getLastSectionIndex(int id) {
	return m_mapRoads[id]->getLastSectionIndex();
}
void CreateLink::swapSectionConnectorInfo(SectionConnectItem& item) {
	int rdFrom = std::atoi(item.fromRoadId.c_str());
	int rdTo = std::atoi(item.toRoadId.c_str());

	int fromLaneId = item.xodrInfo.fromLaneId;
	int toLane = item.xodrInfo.toLaneId;
	if (item.fromRoadId != item.toRoadId) {
		if (fromLaneId < 0 && toLane < 0) {
		}
		else if (fromLaneId < 0 && toLane > 0) {
			item.xodrInfo.from = getLastSectionIndex(rdFrom);
			item.xodrInfo.to = getLastSectionIndex(rdTo);
		}
		else if (fromLaneId > 0 && toLane > 0) {
			std::swap(rdFrom, rdTo);
			std::swap(fromLaneId, toLane);
			item.xodrInfo.from = getFirstSectionIndex(rdFrom);
			item.xodrInfo.to = getFirstSectionIndex(rdTo);
		}
		else if (fromLaneId > 0 && toLane < 0) {
			std::swap(rdFrom, rdTo);
			std::swap(fromLaneId, toLane);
			item.xodrInfo.from = getFirstSectionIndex(rdFrom);
			item.xodrInfo.to = getLastSectionIndex(rdTo);
		}
	}
	else {
		if (fromLaneId < 0 && toLane < 0) {

		}
		else if (fromLaneId < 0 && toLane > 0) {

		}
		else if (fromLaneId > 0 && toLane > 0) {
			std::swap(item.xodrInfo.from, item.xodrInfo.to);
			std::swap(fromLaneId, toLane);
		}
		else if (fromLaneId > 0 && toLane < 0) {
			std::swap(item.xodrInfo.from, item.xodrInfo.to);
			std::swap(fromLaneId, toLane);
		}
	}
	item.fromRoadId = std::to_string(rdFrom);
	item.toRoadId = std::to_string(rdTo);
	item.xodrInfo.fromLaneId = fromLaneId;
	item.xodrInfo.toLaneId = toLane;
}
bool CreateLink::getSectionConnInfo(SectionConnectItem& item) {
	int rdFrom = std::atoi(item.fromRoadId.c_str());
	int rdTo = std::atoi(item.toRoadId.c_str());

	if (!m_linkerData.contains(rdFrom)) return false;
	if (!m_linkerData.contains(rdTo)) return false;

	int fromLaneId = item.xodrInfo.fromLaneId;
	int toLane = item.xodrInfo.toLaneId;

	int sectionindexFrom = item.xodrInfo.from;

	if (!m_linkerData[rdFrom].contains(sectionindexFrom)) return false;
	if (!m_linkerData[rdFrom][sectionindexFrom].contains(fromLaneId)) return false;
	item.xodrInfo.from = m_linkerData[rdFrom][sectionindexFrom][fromLaneId].first;
	item.xodrInfo.fromLaneId = m_linkerData[rdFrom][sectionindexFrom][fromLaneId].second;

	int sectionIdexTo = item.xodrInfo.to;
	if (!m_linkerData[rdTo].contains(sectionIdexTo)) return false;
	if (!m_linkerData[rdTo][sectionIdexTo].contains(toLane)) return false;
	item.xodrInfo.to = m_linkerData[rdTo][sectionIdexTo][toLane].first;
	item.xodrInfo.toLaneId = m_linkerData[rdTo][sectionIdexTo][toLane].second;

	return true;
}
void CreateLink::createSectionConnector() {
	m_ptrProDld->setInfo("阶段3,创建链接关系:", secConnItemList.size());

	for (auto it : secConnItemList) {
		if (!getSectionConnInfo(it)) continue;
		QList<int> fromLanes, toLanes;
		fromLanes << it.xodrInfo.fromLaneId;
		toLanes << it.xodrInfo.toLaneId;
		if (checkHasPatined(it.xodrInfo)) continue;
		gpTessInterface->netInterface()->createConnector(it.xodrInfo.from, it.xodrInfo.to, fromLanes, toLanes);
		m_ptrProDld->addPrescent(1.0);
	}
}