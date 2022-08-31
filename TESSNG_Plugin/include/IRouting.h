/********************************************************************************
* 路径接口，由TESS NG实现，用户可以借此调用接口方法，获取路径一些基本属性
*********************************************************************************/

#ifndef __IRouting__
#define __IRouting__

#include "tessinterfaces_global.h"

#include <QGraphicsItem>

class ILink;

class TESSINTERFACES_EXPORT IRouting
{
public:
	/*路径ID*/
	virtual long id();
	/*计算路径长度*/
	virtual qreal calcuLength();

	/* 根据所给道路判断是否在当前路径上*/
	virtual bool contain(QGraphicsItem* pRoad);

	/* 根据所给道路求下一条道路, pRoad是路段或连接段*/
	virtual QGraphicsItem* nextRoad(QGraphicsItem* pRoad);

	/* 获取路段序列*/
	virtual QList<ILink*> getLinks();
};

#endif