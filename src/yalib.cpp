#include "yalib.h"


Yalib::Yalib()
{
    // initialize
    fgRootPath = "";
    fgVersion = "";
    operating_system = "";
    fgfs_binary = "";
}

bool Yalib::initialize(bool autoDetect)
{
    if(operating_system.isEmpty())
        operating_system = detectOS();
    if(autoDetect)
    {
        fgRootPath = detectRootPath();
        fgfs_binary = detectFGBinPath();
        if(!QFile::exists(fgfs_binary))  // debian has fgfs under /usr/games/
            return false;                // if appconf.ini already exists must it must be removed!
    }
    // detectFGVersion needs the rootpath
    fgVersion = detectFGVersion();

    if(fgRootPath.isEmpty())
        return false;

    QDir dir(getYFScenery());
    if(!dir.exists())
    {
        //if(dir.mkpath(getYFScenery()))
        if(!dir.mkdir(getYFScenery()))
        {
            qFatal("Cannot create dir: %s",getYFScenery().toStdString().data());
            return false;
        }
    }

    yainstall_binary = detectYaInstallPath();

    return true;
}

void Yalib::setRootPath(QString path)
{
    fgRootPath = path.trimmed();
}


QString Yalib::getRootPath()
{
    return fgRootPath;
}

QString Yalib::getOS()
{
    return operating_system;
}

QString Yalib::getFGVersion()
{
    return fgVersion;
}

void Yalib::setFgfsBinPath(QString path)
{
    fgfs_binary = path.trimmed();
}

QString Yalib::getFgfsBinPath()
{
    return fgfs_binary;
}

QString Yalib::getAircraftsDir()
{
    return getRootPath()+"/Aircraft";
}

QString Yalib::getDefaultAirportsDir()
{
    return getDefaultScenery() + "/Airports";
}

QString Yalib::getAPTSource()
{
    return getRootPath() + "/Airports/apt.dat.gz";
}

QString Yalib::getAIDir()
{
    return getRootPath() + "/AI";
}

QHash<QString, QStringList> Yalib::parseAirportsIndex(QString path)
{
    QFile airports(path);
    QHash<QString, QStringList> result;
    QStringList pair;
    if(airports.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream in(&airports);
        result.begin();
        while(!in.atEnd())
        {
            /*
              pair[0] ICAO
              pair[1] longitude
              pair[2] latitude

              resultHash -> | string | <lon, lat, empty space for directory> |
              */
            pair = in.readLine().split("|");
            result.insert(pair[0],QStringList() << pair[1] << pair[2] << "");
        }
        result.end();
        airports.close();
    }
    return result;
}

QHash<QString, QStringList> Yalib::getDefaultAirportList()
{
    return parseAirportsIndex(getDefaultAirportsDir()+"/"+"index.txt");
}

QString Yalib::getYFHome()
{
    QString yfhome = "";
    #ifdef Q_OS_WIN
        yfhome = "/yaflight";
    #else
        #if defined Q_OS_LINUX || defined Q_OS_UNIX
            yfhome = "/.yaflight";
        #endif
    #endif
    yfhome = QDir::homePath() + yfhome;
    if (!QFile::exists(yfhome))
    {
        QDir tmppath(QDir::homePath());
        tmppath.mkpath(yfhome);
    }
    return yfhome;
}

QString Yalib::getYFScenery()
{
    return getYFHome() + "/Scenery";
}

QString Yalib::getDefaultScenery()
{
    // default scenery
    return getRootPath()+"/Scenery";
}

QString Yalib::detectOS()
{
    QProcess *sysinfo;
    QStringList os_details;
    #ifdef Q_OS_UNIX
        #ifdef Q_OS_MAC
            /*
             * kern.ostype = Darwin
             * kern.osrelease = 12.2.0
             * kern.osrevision = 199506
             * kern.ostype: Darwin
             * kern.osrelease: 12.2.0
             * kern.osrevision: 199506
             */
            QString os = "Mac OS X";
            sysinfo = new QProcess();
            sysinfo->setProcessChannelMode(QProcess::MergedChannels);
            sysinfo->start("/usr/sbin/sysctl", QStringList() << "kern.ostype" << "kern.osrelease", QProcess::ReadOnly);
            sysinfo->waitForFinished();
            QByteArray bytes = sysinfo->readAll();
            QStringList strLines = QString(bytes).split("\n");
            QStringList cols;
            foreach(QString line, strLines)
            {
                line = line.trimmed();
                if(line.contains("kern.ostype")||line.contains("kern.osrelease"))
                {
                    cols = line.split(":", QString::SkipEmptyParts, Qt::CaseSensitive);
                    if(cols.length()>0)
                    {
                        os_details.append(cols[1].trimmed());
                    }
                }
            }

            return os + " - " + os_details.join(" ");
        #elif defined Q_OS_LINUX
            QString os = "GNU/Linux";

            sysinfo = new QProcess();
            sysinfo->setProcessChannelMode(QProcess::MergedChannels);
            sysinfo->start("/usr/bin/env",QStringList() << "lsb_release" << "-a", QProcess::ReadOnly);
            sysinfo->waitForFinished();
            QByteArray bytes = sysinfo->readAll();
            QStringList strLines = QString(bytes).split("\n");
            QStringList cols;
            foreach (QString line, strLines){
                line = line.trimmed();
                if(line.contains("Distributor ID")){
                    cols = line.split(":",QString::SkipEmptyParts,Qt::CaseSensitive);
                    if (cols.length()>0)
                        os_details.append(cols[1].trimmed());
                }
            }
            return os + " - " + os_details.join(" ");
        #else
            //bsd
            QString os = "Unix";
            sysinfo = new QProcess();
            sysinfo->setProcessChannelMode(QProcess::MergedChannels);
            sysinfo->start("/usr/bin/env",QStringList() << "uname" << "-s", QProcess::ReadOnly);
            sysinfo->waitForFinished();
            QByteArray bytes = sysinfo->readAll();
            os = os + " " + QString(bytes).split("\n")[0];
            return os;
        #endif
    #endif
    #ifdef Q_OS_WIN32
        QProcessEnvironment pe(QProcessEnvironment::systemEnvironment());
        _win_program_files = pe.value("ProgramFiles").replace("\\","/");
        return "Windows";
    #elif defined Q_OS_WIN64
        QProcessEnvironment pe(QProcessEnvironment::systemEnvironment());
        _win_program_files = pe.value("ProgramW6432").replace("\\","/");
        _win_program_files = _win_program_files.append(";").append(pe.value("ProgramFiles").replace("\\","/"));
    #endif
    return "";
}

