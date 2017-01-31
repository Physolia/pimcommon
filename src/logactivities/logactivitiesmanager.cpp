/*
  Copyright (c) 2017 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "logactivitiesmanager.h"
#include <QtGlobal>

using namespace PimCommon;

Q_GLOBAL_STATIC(LogActivitiesManager, s_pLogActivitiesSelf)

LogActivitiesManager::LogActivitiesManager(QObject *parent)
    : QObject(parent)
{

}

LogActivitiesManager::~LogActivitiesManager()
{

}

LogActivitiesManager *LogActivitiesManager::self()
{
    return s_pLogActivitiesSelf;
}

void LogActivitiesManager::appendLog(const QString &str)
{
    //TODO
}

QString LogActivitiesManager::log() const
{
    return mLog;
}