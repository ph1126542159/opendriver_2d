#ifndef __PyCustomerNet__
#define __PyCustomerNet__

#include "customernet.h"
#include "_objtypes.h"

class TESSINTERFACES_EXPORT PyCustomerNet : public CustomerNet
{
public:
	PyCustomerNet() {}

	//路网文件后缀
	bool netFileSuffix(QString &suffix) override;
	//路网文件后缀
	virtual bool ref_netFileSuffix(objstring &ref_suffix);
	//添加用户设计的表
	virtual QMap<QString, QString> customerTableDDL() override;
	/*插入用户插件创建的表数据*/
	virtual void insertCustomerData(/*QSqlQuery &query*/) override;
	//删除用户插件创建的表数据
	virtual void deleteCustomerData(/*QSqlQuery &query*/) override;
	//加载路网前的准备
	virtual void beforeLoadNet() override;
	//加载完路网后的行为
	virtual void afterLoadNet() override;
	//从场景中移除插件创建的对象
	virtual bool removeItemFromScene(CustomerGraphicsObject *pItem) override;
	//路段类型
	virtual bool linkType(QList<QString> &lType) override;
	//车道类型
	virtual bool laneType(QList<QString> &lType) override;
	//创建车道
	virtual bool linkBuildGLanes(ILink *pILink) override;
	//曲化精度
	bool curvaturePrecision(int itemType, long itemId, qreal &extend1, qreal &extend2, qreal &precision) override;
	//曲化精度
	virtual bool ref_curvaturePrecision(int itemType, long itemId, objreal &ref_extend1, objreal &ref_extend2, objreal &ref_precision);
	//是否允许调用客户绘制逻辑，默认为true。本方法的目的是：在python环境减少不必要的对python代码调用，消除对运行效率的负面影响
	virtual bool isPermitForCustDraw();
	//绘制路网元素
	virtual bool paint(int itemType, long itemId, QPainter *painter) override;
	//路段brush颜色
	virtual bool linkBrushAndPen(long linkId, QBrush &brush, QPen &pen) override;
	//车道brush颜色
	virtual bool laneBrushAndPen(long laneId, QBrush &brush, QPen &pen) override;
	//面域brush颜色
	virtual bool connectorAreaBrushAndPen(long connAreaId, QBrush &brush, QPen &pen) override;
	//写标签，按照给定的属性名和字体大小（米）,outPropName是牧举类型GraphicsItemPropName
	void labelNameAndFont(int itemType, long itemId, int &outPropName, qreal &outFontSize) override;
	//写标签，按照给定的属性名和字体大小（米）
	virtual void ref_labelNameAndFont(int itemType, long itemId, objint &ref_outPropName, objreal &ref_outFontSize);
	//是否绘标签
	//virtual bool isDrawLabel(int itemType, long itemId) override;
	//是否画路段中心线
	virtual bool isDrawLinkCenterLine(long linkId) override;
	//是否绘路段四个拐角
	virtual bool isDrawLinkCorner(long linkId) override;
	//是否画车道中心线
	virtual bool isDrawLaneCenterLine(long laneId) override;

	//QGraphicsView的keyReleaseEvent事件后的行为
	virtual void afterViewKeyReleaseEvent(QKeyEvent *event) override;
	//QGraphicsView的mouseDoubleClickEvent事件后的行为
	virtual void afterViewMouseDoubleClickEvent(QMouseEvent * event) override;
	//QGraphicsView的mouseMoveEvent事件后的行为
	virtual void afterViewMouseMoveEvent(QMouseEvent *event) override;
	//QGraphicsView的mousePressEvent事件后的行为
	virtual void afterViewMousePressEvent(QMouseEvent *event) override;
	//QGraphicsView的mouseReleaseEvent事件后的行为
	virtual void afterViewMouseReleaseEvent(QMouseEvent *event) override;
	//QGraphicsView的resizeEvent事件后的行为
	virtual void afterViewResizeEvent(QResizeEvent *event) override;
	//鼠标滚动事件响应
	virtual void afterViewWheelEvent(QWheelEvent *event) override;
	//滚动条移动事件后的行为
	virtual void afterViewScrollContentsBy(int dx, int dy) override;
};

#endif