QString Yalib::detectFGBinPath(bool autodetect)
{
    if(autodetect)
    {
        #ifdef Q_OS_WIN32
            return "\""+getRootPath()+"/../bin/Win32/fgfs.exe\"";
	#elif defined Q_OS_WIN64
	    return "\""+getRootPath()+"/../bin/Win64/fgfs.exe\"";
        #elif defined Q_OS_UNIX
            #ifdef Q_OS_LINUX
                return "/usr/bin/fgfs";
            #elif defined Q_OS_MACX
                return "/Applications/FlightGear.app/Contents/MacOS/fgfs";
            #else
                //bsd
                return "/usr/local/bin/fgfs";
            #endif
        #endif
    }
    return "";
}

QString Yalib::detectFGVersion()
{
    QString output = "";
    QFile version(getRootPath()+"/"+"version");
    if(version.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream in(&version);
        while(!in.atEnd())
        {
            output += in.readLine();
        }
        version.close();
    }
    else
    {
        qWarning("Failed to open %s for read: %s",
                 version.fileName().toStdString().data(),
                 version.errorString().toStdString().data());
    }
    return output;
}

QString Yalib::detectRootPath()
{
    QStringList possiblePaths;
    #ifdef Q_OS_WIN32
        possiblePaths << _win_program_files + "/FlightGear/data";
        //possiblePaths << "C:/Program Files/FlightGear/data";
    #elif defined Q_OS_WIN64
	QStringList items = _win_program_files.split(";");
	possiblePaths << items[0] + "/FlightGear/data";
	possiblePaths << items[1] + "/FlightGear/data";
    #endif
    #ifdef Q_OS_UNIX
        #ifdef Q_OS_MAC
            possiblePaths << "/Applications/FlightGear.app/Contents/Resources/data";
        #elif defined Q_OS_LINUX
            possiblePaths << "/usr/share/flightgear/data"
                          << "/usr/share/FlightGear"
                          << "/usr/share/flightgear"
                          << "/usr/share/games/FlightGear"
                          << "/usr/share/games/flightgear";
        #else
            //bsd
            possiblePaths << "/usr/local/share/flightgear";
        #endif
    #endif
    for(int i=0;i<possiblePaths.count();i++)
    {
	// check for the version file because of multiple flightgear directories could coexist
        if(QFile::exists(possiblePaths[i]+"/version"))
            return possiblePaths[i];
    }
    return QString();
}

QString Yalib::detectYaInstallPath()
{
    QStringList possiblePaths;
    #ifdef Q_OS_WIN
        possiblePaths << _win_program_files + "/YaInstall/yainstall";
        //possiblePaths << "C:/Program Files/YaInstall";
    #endif
    #ifdef Q_OS_UNIX
        #ifdef Q_OS_MAC
            possiblePaths << "/Applications/YaInstall.app/Contents";
        #elif defined Q_OS_LINUX
            possiblePaths << "/usr/bin/yainstall"
                          << "/usr/sbin/yainstall"
                          << "/opt/yainstall/yainstall"
                          << "/usr/local/bin/yainstall"
                          << "/usr/games/yainstall"
                          << "/usr/share/yainstall/yainstall"
                          << "/usr/share/games/yainstall/yainstall"
                          << "/usr/share/games/YaInstall/yainstall";
        #else
            //bsd
            possiblePaths << "/usr/local/share/yainstall/yainstall"
                          << "/usr/local/bin/yainstall"
                          << "/usr/bin/yainstall";
        #endif
    #endif
    for(int i=0;i<possiblePaths.count();i++)
    {
        if(QFile::exists(possiblePaths[i]))
            return possiblePaths[i];
    }
    return QString();
}

QString Yalib::getTerraSyncBinPath()
{
    QString ts_path = "";
    #ifdef Q_OS_WIN
        ts_path = "\""+getRootPath()+"/../bin/Win32/terrasync.exe\"";
    #elif defined Q_OS_UNIX
        #ifdef Q_OS_LINUX
            ts_path = "/usr/bin/terrasync";
        #elif defined Q_OS_MACX
            ts_path = "";
        #else
            //bsd
            ts_path = "/usr/local/bin/terrasync";
        #endif
    #endif
    return ts_path;
}

QString Yalib::getTerraSyncPidFilePath()
{
    return getYFHome() + "/ts_pid";
}

QString Yalib::getYaInstallBinary()
{
    return yainstall_binary;
}

QStringList Yalib::getScenarios()
{
    QDir dir(getRootPath()+"/AI");
    if(dir.exists())
    {
        QStringList results;
        QStringList fileList = dir.entryList(QDir::Files);
        foreach(QString file, fileList)
        {
            if(file.endsWith(".xml"))
            {
                results << file.replace(".xml","");
            }
        }
        return results;
    }
    qDebug("Directory %s not found", dir.absolutePath().toStdString().data());
    return QStringList();
}
