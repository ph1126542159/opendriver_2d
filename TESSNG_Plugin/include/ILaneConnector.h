/********************************************************************************
* 车道连接接口，由TESS NG实现，用户可以借此调用接口方法，获取车道连接一些基本属性
*********************************************************************************/

#ifndef __ILaneConnector__
#define __ILaneConnector__

#include <QObject>

#include "tessinterfaces_global.h"

class ILane;

class TESSINTERFACES_EXPORT ILaneConnector
{
public:
	//上游车道
	virtual ILane *fromLane();
	//下游车道
	virtual ILane *toLane();
	//车道长度，单位：像素
	virtual qreal length();
	//“车道连接”断点集
	virtual QList<QPointF> centerBreakPoints();
	//“车道连接”左侧线断点集
	virtual QList<QPointF> leftBreakPoints();
	//“车道连接”右侧线断点集
	virtual QList<QPointF> rightBreakPoints();
	//“车道连接”中心线断点(三维)集
	virtual QList<QVector3D> centerBreakPoint3Ds();
	//“车道连接”左侧线断点(三维)集
	virtual QList<QVector3D> leftBreakPoint3Ds();
	//“车道连接”右侧线断点(三维)集
	virtual QList<QVector3D> rightBreakPoint3Ds();
};

#endif