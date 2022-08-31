/****************************************************************************
* 支持在线仿真的几种数据结构，用于在仿真过程中参数的动态输入以及仿真结果的动态输出
*****************************************************************************/

#ifndef __DataStruct__
#define __DataStruct__

#include "../tessinterfaces_global.h"

#include <QObject>
#include <QPointF>
#include <QVector3D>
#include <QColor>
#include <QList>
#include <QJsonObject>

namespace Online {
	/*
	机动车或非机动车分类
	*/
	enum MotorOrNonmotor {Motor, Nonmotor};
	
	/*
	车型组成 vehiTypeCode:车型编码，proportion：分配比
	*/
	struct TESSINTERFACES_EXPORT VehicleComposition {
		/*车型编码*/
		long vehiTypeCode;
		/*分配比*/
		qreal proportion;
		VehicleComposition(long c, qreal p) {
			vehiTypeCode = c;
			proportion = p;
		}
	};

	/*
	发车间隔 dispatchId:发车点ID，toTime:该时间段结束时间(秒), vehiCount:发车数
	*/
	struct TESSINTERFACES_EXPORT DispatchInterval {
		/*发车点ID*/
		long dispatchId;
		/*起始时间 单位秒*/
		long fromTime; 
		/*结束时间 单位秒*/
		long toTime; 
		int vehiCount;
		QList<VehicleComposition> mlVehicleConsDetail;
	};

	/*
	路径流量分配比
	*/
	struct TESSINTERFACES_EXPORT RoutingFlowRatio {
		/* 路径编号 */
		long routingID;
		/* 分配比 */
		qreal ratio;
		RoutingFlowRatio(long id, qreal r) {
			routingID = id;
			ratio = r;
		}
	};

	/*
	一个决策点某个时段各路径车辆分配比
	*/
	struct TESSINTERFACES_EXPORT DecipointFlowRatioByInterval {
		/*决策点编号*/
		long deciPointID;
		/* 起始时间 单位秒*/
		long startDateTime;
		/* 结束时间 单位秒*/
		long endDateTime;
		QList<RoutingFlowRatio> mlRoutingFlowRatio;
	};

	/*
	车辆状态含轨迹
	*/
	struct TESSINTERFACES_EXPORT VehicleStatus{
		/*车辆ID*/
		long vehiId;
		/*车长(米)*/
		qreal mrLength;
		/*车宽(米)*/
		qreal mrWidth;
		/*颜色*/
		QColor mColor;
		/*车辆类型编码*/
		long vehiType;
		/*起始路段ID*/
		long startLinkId;
		/*车辆启动时仿真时间*/
		long startSimuTime;
		/*仿真时间(毫秒)*/
		long mrDatetime;
		/*速度(米/秒)*/
		qreal mrSpeed;
		/*加速度(米/秒/秒)*/
		qreal mrAcce;
		/*已行驶里程(米)*/
		qreal mrDrivDistance;
		/*当前点位*/
		QVector3D mPoint;
		/*当前3维空间的欧拉角*/
		QVector3D mEuler;
		/*方向角，0度指向北，顺时针*/
		qreal mrAngle;
		/*道路ID*/
		long mrRoadId;
		/*道路类型, "L":路段, "C":连接段*/
		QString roadType;
		/*计算批次*/
		long mrBatchNumber;

		VehicleStatus()
		{
			vehiId = 0;
			mrDatetime = 0;
			mrSpeed = 0;
			mrAngle = 0;
			mrRoadId = 0;
			mrBatchNumber = 0;
		}
	};

	/*
	车辆位置信息
	*/
	struct TESSINTERFACES_EXPORT VehiclePosition {
		/*车辆ID*/
		long vehiId;
		/*仿真时间(毫秒)*/
		long mrDatetime;
		/*当前点位*/
		QVector3D mPoint;
		/*当前3维空间的欧拉角*/
		QVector3D mEuler;
		/*方向角，0度指向北，顺时针*/
		qreal mrAngle;
		/*计算批次*/
		long mrBatchNumber;

		VehiclePosition()
		{
			vehiId = 0;
			mrDatetime = 0;
			mrAngle = 0;
			mrBatchNumber = 0;
		}
	};


	/*
	数据采集点数据
	*/
	struct TESSINTERFACES_EXPORT VehiInfoCollected {
		/*采集器ID*/
		long collectorId;
		/*车辆ID*/
		long vehiId;
		/*仿真时间(s)*/
		long simuInterval;
		/*已行驶时间(s)*/
		long drivInterval;
		/*车辆类型*/
		int vehiType;
		/*车辆长度(m)*/
		qreal length;
		/*期望速度(km/h)*/
		qreal desirSpeed;
		/*平均速度(km/h)*/
		qreal avgSpeed;
		/*加速度(m/s2)*/
		qreal acce;
		/*跟车距离*/
		qreal distFront;
		/*跟车时距*/
		qreal intervalFront;

		VehiInfoCollected() {
			collectorId = 0;
			vehiId = 0;
			simuInterval = 0;
			drivInterval = 0;
			vehiType = 0;
			length = 0;
			desirSpeed = 0;
			avgSpeed = 0;
			acce = 0;
			distFront = 0;
			intervalFront = 0;
		}
	};

	/*
	数据采集点信息集计数据
	*/
	struct TESSINTERFACES_EXPORT VehiInfoAggregated {
		/*采集器ID*/
		long collectorId;
		/*时间段*/
		int timeId;
		/*起始时间(秒)*/
		long fromTime;
		/*结束时间(秒)*/
		long toTime;
		/*平均速度*/
		qreal avgSpeed;
		/*平均占有率*/
		qreal occupancy;
		/*车辆数*/
		int vehiCount;

		VehiInfoAggregated() {
			collectorId = 0;
			timeId = 0;
			fromTime = 0;
			toTime = 0;
			avgSpeed = 0;
			occupancy = 0;
			vehiCount = 0;
		}
	};

	/*
	排队计数信息
	*/
	struct TESSINTERFACES_EXPORT VehiQueueCounted {
		/*排除计数器ID*/
		long counterId;
		/*时间段*/
		int timeId;
		/*起始时间(秒)*/
		long fromTime;
		/*结束时间(秒)*/
		long toTime;
		/*仿真时间(秒)*/
		long simuTime;
		/*排队车辆数*/
		int vehiCount;
		/*排队长度(米)*/
		qreal queueLength;

		VehiQueueCounted() {
			counterId = 0;
			timeId = 0;
			fromTime = 0;
			toTime = 0;
			simuTime = 0;
			vehiCount = 0;
			queueLength = 0;
		}
	};

	/*
	排队计数器集计数据
	*/
	struct TESSINTERFACES_EXPORT VehiQueueAggregated {
		/*排除计数器ID*/
		long counterId;
		/*时间段*/
		int timeId;
		/*起始时间(秒)*/
		long fromTime;
		/*结束时间(秒)*/
		long toTime;
		/*最大排队长度*/
		qreal maxQueueLength;
		/*最小排队长度*/
		qreal minQueueLength;
		/*平均排队长度(米)*/
		qreal avgQueueLength;
		/*平均排队车辆数*/
		qreal avgVehiCount;

		VehiQueueAggregated() {
			counterId = 0;
			timeId = 0;
			fromTime = 0;
			toTime = 0;
			maxQueueLength = 0;
			minQueueLength = 0;
			avgQueueLength = 0;
			avgVehiCount = 0;
		}
	};

	/*
	行程时间检测器数据
	*/
	struct TESSINTERFACES_EXPORT VehiTravelDetected {
		/*检测器ID*/
		long detectedId;
		/*车辆ID*/
		long vehiId;
		/*起始时间(秒)*/
		qreal fromTime;
		/*结束时间(秒)*/
		qreal toTime;
		/*行驶时间*/
		qreal travelTime;
		/*行驶距离*/
		qreal travelDistance;
		/*延误*/
		qreal delay;
		/*期望速度(千米/小时)*/
		qreal desireSpeed;

		VehiTravelDetected() {
			detectedId = 0;
			vehiId = 0;
			fromTime = 0;
			toTime = 0;
			travelTime = 0;
			travelDistance = 0;
			delay = 0;
			desireSpeed = 0;
		}
	};

	/*
	行程时间集计数据
	*/
	struct TESSINTERFACES_EXPORT VehiTravelAggregated {
		/*检测器ID*/
		long detectedId;
		/*时间段*/
		int timeId;
		/*起始时间(秒)*/
		long fromTime;
		/*结束时间(秒)*/
		long toTime;
		/*平均行程时间(秒)*/
		qreal avgTravelTime;
		/*平均行程距离(米)*/
		qreal avgTravelDistance;
		/*平均延误*/
		qreal avgDelay;
		/*车辆数*/
		int vehiCount;

		VehiTravelAggregated() {
			detectedId = 0;
			timeId = 0;
			fromTime = 0;
			toTime = 0;
			avgTravelTime = 0;
			avgTravelDistance = 0;
			avgDelay = 0;
			vehiCount = 0;
		}
	};

