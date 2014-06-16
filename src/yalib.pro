#-------------------------------------------------
#
# Project created by QtCreator 2013-02-08T11:58:33
#
#-------------------------------------------------

QT       -= gui

TARGET = yalib
TEMPLATE = lib
mac: CONFIG += lib_bundle

MAX_VERSION = 1
MIN_VERSION = 6
VERSION = $$MAX_VERSION.$$MIN_VERSION

DEFINES += YALIB_LIBRARY

SOURCES += yalib.cpp \
    installer.cpp

HEADERS += yalib.h\
        yalib_global.h \
    installer.h

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
        header_files.path = /opt/usr/include/yalib
    } else {
        target.path = /usr/lib
        header_files.path = /usr/include/yalib
    }
    header_files.files = $$HEADERS
    INSTALLS += target header_files
}

unix:!macx {
    LIBS += -lzip -lz
    target.path = /usr/bin
}
macx {
    INCLUDEPATH += /opt/local/include /opt/local/lib/libzip/include
    LIBS += -L/opt/local/lib -lzip -lz
}

FRAMEWORK_HEADERS.version = Versions
FRAMEWORK_HEADERS.files = yalib.h yalib_global.h
FRAMEWORK_HEADERS.path = HEADERS
QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS
