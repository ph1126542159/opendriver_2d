/********************************************************************************
* 信号灯接口，由TESS NG实现，用户可以借此调用接口方法，获取信号灯一些基本属性
*********************************************************************************/

#ifndef ISIGNALLAMP_H
#define ISIGNALLAMP_H

#include "tessinterfaces_global.h"

#include <QObject>
#include <QColor>

class TESSINTERFACES_EXPORT ISignalLamp
{
public:
	//获取信号灯ID
	virtual long id();
	//设置灯色，colorStr为"红"、"绿"、"黄"、"灰"，或者"R"、“G”、“Y”、“gray”分别表示"红"、"绿"、"黄"、"灰"
	virtual void setLampColor(QString colorStr);
	//color：共有四种颜色可选，分别是QColor(Qt::red)、QColor(Qt::yellow)、 QColor(Qt::green)、QColor(Qt::gray)，分别代表红、黄、绿、灰四种颜色
	virtual void setLampColor(QColor color);
	//获取相位ID
	virtual long phaseId();
	//获取信号灯组ID
	virtual long signalGroupId();
private:
	
};

#endif // ISIGNALLAMP_H