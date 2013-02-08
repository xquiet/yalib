#ifndef YALIB_H
#define YALIB_H

#include "yalib_global.h"
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QProcessEnvironment>
#include <QHash>

class YALIBSHARED_EXPORT Yalib {
public:
    Yalib();
    QString detectFGBinPath(bool autodetect = true);
    QString detectFGVersion();
    QString detectRootPath();
    QString detectOS();
    QString getYFHome();
    QString getYFScenery();
    QString getDefaultScenery();
    bool initialize(bool autoDetect = true);
    QString getOS();
    QString getFGVersion();
    QString getAircraftsDir();
    QString getDefaultAirportsDir();
    QString getAPTSource();
    QHash<QString, QStringList> parseAirportsIndex(QString path);
    QHash<QString, QStringList> getDefaultAirportList();

    void setRootPath(QString path);
    QString getRootPath();

    void setFgfsBinPath(QString path);
    QString getFgfsBinPath();

    QString getTerraSyncBinPath();
    QString getTerraSyncPidFilePath();

private:
    QString fgRootPath;
    QString fgfs_binary;
    QString operating_system;
    QString fgVersion;
};

#endif // YALIB_H