	/*
	信号灯组相位颜色，用于表示当前信号灯相位灯色等数据
	*/
	struct TESSINTERFACES_EXPORT SignalPhaseColor {
		/*信号灯组ID*/
		long signalGroupId;
		/*相位序号*/
		long phaseNumber;
		/*颜色，"R":红色，"Y":黄, "G":绿色, "gray"：灰色*/
		QString color;
		/*当前颜色设置时间(毫秒）*/
		long mrIntervalSetted;
		/*当前颜色已持续时间(毫秒)*/
		long mrIntervalByNow;
	};

	/*
	信号控制
	*/
	struct TESSINTERFACES_EXPORT SignalContralParam {
		/*灯组ID*/
		long signalGroupId;
		/*起始时间*/
		long fromTime;
		/*结束时间*/
		long toTime;
		/*周期(秒)*/
		int period;
		/*协调相位序号*/
		int crdinatedPhaseNum;
		/*协调相位差(秒)*/
		int crdinatedPhaseDiff;
		/*黄色时长*/
		int yellowInterval;
		/*全红时长*/
		int redInterval;
		//各相位绿时(秒),按相位序号顺序排列
		QList<int> mlPhaseGreen;
		SignalContralParam() {
			signalGroupId = 0;
			fromTime = 1;
			toTime = 3600;
			period = 60;
			crdinatedPhaseNum = 1;
			crdinatedPhaseDiff = 0;
			yellowInterval = 3;
			redInterval = 2;
		}
	};

	/*
	一条路段某个时段各车道限制车型
	*/
	struct TESSINTERFACES_EXPORT LimitLaneByVehiType {
		/*路段ID*/
		long linkId;
		/*车型*/
		long vehiType;
		/*起始时间 单位秒*/
		long fromTime;
		/*结束时间 单位秒*/
		long toTime;
		/*限行车道*/
		QList<int> mlLaneNumber;
	};

	/*
	车道最高速度(km/h)
	*/
	struct TESSINTERFACES_EXPORT LimitSpeedByLane {
		/*车道编号*/
		int laneNumber;
		/*限速，即最高速度：像素/秒*/
		qreal limitSpeed;
		LimitSpeedByLane() {}
		LimitSpeedByLane(int number, qreal speed) {
			laneNumber = number;
			limitSpeed = speed;
		}
	};

	/*
	一条路段某个时段各车道最高速度(km/h)
	*/
	struct TESSINTERFACES_EXPORT LimitSpeedByLanes {
		/*路段ID*/
		long linkId;
		/*起始时间 单位秒*/
		long fromTime;
		/*结束时间 单位秒*/
		long toTime;
		QList<LimitSpeedByLane> mlLimitSpeedByLane;
	};

	/*
	跟驰模型参数
	*/
	struct TESSINTERFACES_EXPORT FollowingModelParam {
		/*车辆类型，机动车或非机动车*/
		MotorOrNonmotor vtype;
		/*安全时距，单位：s */
		qreal safeInterval;
		/*安全距离，单位：m */
		qreal safeDistance;
		qreal alfa;
		qreal beit;
		FollowingModelParam()
		{
			vtype = MotorOrNonmotor::Motor;
			safeInterval = 1.5;
			safeDistance = 2.0;
			alfa = 4;
			beit = 2;
		}
	};

	/*
	动态创建车辆基本参数
	*/
	struct TESSINTERFACES_EXPORT DynaVehiParam {
		/*名称，可以是车牌或其它标识*/
		QString name;
		/*路段ID*/
		long roadId;
		/*车辆类型编码*/
		long vehiTypeCode;
		/*车道编号，从0开始*/
		int laneNumber;
		/*连接段目标车道编号*/
		int toLaneNumber;
		/*距车道起点距离：m */
		qreal dist;
		/*当前速度 单位：m/s */
		qreal speed;
		/*颜色：RGB，举例："#EE0000" */
		QString color;
		/*其它信息*/
		QJsonObject others;

		DynaVehiParam()
		{
			roadId = 0;
			laneNumber = 0;
			toLaneNumber = -1;
			vehiTypeCode = 1;
			dist = 0;
			speed = 0;
		}
	};

	/*
	动态创建车辆基本参数，附带时间戳
	*/
	struct TESSINTERFACES_EXPORT DynsVehiWithTimestamp {
		qint64 mrTimestamp;
        QList<DynaVehiParam> mlDynaVehi;
		DynsVehiWithTimestamp()
		{
			mrTimestamp = 0;
		}
	};

