/********************************************************************************
* 车辆接口，由TESS NG实现，用户可以借此调用接口方法，获取车辆一些基本属性，以及运动过程中的一些动态数据，
* 还可以调用一些接口方法对车辆进行初始化，设置动态信息
*********************************************************************************/

#ifndef IVEHICLE_H
#define IVEHICLE_H

#include "tessinterfaces_global.h"

#include <QObject>
#include <QPicture>

class Vehicle;
class IVehicleDriving;
class ILink;
class ILane;
class IRouting;

class TESSINTERFACES_EXPORT IVehicle
{
public:
	//车辆ID
	virtual long id();
	//车辆名称
	virtual QString name();
	//起始路段
	virtual ILink *startLink();
	//起始仿真时间
	virtual long startSimuTime();
	//道路，如果在路段上返回ILink, 如果在连接段上返回IConnector
	virtual void *road();
	//道路ID
	virtual long roadId();
	//当前道路是否路段，如果不是则在连接段上
	virtual bool roadIsLink();
	//道路名
	virtual QString roadName();
	//长度，单位：像素
	virtual qreal length();
	//车道ID
	virtual long laneId();
	//连接段的去向路段上车道ID
	virtual long toLaneId();
	//获取当前车道，如果在“车道连接”上，获取的是“车道连接”的上游车道
	virtual ILane *lane();
	//获取当前“车道连接”的下游车道，如果当前不在“车道连接”上，返回空指针
	virtual ILane *toLane();
	//当前仿真计算批次
	virtual long currBatchNumber();
	//道路类型，即路段或连接段
	virtual int roadType();
	//车道或车道连接中心线内点集
	virtual QList<QPointF> lLaneObjectVertex();
	//车辆所在道路最大限速
	virtual qreal limitMaxSpeed();
	//车辆所在道路最小限速
	virtual qreal limitMinSpeed();

	virtual long vehicleTypeCode();
	virtual QString vehicleTypeName();
	virtual IVehicleDriving* vehicleDriving();
	virtual void driving();
	virtual qreal initSpeed(qreal speed = -1);
	//在路段上用车道序号、距起点距离、当前速度进行初始化
	virtual void initLane(int laneNumber, qreal dist = -1, qreal speed = -1);
	//在连接段上用车道连接起始车道序号和目标车道序号以及距起点距离、当前速度进行初始化
	virtual void initLaneConnector(int laneNumber, int toLaneNumber, qreal dist = -1, qreal speed = -1);
	virtual void setVehiType(int code);
	//设置车辆长度，单位：像素, bRestrictWidth:是否同比例约束宽度
	virtual void setLength(qreal len, bool bRestWidth = false);
	//是否使用缓存
	virtual void useCache(bool bCache);
	//当前路径
	virtual IRouting *routing();
	//车辆
	virtual Vehicle *vehicle();
	//当前点位
	virtual QPointF pos();
	//当前高程
	virtual qreal zValue();
	//当前加速度
	virtual qreal acce();
	//当前速度
	virtual qreal currSpeed();
	//当前角度
	virtual qreal angle();
	//车辆图
	virtual QPicture picture();
	//是否已启动
	virtual bool isStarted();

	//前车
	virtual IVehicle *vehicleFront();
	//后车
	virtual IVehicle *vehicleRear();
	//左前车
	virtual IVehicle *vehicleLFront();
	//左后车
	virtual IVehicle *vehicleLRear();
	//右前车
	virtual IVehicle *vehicleRFront();
	//右后车
	virtual IVehicle *vehicleRRear();
	/* 前车距离 */
	virtual qreal vehiDistFront();
	/* 前车速度*/
	virtual qreal vehiSpeedFront();
	/* 后车距*/
	virtual qreal vehiDistRear();
	/* 后车速度*/
	virtual qreal vehiSpeedRear();
	/* 距前车时距 */
	virtual qreal vehiHeadwayFront();
	/* 距后车时距 */
	virtual qreal vehiHeadwaytoRear();
	/* 相邻左车道前车距离 */
	virtual qreal vehiDistLLaneFront();
	/* 相邻左车道前车速度 */
	virtual qreal vehiSpeedLLaneFront();
	/* 相邻左车道后车距离 */
	virtual qreal vehiDistLLaneRear();
	/* 相邻左车道后车速度 */
	virtual qreal vehiSpeedLLaneRear();
	/* 相邻右车道前车距离 */
	virtual qreal vehiDistRLaneFront();
	/* 相邻右车道前车速度 */
	virtual qreal vehiSpeedRLaneFront();
	/* 相邻右车道后车距离 */
	virtual qreal vehiDistRLaneRear();
	/* 相邻右车道后车速度 */
	virtual qreal vehiSpeedRLaneRear();
	//获取车辆由方向和长度决定的四个拐角构成的多边型
	virtual QPolygonF boundingPolygon();
	//设置标签表示的状态
	virtual void setTag(int tag);
	//获取标签表示的状态
	virtual int tag();
	//设置动态信息
	virtual void setDynaInfo(void *pDynaInfo);
	//获取动态信息
	virtual void *dynaInfo();

