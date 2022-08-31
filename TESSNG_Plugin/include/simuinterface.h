/********************************************************************************
* TESS NG仿真运算层接口，此接口由TESS NG实现，用户可以通过此接口启动停止仿真，
* 在仿真过程获取所有车辆运行状态、指定车辆运行轨迹、几种检测器检测数据等
*********************************************************************************/

#ifndef SIMUINTERFACE_H
#define SIMUINTERFACE_H

#include <QObject>

#include "tessinterfaces_global.h"
#include "Plugin/_datastruct.h"

class CustomerSimulator;
class IVehicleSupervisor;
class IVehicleDrivingManagerTask;
class IVehicleDrivingTask;
class IVehicle;

class TESSINTERFACES_EXPORT SimuInterface
{
public:
	virtual IVehicleDrivingManagerTask* vehicleDrivingManagerTask();
	virtual QList<IVehicleDrivingTask*> vehicleDrivingTasks();

	//仿真时间是否由现实时间确定
	virtual bool byCpuTime();
	//设置是否由现实时间(处理器运算时间)确定仿真时间,如果正在仿真计算则不进行设置并返回false，否则设置参数并返回true
	virtual bool setByCpuTime(bool bByCpuTime);
	//启动仿真
	virtual void startSimu();
	//暂停仿真
	virtual void pauseSimu();
	//结束仿真
	virtual void stopSimu();
	//仿真是否在进行
	virtual bool isRunning();
	//仿真是否处于暂停状态
	virtual bool isPausing();
	//仿真精度
	virtual int simuAccuracy();
	//设置仿真精度
	virtual void setSimuAccuracy(int accuracy);
	//加速倍数
	virtual int acceMultiples();
	//设置加速倍数
	virtual void setAcceMultiples(int multiples);
	//实际加速倍数
	virtual qreal acceMultiplesReally();
	//当前批次
	virtual long batchNumber();
	//指定批次的实时时间t
	virtual qint64 timeOnBatchNumber(long batchNumber);
	//当前批次实际时间
	virtual qreal batchIntervalReally();
	//仿真开始的现实时间
	virtual qint64 startMSecsSinceEpoch();
	//仿真结束的现实时间
	virtual qint64 stopMSecsSinceEpoch();
	//当前已仿真时间
	virtual long simuTimeIntervalWithAcceMutiples();
	//仿真到指定批次时总延误(毫秒)
	virtual long delayTimeOnBatchNumber(long batchNumber);
	//车辆总数
	virtual long vehiCountTotal();
	//路网上运行的车辆数
	virtual long vehiCountRunning();
	//根据车辆ID获取车辆对象
	virtual IVehicle* getVehicle(long vehiId);
	//在运行所有车辆
	virtual QList<IVehicle*> allVehiStarted();
	//所有车辆
	virtual QList<IVehicle*> allVehicle();
	//获取所有在运行车辆状态，包括轨迹
	virtual QList<Online::VehicleStatus> getVehisStatus();
	//获取指定车辆运行轨迹
	virtual QList<Online::VehiclePosition> getVehiTrace(long vehiId);
	//获取当前所有信号灯组相位颜色
	virtual QList<Online::SignalPhaseColor> getSignalPhasesColor();
	//获取当前仿真时间完成穿越采集器的所有车辆信息
	virtual QList<Online::VehiInfoCollected> getVehisInfoCollected();
	//获取最近集计时间段内采集器采集的所有车辆集计信息
	virtual QList<Online::VehiInfoAggregated> getVehisInfoAggregated();
	//获取当前仿真时间排队计数器计数的车辆排队信息
	virtual QList<Online::VehiQueueCounted> getVehisQueueCounted();
	//获取最近集计时间段内排队计数器集计数据
	virtual QList<Online::VehiQueueAggregated> getVehisQueueAggregated();
	//获取当前仿真时间行程时间检测器完成的行程时间检测信息
	virtual QList<Online::VehiTravelDetected > getVehisTravelDetected();
	//获取最近集计时间段内行程时间检测器集计数据
	virtual QList<Online::VehiTravelAggregated> getVehisTravelAggregated();
	//动态创建车辆
	virtual IVehicle* createGVehicle(Online::DynaVehiParam dynaVehi);
	//停止车辆运行
	virtual void stopVehicleDriving(IVehicle* pVehicle);

	//主界面工具栏按钮功能
	//暂停或恢复仿真
	virtual void pauseSimuOrNot();

	virtual QList<IVehicle*> vehisInLink(long linkId);
	virtual QList<IVehicle*> vehisInLane(long laneId);
	virtual QList<IVehicle*> vehisInConnector(long connectorId);
	virtual QList<IVehicle*> vehisInLaneConnector(long connectorId, long fromLaneId, long toLaneId);

	//排队计数器最近一次排队信息
	virtual bool queueRecently(long queueCounterId, qreal& queueLength, int& vehiCount);

private:

};

#endif // SIMUINTERFACE_H