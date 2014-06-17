/**
    Copyright (C) 2012-2013  Matteo Pasotti <matteo.pasotti@gmail.com>

    This file is part of yalib

    yalib is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    yalib is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    */

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

    QString getYaInstallBinary();

    QString getAIDir();

    QStringList getScenarios();

private:
    QString detectFGBinPath(bool autodetect = true);
    QString detectFGVersion();
    QString detectRootPath();
    QString detectYaInstallPath();
    QString detectOS();

    QString fgRootPath;
    QString fgfs_binary;
    QString operating_system;
    QString fgVersion;
    QString yainstall_binary;
    QString _win_program_files;
    bool _32_on_64;
};

#endif // YALIB_H
