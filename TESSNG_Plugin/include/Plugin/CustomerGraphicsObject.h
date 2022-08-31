/*****************************************************************************
* 客户自定义路网元素基础类
* 定义一些抽象方法，用户借此创建可视化元素并实现这些方法后，可以在插件环境下与TESS NG进行交互
******************************************************************************/

#ifndef __CustomerGraphicsObject__
#define __CustomerGraphicsObject__

#include "tessinterfaces_global.h"

#include <QGraphicsObject>
#include <QSqlQuery>
#include <QSqlError>

class TESSINTERFACES_EXPORT CustomerGraphicsObject : public QGraphicsObject
{
	Q_OBJECT

public:
	CustomerGraphicsObject(QGraphicsItem *parent = nullptr);
	~CustomerGraphicsObject();

	virtual int type() const override{ return QGraphicsItem::UserType + 1000; }
	virtual QString tableName() { return QString(); }
	virtual qreal distToStartPoint() { return 0; }
	virtual qreal length() { return 0; }
	virtual bool insertRecord(QSqlQuery &query) { return true; };
	virtual QGraphicsItem *road() { return nullptr; };
	virtual void adjust() {}
	virtual void detect() {}
	qreal calcFontSize(qreal fsize) const;
};

#endif