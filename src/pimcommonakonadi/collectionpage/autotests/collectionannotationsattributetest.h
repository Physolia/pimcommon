/*
  Copyright (c) 2014-2017 Montel Laurent <montel@kde.org>

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

#ifndef COLLECTIONANNOTATIONSATTRIBUTETEST_H
#define COLLECTIONANNOTATIONSATTRIBUTETEST_H

#include <QObject>

class CollectionAnnotationsAttributeTest : public QObject
{
    Q_OBJECT
public:
    explicit CollectionAnnotationsAttributeTest(QObject *parent = nullptr);
    ~CollectionAnnotationsAttributeTest();
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldAssignAttribute();
    void shouldDeserializedAttribute();
    void shouldCloneAttribute();
    void shouldHaveType();
};

#endif // COLLECTIONANNOTATIONSATTRIBUTETEST_H