/*******************************************************************************
* 路网元素类型常量定义
********************************************************************************/

#ifndef __NetItemType__
#define __NetItemType__

#include "../tessinterfaces_global.h"

#include <QGraphicsItem>

class TESSINTERFACES_EXPORT NetItemType {
public:
	static const int GVertexType = QGraphicsItem::UserType + 1;
	static const int GLinkType = QGraphicsItem::UserType + 2;
	static const int GLaneType = QGraphicsItem::UserType + 3;
	static const int GConnectorType = QGraphicsItem::UserType + 4;
	static const int GLaneConnectorType = QGraphicsItem::UserType + 5;
	static const int GDecisionType = QGraphicsItem::UserType + 6;
	static const int GDeparturePointType = QGraphicsItem::UserType + 7;
	static const int GVehicleType = QGraphicsItem::UserType + 8;
	static const int GSignalLampType = QGraphicsItem::UserType + 9;
	static const int GVehicleDrivInfoCollecterType = QGraphicsItem::UserType + 10;
	static const int GVehicleQueueCounterType = QGraphicsItem::UserType + 11;
	static const int GVehicleTravelDetectorType = QGraphicsItem::UserType + 12;
	static const int GReduceSpeedAreaType = QGraphicsItem::UserType + 13;
	static const int GBusStationType = QGraphicsItem::UserType + 14;
	static const int GBusLineType = QGraphicsItem::UserType + 15;
	static const int GGuideArrowType = QGraphicsItem::UserType + 16;
	static const int GConnectorAreaType = QGraphicsItem::UserType + 17;
	static const int GLinkCenterType = QGraphicsItem::UserType + 18;
	static const int GVehicleDetectorType = QGraphicsItem::UserType + 19;

	static const int LaneType = QGraphicsItem::UserType + 101;
	static const int LaneConnectorType = QGraphicsItem::UserType + 102;
};

#endif