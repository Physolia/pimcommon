/*
  Copyright (c) 2012-2016 Montel Laurent <montel@kde.org>

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

#ifndef PIMCOMMONCREATERESOURCE_H
#define PIMCOMMONCREATERESOURCE_H

#include "pimcommonakonadi_export.h"
#include <QObject>
#include <QVariant>
#include <QMap>

namespace PimCommon {
class PIMCOMMONAKONADI_EXPORT CreateResource : public QObject
{
    Q_OBJECT
public:
    explicit CreateResource(QObject *parent = nullptr);
    ~CreateResource();

    QString createResource(const QString &resources, const QString &name, const QMap<QString, QVariant> &settings, bool synchronizeTree = false);

Q_SIGNALS:
    void createResourceInfo(const QString &);
    void createResourceError(const QString &);
};
}

#endif // CREATERESOURCE_H
