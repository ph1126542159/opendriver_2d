/********************************************************************************
* 路段接口，由TESS NG实现，用户可以借此调用接口方法，获取路段一些基本属性
*********************************************************************************/

#ifndef __ILink__
#define __ILink__

#include "tessinterfaces_global.h"

#include "ILane.h"

#include <QVector3D>

class IRouting;

class TESSINTERFACES_EXPORT  ILink
{
public:
	/*路段ID	*/
	virtual long id();
	//路段长度
	virtual qreal length();
	//路段宽度
	virtual qreal width();
	//路段名
	virtual QString name();
	//车道数
	virtual int laneCount();
	//限速 千米/小时
	virtual double limitSpeed();
	//设置最高限速
	virtual void setLimitSpeed(qreal speed);
	//最小速度 千米/小时
	virtual qreal minSpeed();
	//车道接口列表
	virtual QList<ILane*> lanes();
	//路段中心线断点集
	virtual QList<QPointF> centerBreakPoints();
	//路段左侧线断点集
	virtual QList<QPointF> leftBreakPoints();
	//路段右侧线断点集
	virtual QList<QPointF> rightBreakPoints();
	//路段中心线断点(三维)集
	virtual QList<QVector3D> centerBreakPoint3Ds();
	//路段左侧线断点(三维)集
	virtual QList<QVector3D> leftBreakPoint3Ds();
	//路段右侧线断点(三维)集
	virtual QList<QVector3D> rightBreakPoint3Ds();
};

#endif