/********************************************************************************
* 公交站点接口，由TESS NG实现，用户可以借此访问公交站点对象方法，获取公交线路一些基本信息
*********************************************************************************/

#ifndef __IBusStation__
#define __IBusStation__

#include "tessinterfaces_global.h"

#include "IBusStationLine.h"

#include <QObject>
#include <QList>

class ILink;
class ILane;
class IBusLine;

class TESSINTERFACES_EXPORT IBusStation
{
public:
	// 线路ID
	virtual long id();
	//线路名称
	virtual QString name();
	/* 公交站点所在车道序号 */
	virtual int laneNumber();
	/* 位置X */
	virtual qreal x();
	/* 位置Y */
	virtual qreal y();
	/* 长度 */
	virtual qreal length();
	/* 站点类型 1：路边式、2：港湾式 */
	virtual int stationType();
	/* 公交站点所在路段 */
	virtual ILink* link();
	/*公交站点所在车道*/
	virtual ILane* lane();
};

#endif