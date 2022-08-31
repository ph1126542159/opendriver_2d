/********************************************************************************
* TESS NG路网层接口，此接口由TESS NG实现，用户可以通过此接口访问路网，获取路网数据，创建路段、发车点等
*********************************************************************************/

#ifndef NETINTERFACE_H
#define NETINTERFACE_H

#include <QObject>

#include <QGraphicsScene>
#include <QPointF>
#include <QList>
#include <QMap>

#include "tessinterfaces_global.h"
#include "Plugin/_datastruct.h"

class CustomerNet;
class IRoadNet;
class ILink;
class Link;
class IConnector;
class Connector;
class IDispatchPoint;
class IDecisionPoint;
class CustomerGraphicsObject;
class IConnectorArea;
class IBusLine;
class IBusStation;
class IRouting;

/*
访问、控制路网的接口
*/
class TESSINTERFACES_EXPORT NetInterface
{
public:
	//打开路网文件
	virtual void openNetFle(QString filePath);
	//保存路网
	virtual void saveRoadNet();
	//路网文件路径
	virtual QString netFilePath();
	//路网对象
	virtual IRoadNet* roadNet();
	//场景
	virtual QGraphicsScene* graphicsScene();
	//视图
	virtual QGraphicsView* graphicsView();
	//场景中的比例尺
	virtual qreal sceneScale();
	//设置场景大小
	virtual void setSceneSize(qreal w, qreal h);
	//场景宽度
	virtual qreal sceneWidth();
	//场景高度
	virtual qreal sceneHeigth();
	//背景图
	virtual QByteArray backgroundMap();
	//路段ID集
	virtual QList<long> linkIds();
	//路段数
	virtual int linkCount();
	//路段集
	virtual QList<ILink*> links();
	//根据路段ID查找路段
	virtual ILink* findLink(long id);
	//连接段ID集
	virtual QList<long> connectorIds();
	//连接段数
	virtual int connectorCount();
	//连接段集
	virtual QList<IConnector*> connectors();
	//根据连接段ID查找连接段
	virtual IConnector* findConnector(long id);
	//发车点集
	virtual QList<IDispatchPoint*> dispatchPoints();
	//根据发车点ID查找发车点
	virtual IDispatchPoint* findDispatchPoint(long id);
	//决策点集
	virtual QList<IDecisionPoint*> decisionPoints();
	//根据决策点ID查找决策点
	virtual IDecisionPoint* findDecisionPoint(long id);
	//公交线路集
	virtual QList<IBusLine*> buslines();
	//根据公交线路ID查询公交线路
	virtual IBusLine* findBusline(long buslineId);
	//根据公交线路起始路段ID查询公交线路
	virtual IBusLine* findBuslineByFirstLinkId(long linkId);
	//公交站点集
	virtual QList<IBusStation*> busStations();
	//根据公交站点ID查询公交站点
	virtual IBusStation* findBusStation(long stationId);
	//面域集
	virtual QList<IConnectorArea*> allConnectorArea();
	//车道中心线断点集
	virtual QList<QPointF> laneCenterPoints(long laneId);
	//路段中心线断点集
	virtual QList<QPointF> linkCenterPoints(long linkId);
	//判断路段去向是否进入交叉口， 以面域是否存在多连接段以及当前路段与后续路段之间的角度为依据
	virtual bool judgeLinkToCross(long linkId);

	//根据路网元素名获取自增ID
	virtual long getIDByItemName(QString name);

	//路网基本属性
	virtual IRoadNet* netAttrs();

	//设置路网基本属性，name:路网名称，centerPoint:中心点坐标，默认为(0,0)，sourceType:数据g来源分类，otherAttrsJson:保存在json对象中的其它属性
	virtual IRoadNet* setNetAttrs(QString name, QString sourceType = QString("TESSNG"), QPointF centerPoint = QPointF(), QString backgroundUrl = QString(), QJsonObject otherAttrsJson = QJsonObject());

	//创建路段，lCenterPoint:路段中心线，laneCount:车道数
	virtual ILink* createLink(QList<QPointF> lCenterPoint, int laneCount, QString linkName = QString(), bool bAddToScene = true);

	//创建路段，lCenterV3:路段中心线，laneCount:车道数
	virtual ILink* createLink3D(QList<QVector3D> lCenterV3, int laneCount, QString linkName = QString(), bool bAddToScene = true);

	//创建路段，lCenterPoint:路段中心线，lLaneWidth:车道宽度列表
	virtual ILink* createLinkWithLaneWidth(QList<QPointF> lCenterPoint, QList<qreal> lLaneWidth, QString linkName = QString(), bool bAddToScene = true);

	//创建路段，lCenterV3:路段中心线，lLaneWidth:车道宽度列表
	virtual ILink* createLink3DWithLaneWidth(QList<QVector3D> lCenterV3, QList<qreal> lLaneWidth, QString linkName = QString(), bool bAddToScene = true);

	//创建路段，lCenterLineV3：路段中心点集(对应TESSNG路段中心点)，lanesWithPoints：车道点集的集合，linkName：路段名，默认为路段ID，bAddToScene：是否加入路网，默认true表示加入
	virtual ILink* createLink3DWithLanePoints(QList<QVector3D> lCenterLineV3, QList<QMap<QString, QList<QVector3D>>> lanesWithPoints, QString linkName = QString(), bool bAddToScene = true);

	//创建连接段
	virtual IConnector* createConnector(long fromLinkId, long toLinkId, QList<int> lFromLaneNumber, QList<int> lToLaneNumber, QString connName = QString(), bool bAddToScene = true);

	//创建连接段，创建连接段后将laneConnector中自动计算的断点集用参数laneConnectorWithPoints断点替换
	virtual IConnector* createConnector3DWithPoints(long fromLinkId, long toLinkId, QList<int> lFromLaneNumber, QList<int> lToLaneNumber, QList<QMap<QString, QList<QVector3D>>> laneConnectorWithPoints, QString connName = QString(), bool bAddToScene = true);
	//createConnectorWithPoints
	//创建发车点
	virtual IDispatchPoint* createDispatchPoint(ILink* pLink, QString dpName = QString(), bool bAddToScene = true);

	//创建车型组成
	virtual long createVehicleComposition(QString name, QList<Online::VehicleComposition> lVehiComp);

	//计算最短路径，返回路径上路段序列，pFromLink:起始路段，pToLink：目标路段
	virtual IRouting *shortestRouting(ILink* pFromLink, ILink* pToLink);
	//用连续通达的路段序列创建路径
	virtual IRouting *createRouting(QList<ILink*> lILink);

	//场景角度转换到图元角度
	virtual qreal angleToItem(qreal angle);
	//增加客户路网元素到场景
	virtual void addCustomerItem(CustomerGraphicsObject* pCustObj);
	//从场景移除客户路网元素
	virtual void removeCustomerItem(CustomerGraphicsObject* pCustObj);

private:

};

#endif // NETINTERFACE_H