	//====设置插件方法调用步长，即多少个计算周期调用一次，以下方法的目的在于python环境下设置指定方法调用步长，减少不必要的对python过载方法调用频次，以减少效率的损失
	//设置是否允许客户对于车辆的绘制
	virtual void setIsPermitForVehicleDraw(bool bDraw);
	//每steps个计算周期调用一次 CustomerSimulator::beforeNextPoint(...)方法  
	virtual void setSteps_beforeNextPoint(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::nextPoint(...)方法  
	virtual void setSteps_nextPoint(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::afterNextPoint(...)方法  
	virtual void setSteps_afterNextPoint(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::isStopDriving(...)方法  
	virtual void setSteps_isStopDriving(int steps);

	//每steps个计算周期调用一次 CustomerSimulator::judgeIfOnTargetLane(...)方法  
	virtual void setSteps_judgeIfOnTargetLane(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::reCalcdesirSpeed(...)方法  
	virtual void setSteps_reCalcdesirSpeed(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::calcMaxLimitedSpeed(...)方法  
	virtual void setSteps_calcMaxLimitedSpeed(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::calcLimitedLaneNumber(...)方法  
	virtual void setSteps_calcLimitedLaneNumber(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::calcSpeedLimitByLane(...)方法  
	virtual void setSteps_calcSpeedLimitByLane(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::isCalcDistToReduceArea(...)方法  
	virtual void setSteps_isCalcDistToReduceArea(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::calcDistToEventObj(...)方法  
	virtual void setSteps_calcDistToEventObj(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::calcChangeLaneSafeDist(...)方法  
	virtual void setSteps_calcChangeLaneSafeDist(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::reCalcToLeftLane(...)方法  
	virtual void setSteps_reCalcToLeftLane(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::reCalcToRightLane(...)方法  
	virtual void setSteps_reCalcToRightLane(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::reCalcToLeftFreely(...)方法  
	virtual void setSteps_reCalcToLeftFreely(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::reCalcToRightFreely(...)方法  
	virtual void setSteps_reCalcToRightFreely(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::afterCalcTracingType(...)方法  
	virtual void setSteps_afterCalcTracingType(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::beforeMergingToLane(...)方法  
	virtual void setSteps_beforeMergingToLane(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::reSetFollowingType(...)方法  
	virtual void setSteps_reSetFollowingType(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::calcAcce(...)方法  
	virtual void setSteps_calcAcce(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::reSetAcce(...)方法  
	virtual void setSteps_reSetAcce(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::reSetSpeed(...)方法  
	virtual void setSteps_reSetSpeed(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::reCalcAngle(...)方法  
	virtual void setSteps_reCalcAngle(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::recentTimeOfSpeedAndPos(...)方法  
	virtual void setSteps_recentTimeOfSpeedAndPos(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::travelOnChangingTrace(...)方法  
	virtual void setSteps_travelOnChangingTrace(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::leaveOffChangingTrace(...)方法  
	virtual void setSteps_leaveOffChangingTrace(int steps);
	//每steps个计算周期调用一次 CustomerSimulator::beforeNextRoad(...)方法  
	virtual void setSteps_beforeNextRoad(int steps);

private:
	
};

#endif // IVEHICLE_H