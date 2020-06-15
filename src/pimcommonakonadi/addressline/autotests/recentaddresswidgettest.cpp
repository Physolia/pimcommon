/*
  Copyright (c) 2015-2020 Laurent Montel <montel@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.

*/

#include "recentaddresswidgettest.h"
#include "../recentaddress/recentaddresswidget.h"
#include <QLineEdit>
#include <QToolButton>
#include <QListWidget>
#include <QTest>
#include <qtestmouse.h>

RecentAddressWidgetTest::RecentAddressWidgetTest(QObject *parent)
    : QObject(parent)
{
}

RecentAddressWidgetTest::~RecentAddressWidgetTest()
{
}

void RecentAddressWidgetTest::shouldHaveDefaultValue()
{
    PimCommon::RecentAddressWidget w;
    QLineEdit *lineedit = w.findChild<QLineEdit *>(QStringLiteral("line_edit"));
    QVERIFY(lineedit);
    QVERIFY(lineedit->isClearButtonEnabled());
    QVERIFY(lineedit->text().isEmpty());

    QToolButton *newButton = w.findChild<QToolButton *>(QStringLiteral("new_button"));
    QVERIFY(newButton);

    QToolButton *removeButton = w.findChild<QToolButton *>(QStringLiteral("remove_button"));
    QVERIFY(removeButton);
    QVERIFY(!removeButton->isEnabled());

    QListWidget *listview = w.findChild<QListWidget *>(QStringLiteral("list_view"));
    QVERIFY(listview);
    QCOMPARE(listview->count(), 0);
}

void RecentAddressWidgetTest::shouldAddAddresses()
{
    PimCommon::RecentAddressWidget w;
    QListWidget *listview = w.findChild<QListWidget *>(QStringLiteral("list_view"));
    QCOMPARE(listview->count(), 0);
    QStringList lst;
    lst << QStringLiteral("foo");
    lst << QStringLiteral("foo1");
    lst << QStringLiteral("foo2");
    w.setAddresses(lst);
    QCOMPARE(listview->count(), lst.count());
    //Clear list before to add
    w.setAddresses(lst);
    QCOMPARE(listview->count(), lst.count());
}

void RecentAddressWidgetTest::shouldInformThatItWasChanged()
{
    PimCommon::RecentAddressWidget w;
    QVERIFY(!w.wasChanged());
    QLineEdit *lineedit = w.findChild<QLineEdit *>(QStringLiteral("line_edit"));
    lineedit->setText(QStringLiteral("foo"));
    QToolButton *newButton = w.findChild<QToolButton *>(QStringLiteral("new_button"));
    QVERIFY(newButton);
    QVERIFY(newButton->isEnabled());
    QTest::mouseClick(newButton, Qt::LeftButton);
    QVERIFY(w.wasChanged());
    QListWidget *listview = w.findChild<QListWidget *>(QStringLiteral("list_view"));
    QCOMPARE(listview->count(), 1);
}

void RecentAddressWidgetTest::shouldNotAddMultiSameLine()
{
    PimCommon::RecentAddressWidget w;
    QLineEdit *lineedit = w.findChild<QLineEdit *>(QStringLiteral("line_edit"));
    QToolButton *newButton = w.findChild<QToolButton *>(QStringLiteral("new_button"));

    QListWidget *listview = w.findChild<QListWidget *>(QStringLiteral("list_view"));
    QCOMPARE(listview->count(), 0);

    lineedit->setText(QStringLiteral("foo"));
    QVERIFY(newButton->isEnabled());
    QTest::mouseClick(newButton, Qt::LeftButton);
    QCOMPARE(listview->count(), 1);

    QTest::mouseClick(newButton, Qt::LeftButton);
    QCOMPARE(listview->count(), 1);
}

void RecentAddressWidgetTest::shouldNotAddEmptyLine()
{
    PimCommon::RecentAddressWidget w;
    QLineEdit *lineedit = w.findChild<QLineEdit *>(QStringLiteral("line_edit"));
    QToolButton *newButton = w.findChild<QToolButton *>(QStringLiteral("new_button"));
    QListWidget *listview = w.findChild<QListWidget *>(QStringLiteral("list_view"));
    QCOMPARE(listview->count(), 0);
    QVERIFY(lineedit->text().isEmpty());
    QVERIFY(!newButton->isEnabled());

    QTest::mouseClick(newButton, Qt::LeftButton);
    QCOMPARE(listview->count(), 0);

    QTest::mouseClick(newButton, Qt::LeftButton);
    QCOMPARE(listview->count(), 0);

    lineedit->setText(QStringLiteral("foo"));
    QTest::mouseClick(newButton, Qt::LeftButton);
    QCOMPARE(listview->count(), 1);
}

void RecentAddressWidgetTest::shouldDisableAddButton()
{
    PimCommon::RecentAddressWidget w;
    QLineEdit *lineedit = w.findChild<QLineEdit *>(QStringLiteral("line_edit"));
    QToolButton *newButton = w.findChild<QToolButton *>(QStringLiteral("new_button"));

    lineedit->setText(QStringLiteral("foo"));
    QVERIFY(newButton->isEnabled());
    lineedit->clear();
    QVERIFY(!newButton->isEnabled());
}

QTEST_MAIN(RecentAddressWidgetTest)