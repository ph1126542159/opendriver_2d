/********************************************************************************
* 公交线路接口，由TESS NG实现，用户可以借此访问公交线路对象方法，获取公交线路一些基本信息
*********************************************************************************/

#ifndef __IBusLine__
#define __IBusLine__

#include "tessinterfaces_global.h"

#include <QObject>

class IBusStation;
class ILink;
class IBusStationLine;

class TESSINTERFACES_EXPORT IBusLine
{
public:
	// 线路ID
	virtual long id();
	//线路名称
	virtual QString name();
	/* 长度,单位：像素 */
	virtual double length();
	/* 发车间隔(秒) */
	virtual int dispatchFreq();
	/* 发车开始时间(秒) */
	virtual int dispatchStartTime();
	/* 发车结束时间(秒) */
	virtual int dispatchEndTime();
	/* 期望速度(km/h) */
	virtual qreal desirSpeed();
	/* 起始载客人数 */
	virtual int passCountAtStartTime();
	/* 公交线路经过的路段 */
	virtual QList<ILink*> links();
	//线路所有站点
	virtual QList<IBusStation*> stations();
	/* 公交站点线路，当前站点相关线路的上下客等参数 */
	virtual QList<IBusStationLine*> stationLines();
};

#endif