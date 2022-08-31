#include "ParseXodr.h"
#include "tessinterface.h"
#include "guiinterface.h"
#include <QMainWindow>
#include <QAction>
#include <QFileDialog>
#include <QApplication>
#include "XodrNet.h"
#include <QSettings>
#include <QMessageBox>

ParseXodr::ParseXodr(QObject* parent) :QObject(parent)
{

}

void ParseXodr::init()
{
	initGui();

	m_ptrXodrNet = std::make_shared<XodrNet>();
}

void ParseXodr::unload()
{

}

CustomerGui* ParseXodr::customerGui()
{
	return nullptr;
}

CustomerNet* ParseXodr::customerNet()
{
	return m_ptrXodrNet.get();
}

CustomerSimulator* ParseXodr::customerSimulator()
{
	return nullptr;
}

void ParseXodr::initGui()
{
	QAction* pCloase = gpTessInterface->guiInterface()->actionClose();
	QMenu* pMenu = gpTessInterface->guiInterface()->fileMenu();
	QMenu* xodrMenu = new QMenu("加载OpenDriver", gpTessInterface->guiInterface()->mainWindow());
	pMenu->insertMenu(pCloase, xodrMenu);
	QAction* action = xodrMenu->addAction("选择xodr");
	QObject::connect(action, &QAction::triggered, [=]() {
		QString	custSuffix = QString("TESSNG Files (*.xodr);");
		QString dbDir = QApplication::applicationDirPath();
		QString selectedFilter = QString("TESSNG Files (*.xodr)");
		const QFileDialog::Options options = QFlag(0);

		QSettings setting("./Setting.ini", QSettings::IniFormat);
		QString lastPath = setting.value("LastFilePath").toString();

		QString netFilePath = QFileDialog::getOpenFileName(nullptr,
			QString("打开文件"),
			lastPath,
			custSuffix,
			&selectedFilter,
			options);

		if (netFilePath.isEmpty()) return;
		int i = netFilePath.lastIndexOf('/');
		QString Path = netFilePath.left(i);
		QVariant VarPath(Path);
		setting.setValue("LastFilePath", VarPath);

	
		try {
			m_ptrXodrNet->loadXodrNet(netFilePath);
		}
		catch (std::exception& exc) {
			QMessageBox::critical(gpTessInterface->guiInterface()->mainWindow(),QString("加载文件出错"), exc.what());
		}
		catch (...) {
			QMessageBox::critical(gpTessInterface->guiInterface()->mainWindow(),QString("加载文件出错"), QString("未知错误出错"));
		}
		
		});


	QAction* pShowAll = xodrMenu->addAction("显示所有");
	pShowAll->setCheckable(true);
	pShowAll->setChecked(false);
	QObject::connect(pShowAll, &QAction::triggered, [=](bool checked) {
			m_ptrXodrNet->setShowAll(checked);
		});
}
