/********************************************************************************
* TESS NG用户交互接口，此抽象类由TESS NG自己实现，用户可基于API访问TESS NG主界面
*********************************************************************************/

#ifndef GUIINTERFACE_H
#define GUIINTERFACE_H

#include "tessinterfaces_global.h"

#include <QObject>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QtCore/qglobal.h>

class GraphicsView;
class GraphicsScene;

class TESSINTERFACES_EXPORT GuiInterface
{

public:
	//窗体
	virtual QMainWindow *mainWindow() { return nullptr; }
	virtual qreal winWidth() { return 0; }
	virtual qreal winHeight() { return 0; }
	virtual qreal winX() { return 0; }
	virtual qreal winY() { return 0; }

	//菜单
	virtual QMenuBar *menuBar() { return nullptr; }
	virtual QMenu *fileMenu() { return nullptr; }
	virtual QMenu *viewMenu() { return nullptr; }
	virtual QMenu *netMenu() { return nullptr; }
	virtual QMenu *editorMenu() { return nullptr; }
	virtual QMenu *simuMenu() { return nullptr; }
	virtual QMenu *aboutMenu() { return nullptr; }

	//工具栏
	virtual QToolBar *fileToolBar() { return nullptr; }
	virtual QToolBar *operToolBar() { return nullptr; }
	virtual QToolBar *netToolBar() { return nullptr; }
	virtual QToolBar *systemToolBar() { return nullptr; }
	virtual QToolBar *simuToolBar() { return nullptr; }
	virtual QToolBar *addToolBar( const QString& name ) { return nullptr; }
	virtual QAction* addWidgetToToolBar( QWidget* pWidget ) { return nullptr; }
	virtual void checkToolButtons(bool checked) {}
	virtual void checkToolButtons(bool checked, QAction *pException) {}

	//状态栏
	virtual QStatusBar *statusBar() { return nullptr; }

	//Action
	virtual QAction *actionNewFile() { return nullptr; }
	virtual QAction *actionOpenFile() { return nullptr; }
	virtual QAction *actionClose() { return nullptr; }
	virtual QAction *actionCloseAll() { return nullptr; }
	virtual QAction *actionSave() { return nullptr; }
	virtual QAction *actionSaveOther() { return nullptr; }
	virtual QAction *actionExit() { return nullptr; }

	virtual QAction *actionSelectRectangle() { return nullptr; }
	virtual QAction *actionCalcDistance() { return nullptr; }
	virtual QAction *actionZoomIn() { return nullptr; }
	virtual QAction *actionZoomOut() { return nullptr; }
	virtual QAction *actionZoomFullExtent() { return nullptr; }
	virtual QAction *actionNullGMapTool() { return nullptr; }
	virtual QAction *actionPan() { return nullptr; }

	virtual QAction *actionRun() { return nullptr; }
	virtual QAction *actionStop() { return nullptr; }
	virtual QAction *actionPause() { return nullptr; }
	virtual QAction *actionBusLine() { return nullptr; }
	virtual QAction *actionBusStation() { return nullptr; }
	virtual QAction *actionSignalGroup() { return nullptr; }
	virtual QAction *actionSignalLamp() { return nullptr; }
	virtual QAction *actionVehicleType() { return nullptr; }
	virtual QAction *actionVehicleComposition() { return nullptr; }
	virtual QAction *actionChangeLaneParam() { return nullptr; }
	virtual QAction *actionTracingParam() { return nullptr; }
	virtual QAction *actionDrivInfoCollecter() { return nullptr; }
	virtual QAction *actionQueueCounter() { return nullptr; }
	virtual QAction *actionTravelDetector() { return nullptr; }
	virtual QAction *actionSimuConfig() { return nullptr; }
	virtual QAction *actionEvalPubtrans() { return nullptr; }

	virtual QAction *actionSelectAllGLink() { return nullptr; }
	virtual QAction *actionSelectAllGConnector() { return nullptr; }
	virtual QAction *actionSelectAllGBusLine() { return nullptr; }
	virtual QAction *actionSelectAllGDeciPoint() { return nullptr; }
	virtual QAction *actionSelectAllGBusStation() { return nullptr; }
	virtual QAction *actionDispConfig() { return nullptr; }
	virtual QAction *actionPluginManager() { return nullptr; }

	virtual void setActionTriggered(QAction *pAction) {}
	virtual QAction *actionTriggered() { return nullptr; }

	//DockWidget
	virtual void addDockWidgetToMainWindow(Qt::DockWidgetArea area, QDockWidget * dockwidget) {}
	virtual void removeDockWidgetFromMainWindow(QDockWidget * dockwidget) {}

	//绘制网格
	virtual void drawGrid();

	//加载插件
	virtual void loadPlugins();

	//释放插件
	virtual void releasePlugins();

	//插件的身份认证
	virtual bool certificatePlugin(QString pluginName) { return false; }

private:
	
};

#endif // GUIINTERFACE_H