/*
  Copyright (c) 2016-2018 Montel Laurent <montel@kde.org>

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

#ifndef NetworkManager_H
#define NetworkManager_H

#include <QObject>
#include "pimcommon_export.h"
class QNetworkConfigurationManager;
namespace PimCommon {
class PIMCOMMON_EXPORT NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();
    static NetworkManager *self();

    Q_REQUIRED_RESULT QNetworkConfigurationManager *networkConfigureManager() const;

private:
    QNetworkConfigurationManager *mNetworkConfigureManager = nullptr;
};
}

#endif // NetworkManager_H
