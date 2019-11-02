//
//  proxyconfighelpermanager.cpp
//  ShadowClash
//
//  Created by TheWanderingCoel on 2019/6/12.
//  Copyright © 2019 Coel Wu. All rights reserved.
//

#include "paths.h"
#include "proxyconfighelpermanager.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QProcess>

void ProxyConfigHelperManager::install()
{
    QString dir = Paths::configFolderPath;

#ifdef Q_OS_WIN
    if (!QFile::exists(dir + "ProxyConfig.exe")) {
        QFile::copy(":/ProxyConfig.exe",dir + "ProxyConfig.exe");
    }

#elif defined(Q_OS_MAC)
    if (!QFile::exists(dir + "ProxyConfig")) {
        QFile::copy(":/ProxyConfig",dir + "ProxyConfig");
    }

#elif defined(Q_OS_LINUX)
    if (!QFile::exists(dir + "ProxyConfig")) {
        QFile::copy(":/ProxyConfigLinux",dir);
        QFile::rename(dir + "ProxyConfigLinux", dir + "ProxyConfig");
    }
#endif

}

void ProxyConfigHelperManager::setUpSystemProxy(int port, int socksPort)
{
    QProcess *task = new QProcess;
    QStringList param;
#ifdef Q_OS_WIN
    if (port && socksPort) {
        param << "-p" << QString("127.0.0.1:") + QString::number(socksPort);
    } else {
        param << "-d";
    }
    task->start(QString(Paths::configFolderPath) + "ProxyConfig.exe", param);
    task->waitForFinished();

#elif defined Q_OS_MAC
    if (port && socksPort) {
        param << QString::number(port) << QString::number(socksPort) << "enable";
    } else {
        param << "0" << "0" << "disable";
    }
    task->start(QString(Paths::configFolderPath) + "ProxyConfig", param);
    qDebug() << port;
    task->waitForFinished();
#endif
}
