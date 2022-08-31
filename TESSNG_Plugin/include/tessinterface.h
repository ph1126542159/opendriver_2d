/********************************************************************************
* TESS NG顶层接口，此接口由TESS NG实现，用户可以通过此接口获取三个子接口、从内存加载插件、释放插件
*********************************************************************************/

#ifndef TESSINTERFACE_H
#define TESSINTERFACE_H

#include "tessinterfaces_global.h"

#include <QObject>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QtCore/qglobal.h>

class GraphicsView;
class GraphicsScene;
class GuiInterface;
class NetInterface;
class SimuInterface;
class TessPlugin;

/*
TESSNG 的顶级接口：NetInterface、SimuInterface、GuiInterface，下面有三个子接口，分别用于访问或控制路网、仿真过程和窗体。
*/
class TESSINTERFACES_EXPORT TessInterface : public QObject
{
	Q_OBJECT

public:
	TessInterface();
	~TessInterface();

	/*
	从内存加载插件
	*/
    virtual bool loadPluginFromMem(TessPlugin *pPlugin);

	/*
	卸载并释放插件
	*/
    virtual void releasePlugins();

    virtual GuiInterface *guiInterface();
    virtual NetInterface *netInterface();
    virtual SimuInterface *simuInterface();

private:

};

extern TessInterface TESSINTERFACES_EXPORT *gpTessInterface;
extern QMainWindow TESSINTERFACES_EXPORT *tessng(QString netFilePath = QString());

#endif // TESSINTERFACE_H