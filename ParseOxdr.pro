QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console

msvc:QMAKE_CXXFLAGS += -source-charset:utf-8
msvc:QMAKE_CXXFLAGS += -execution-charset:utf-8


MOC_DIR += $$PWD/temp/moc_dir
OBJECTS_DIR += $$PWD/temp/obj_dir
UI_DIR += $$PWD/temp/ui_dir
RCC_DIR += $$PWD/temp/rcc_dir

SOURCES += \
    CreateJountion.cpp \
    CreateLink.cpp \
    ParseXodr.cpp \
    PrograssDlgForFloat.cpp \
    XodrNet.cpp \
    main.cpp

HEADERS += \
    CreateJountion.h \
    CreateLink.h \
    ParseXodr.h \
    PrograssDlgForFloat.h \
    XodrNet.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH +=$$PWD/OpenDrive/
include($$PWD/OpenDrive/OpenDrive.pri)


INCLUDEPATH += $$PWD/XODR_Plugin/include
DEPENDPATH += $$PWD/XODR_Plugin/include

INCLUDEPATH += $$PWD/TESSNG_Plugin/include
DEPENDPATH += $$PWD/TESSNG_Plugin/include
win32{
contains(QT_ARCH, i386) {
    message("32-bit")
  }else {
    message("64-bit")

    win32:CONFIG(release, debug|release): LIBS += -L$$PWD/TESSNG_Plugin/lib/release/ -lTessInterfaces
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/TESSNG_Plugin/lib/debug/ -lTessInterfaces
    win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/TESSNG_Plugin/lib/release/libTessInterfaces.a
    else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/TESSNG_Plugin/lib/debug/libTessInterfaces.a
    else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/TESSNG_Plugin/lib/release/TessInterfaces.lib
    else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/TESSNG_Plugin/lib/debug/TessInterfaces.lib

    win32:CONFIG(release, debug|release): LIBS += -L$$PWD/TESSNG_Plugin/lib/release/ -lTessSupport
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/TESSNG_Plugin/lib/debug/ -lTessSupport
    win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/TESSNG_Plugin/lib/release/libTessSupport.a
    else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/TESSNG_Plugin/lib/debug/libTessSupport.a
    else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/TESSNG_Plugin/lib/release/TessSupport.lib
    else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/TESSNG_Plugin/lib/debug/TessSupport.lib

    win32:CONFIG(release, debug|release): LIBS += -L$$PWD/XODR_Plugin/lib/x64/release/ -lxodr
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/XODR_Plugin/lib/x64/debug/ -lxodr

    win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/XODR_Plugin/lib/x64/release/libpugixml.a
    else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/XODR_Plugin/lib/x64/debug/libpugixml.a
    else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/XODR_Plugin/lib/x64/release/pugixml.lib
    else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/XODR_Plugin/lib/x64/debug/pugixml.lib
  }
}

DISTFILES +=