	/*
	动态创建施工区参数
	*/
	struct TESSINTERFACES_EXPORT DynaRoadWorkZoneParam
	{
		/*道路ID*/
		long roadId;
		/*施工区名称*/
		QString name;
		/*位置，距路段或连接段起点距离，单位米*/
		qreal location;
		/*施工区长度，单位米*/
		qreal length;
		/*车辆经过施工区的最大车速*/
		qreal limitSpeed;
		/*施工区施工时长，单位秒*/
		long duration;
		/*施工区起始车道序号列表，如果mlToLaneNumber为空，则施工区在路段上*/
		QList<int> mlFromLaneNumber;
		/*施工区目标车道序号列表，如果不空，则施工区在连接段上*/
		QList<int> mlToLaneNumber;

		DynaRoadWorkZoneParam()
		{
			/*道路ID*/
			roadId = -1;
			/*位置，距路段或连接段起点距离，单位米*/
			location = 0;
			/*施工区长度，单位米*/
			length = 50;
			/*车辆经过施工区的最大车速*/
			limitSpeed = 50;
			/*施工区施工时长，单位秒*/
			duration = 3600;
		}
	};

	/*
	动态创建事故区参数
	*/
	struct TESSINTERFACES_EXPORT DynaAccidentZoneParam
	{
		/*道路ID*/
		long roadId;
		/*位置，距路段或连接段起点距离，单位米*/
		qreal location;
		/*施工区长度，单位米*/
		qreal length;
		/*施工区起始车道序号列表，如果mlToLaneNumber为空，则施工区在路段上*/
		QList<int> mlFromLaneNumber;
		/*施工区目标车道序号列表，如果不空，则施工区在连接段上*/
		QList<int> mlToLaneNumber;

		//======以下是事故管理相关属性
		//事故等级，分4级，默认为未定等级(0级)持续时间未定，事故区不会自动移除，一般事故(1级)持续时间10分钟，普通事故(2)级持续时间1小时，重大事故(3级)持续时间3小时
		int level;
		//事故持续时间，单位秒。如果值为0，事故持续时间由事故等级决定，大于0则由此值决定
		long duration;
		//是否需要救援，如果为-1，由事故等级决定，重大事故需要求援，如为0不需救援，如果为1需要救援
		int needRescue;
		//救援时间
		long rescueTime;
		//救援车辆发车时间距事故产生的时间，单位秒，默认60秒
		long waitTimeBeforeRescue;

		DynaAccidentZoneParam()
		{
			roadId = 0;
			/*位置，距路段或连接段起点距离，单位米*/
			location = 0;
			/*施工区长度，单位米*/
			length = 0;

			//======事故管理属性默认值
			/*事故区时长，单位秒*/
			duration = 0;
			level = 0;
			needRescue = -1;
			waitTimeBeforeRescue = 60;
		}
	};

	/*
	一个或一次数据来源里保存的所有发车点一次发车间隔信息 sourceKey:来源(如：文件路径)
	*/
	struct TESSINTERFACES_EXPORT DispatchWithSource {
		QString sourceKey;
		QList<Online::DispatchInterval> mlDispatchInterval;
		DispatchWithSource() {
		}
		DispatchWithSource(QString key, QList<Online::DispatchInterval>& lDi) {
			sourceKey = key;
			mlDispatchInterval << lDi;
		}
	};

	/*
	一个或一次数据来源里保存的所有决策点在一个时间间隔的路径流量分配信息 sourceKey:来源(如：文件路径)
	*/
	struct TESSINTERFACES_EXPORT FlowRatioWithSource {
		QString sourceKey;
		QList<DecipointFlowRatioByInterval> mlDecipointFlowRatioByInterval;
		FlowRatioWithSource() {
		}
		FlowRatioWithSource(QString& key, QList<DecipointFlowRatioByInterval>& lRfi) {
			sourceKey = key;
			mlDecipointFlowRatioByInterval << lRfi;
		}
	};

	/*
	一个或一次数据来源里保存的所有信号灯组在一个时间间隔各相位灯色信息 sourceKey:来源(如：文件路径)
	*/
	struct TESSINTERFACES_EXPORT SignalContralWithSource {
		QString sourceKey;
		QList<SignalContralParam> mlSignalContral;
		SignalContralWithSource() {
		}
		SignalContralWithSource(QString& key, QList<SignalContralParam>& lSC) {
			sourceKey = key;
			mlSignalContral << lSC;
		}
	};
}

#endif