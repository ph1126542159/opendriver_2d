/********************************************************************************
* 驾驶行为接口，由TESS NG实现，用户可以借此调用接口方法，获取驾驶过程动态数据，
* 还可以调用一些接口方法对改变原有的驾驶行为或参数
*********************************************************************************/

#ifndef IVEHICLEDRIVING_H
#define IVEHICLEDRIVING_H

#include "tessinterfaces_global.h"

#include <QObject>
#include <QGraphicsItem>

class IVehicle;
class IRouting;

class TESSINTERFACES_EXPORT IVehicleDriving
{
public:
	virtual IVehicle *vehicle();
	//获取随机数
	virtual long getRandomNumber();
	virtual bool nextPoint();
	//当前车速为零持续时间(毫秒)
	virtual long zeroSpeedInterval();
	//当前是否在路径上
	virtual bool isOnRouting();
	//当前是否在路段上且有决策点
	virtual bool isHavingDeciPointOnLink();
	//停止运行
	virtual void stopVehicle();

	virtual int followingType();
	//初始化轨迹
	virtual void initTrace();
	//设置轨迹
	virtual void setTrace(QList<QPointF> &lPoint);
	//计算轨迹长度
	virtual void calcTraceLength();
	//返回轨迹类型
	virtual int tracingType();
	//设置轨迹类型
	virtual void setTracingType(int type);
	//返回车辆角度
	virtual qreal angle();
	//设置车辆角度
	virtual void setAngle(qreal angle);
	//期望速度
	virtual qreal desirSpeed();
	//返回当前所在路段或连接段
	virtual QGraphicsItem *getCurrRoad();
	//下一路段或连接段
	virtual QGraphicsItem *getNextRoad();

	//与目标车道编号的差值
	virtual int differToTargetLaneNumber();
	//左变道
	virtual void toLeftLane();
	//右变道
	virtual void toRightLane();
	//车道序号
	virtual int laneNumber();
	//设置车道序号
	virtual void setLaneNumber(int number);
	//设置当前路段已行驶的距离
	virtual void setCurrDistanceInRoad(qreal dist);
	//当前路段已行驶距离
	virtual qreal currDistanceInRoad();
	//设置当前分段已行驶的距离
	virtual void setCurrDistanceInSegment(qreal dist);
	//当前分段已行驶距离
	virtual qreal currDistanceInSegment();
	//设置分段序号
	virtual void setSegmentIndex(int index);
	//设置当前已行驶总里程
	virtual void setVehiDrivDistance(qreal dist);
	//当前已行驶总里程
	virtual qreal getVehiDrivDistance();
	//设置曲化轨迹上行驶的距离
	virtual void setCurrDistanceInTrace(qreal dist);
	//设置曲化轨迹上的分段序号
	virtual void setIndexOfSegmInTrace(int index);
	//设置是否改变轨迹
	virtual void setChangingTracingType(bool b);
	//设置当前车速
	virtual void setSpeed(qreal speed);
	//当前时间段移动距离
	virtual qreal currDistance();
	virtual void setX(qreal posX);
	virtual void setY(qreal posY);
	//设置路径
	virtual void setRouting(void *pRouting);
	/*设置跟驰状态*/
	virtual void setFollowingType(int followingType, int interval = 0, IVehicle *pIVehicleNegotiated = 0);
	virtual IVehicle* getVehicleNegotiated();
	/*变轨点集*/
	virtual QList<QPointF> changingTrace();
	/*变轨长度*/
	virtual qreal changingTraceLength();
	/*在车道或车道连接上到终端距离 fromVehiHead:是否从车头计算*/
	virtual qreal distToEndpoint(bool fromVehiHead = false);
	//设置路径，外界设置的路径不一定有决策点，可能是临时创建的，如果车辆不在此路径上则设置不成功并返回false
	virtual bool setRouting(IRouting *pRouting);
	//当前路径
	virtual IRouting* routing();
private:
	IVehicle *mpVehicle;
};

#endif // IVEHICLEDRIVING_H