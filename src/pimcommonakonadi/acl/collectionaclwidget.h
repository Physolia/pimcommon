/*
  Copyright (c) 2015-2018 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef COLLECTIONACLWIDGET_H
#define COLLECTIONACLWIDGET_H

#include <QWidget>
class QCheckBox;
namespace PimCommon {
class AclManager;
class CollectionAclWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CollectionAclWidget(QWidget *parent = nullptr);
    ~CollectionAclWidget();

    Q_REQUIRED_RESULT PimCommon::AclManager *aclManager() const;
    Q_REQUIRED_RESULT bool recursive() const;
    void setEnableRecursiveCheckBox(bool enable);

private Q_SLOTS:
    void slotRecursivePermissionChanged();
    void slotCollectionCanBeAdministrated(bool b);

private:
    PimCommon::AclManager *mAclManager = nullptr;
    QCheckBox *mRecursiveChk = nullptr;
};
}

#endif // COLLECTIONACLWIDGET_H
