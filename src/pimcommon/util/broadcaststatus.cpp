/*
  broadcaststatus.cpp

  This file is part of libkdepim.

  Author: Don Sanders <sanders@kde.org>

  Copyright (C) 2000 Don Sanders <sanders@kde.org>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include "broadcaststatus.h"
#include <QCoreApplication>

static PimCommon::BroadcastStatus *instance_;

static void deleteGlobalStaticBroadcastStatus()
{
    delete instance_;
    instance_ = nullptr;
}

namespace PimCommon {
BroadcastStatus *BroadcastStatus::instance()
{
    if (!instance_) {
        instance_ = new BroadcastStatus();
        qAddPostRoutine(deleteGlobalStaticBroadcastStatus);
    }
    return instance_;
}

class BroadcastStatusPrivate
{
public:
    BroadcastStatusPrivate()
    {
    }

    QString mStatusMsg;
    bool mTransientActive = false;
};

BroadcastStatus::BroadcastStatus()
    : d(new PimCommon::BroadcastStatusPrivate)
{
}

BroadcastStatus::~BroadcastStatus()
{
    instance_ = nullptr;
    delete d;
}

void BroadcastStatus::setStatusMsg(const QString &message)
{
    d->mStatusMsg = message;
    if (!d->mTransientActive) {
        Q_EMIT statusMsg(message);
    }
}

void BroadcastStatus::setTransientStatusMsg(const QString &msg)
{
    d->mTransientActive = true;
    Q_EMIT statusMsg(msg);
}

void BroadcastStatus::reset()
{
    d->mTransientActive = false;
    // restore
    Q_EMIT statusMsg(d->mStatusMsg);
}
}