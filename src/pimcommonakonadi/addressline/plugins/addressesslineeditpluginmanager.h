/*
   Copyright (C) 2017-2020 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef ADDRESSESSLINEEDITPLUGINMANAGER_H
#define ADDRESSESSLINEEDITPLUGINMANAGER_H

#include <QObject>
#include "pimcommonakonadi_export.h"

namespace PimCommon {
class AddressessLineEditAbstractPlugin;
class AddressessLineEditPluginManagerPrivate;
/**
 * @brief The AddressessLineEditPluginManager class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT AddressessLineEditPluginManager : public QObject
{
    Q_OBJECT
public:
    explicit AddressessLineEditPluginManager(QObject *parent = nullptr);
    ~AddressessLineEditPluginManager();

    static AddressessLineEditPluginManager *self();

    PimCommon::AddressessLineEditAbstractPlugin *plugin(const QString &identifier);
    QVector<PimCommon::AddressessLineEditAbstractPlugin *> pluginsList() const;

private:
    AddressessLineEditPluginManagerPrivate *const d;
};
}

#endif // ADDRESSESSLINEEDITPLUGINMANAGER_H