/********************************************************************************
* 连接段接口，由TESS NG实现，用户可以借此调用接口方法，获取连接段一些基本属性
*********************************************************************************/

#ifndef __IConnector__
#define __IConnector__

#include "tessinterfaces_global.h"

class ILink;
class ILaneConnector;

class TESSINTERFACES_EXPORT IConnector
{
public:
	//连接段ID
	virtual long id();
	//上游路段
	virtual ILink* fromLink();
	//下游路段
	virtual ILink* toLink();
	//限速 千米/小时
	virtual qreal limitSpeed();
	//最小速度 千米/小时
	virtual qreal minSpeed();
	//车道连接列表
	virtual QList<ILaneConnector*> laneConnectors();
};

#endif