#-------------------------------------------------
#
# Project created by QtCreator 2013-02-08T11:58:33
#
#-------------------------------------------------

QT       -= gui

TARGET = yalib
TEMPLATE = lib

DEFINES += YALIB_LIBRARY

SOURCES += yalib.cpp

HEADERS += yalib.h\
        yalib_global.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE22B6BC5
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = yalib.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
