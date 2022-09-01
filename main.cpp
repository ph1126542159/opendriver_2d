#include <QApplication>
#include <QTextCodec>
#include <QFileInfo>
#include <QDir>
#include <QLibrary>
#include <QFont>
#include <QMainWindow>
#include <qvector3d.h>
#include "tessinterface.h"
#include "ParseXodr.h"
#include <QMap>
#include "CreateJountion.h"

void debugInfo(QtMsgType, const QMessageLogContext& contex, const QString& msg) {
    qDebug() << contex.file << contex.line << msg;
}
int main(int argc, char *argv[])
{  
    const char *pAppFilePath = "C:\\TESSNG_2.1.0\\TESSNG.exe";
    QTextCodec* pLocalCode = QTextCodec::codecForLocale();
    QTextCodec* pUtf8 = QTextCodec::codecForName("UTF-8");
    QString tmpString = pLocalCode->toUnicode(pAppFilePath);
    QString appFilePath = pUtf8->fromUnicode(tmpString);
    appFilePath = QString(pAppFilePath);
    appFilePath.replace('\\', '/');
    QFileInfo appFileInfo = QFileInfo(appFilePath);
    QDir appDir = appFileInfo.dir();
    QString pluginDir = appDir.path() + "/plugins";
    QCoreApplication::addLibraryPath(pluginDir);

    QFont font = QFont();
    font.setFixedPitch(true);
    font.setPixelSize(13);

    qInstallMessageHandler(debugInfo);
    QGuiApplication::setFont(font);

    QApplication a(argc, argv);

    int result = -1;
    QMainWindow *pWindow = tessng();
    if (pWindow){
        ParseXodr *p = new ParseXodr();
        p->init();
        gpTessInterface->loadPluginFromMem(p);
        pWindow->showMaximized();
        result = a.exec();
        pWindow->deleteLater();
    }
    else {
        result = a.exec();
    }
    return result;
}
