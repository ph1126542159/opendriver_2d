/********************************************************************************
* 管理线程接口，由TESS NG实现，用户可以借此调用接口方法，获取仿真过程一些数据，如加速倍数、是否正在运行等
*********************************************************************************/

#ifndef IVEHICLEDRIVINGMANAGERTASK_H
#define IVEHICLEDRIVINGMANAGERTASK_H

#include "tessinterfaces_global.h"
#include "Plugin/customersimulator.h"

#include <QObject>

class TESSINTERFACES_EXPORT IVehicleDrivingManagerTask
{
public:
	virtual bool finished();
	virtual bool running();
	virtual long currBatchNumber();
	virtual void setStopped(bool stopped);
	virtual bool isStoppeed();
	//实际加速倍数
	virtual qreal acceMultiplesReally();
	//指定批次实际时间
	virtual qint64 timeOnBatchNumber(long batchNumber);

	//当前批次实际用时
	virtual qreal batchIntervalReally();
};

#endif // IVEHICLEDRIVINGMANAGERTASK_H