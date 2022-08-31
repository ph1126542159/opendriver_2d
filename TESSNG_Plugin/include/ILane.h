/********************************************************************************
* 车道接口，由TESS NG实现，用户可以借此调用接口方法，获取车道一些基本属性
*********************************************************************************/

#ifndef __ILane__
#define __ILane__

#include "tessinterfaces_global.h"

#include <QObject>
#include <QList>
#include <QPointF>

class ILink;

class TESSINTERFACES_EXPORT ILane
{
public:
	//车道ID
	virtual long id();
	//获取车道所在路段
	virtual ILink *link();
	//车道长度，单位：像素
	virtual qreal length();
	//序号，从0开始，自外侧往内侧
	virtual int number();
	//车道行为类型：“机动车道”、“非机动车道”、“公交专用道”等
	virtual QString actionType();
	//车道中心线点集
	virtual QList<QPointF> centerBreakPoints();
	//车道左侧线断点集
	virtual QList<QPointF> leftBreakPoints();
	//车道右侧线断点集
	virtual QList<QPointF> rightBreakPoints();
	//车道中心线断点(三维)集
	virtual QList<QVector3D> centerBreakPoint3Ds();
	//车道左侧线断点(三维)集
	virtual QList<QVector3D> leftBreakPoint3Ds();
	//车道右侧线断点(三维)集
	virtual QList<QVector3D> rightBreakPoint3Ds();
};

#endif