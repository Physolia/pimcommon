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

#include "lineeditwithcompleterngtest.h"
#include "../lineeditwithcompleterng.h"
#include <QCompleter>
#include <QTest>

QTEST_MAIN(LineEditWithCompleterNgTest)

LineEditWithCompleterNgTest::LineEditWithCompleterNgTest(QObject *parent)
    : QObject(parent)
{

}

void LineEditWithCompleterNgTest::shouldHaveDefaultValue()
{
   PimCommon::LineEditWithCompleterNg w;
   QVERIFY(w.completer());
   QVERIFY(w.completer()->model());
   QCOMPARE(w.completer()->model()->rowCount(), 0);
}


void LineEditWithCompleterNgTest::shouldAddCompletionItem()
{
    PimCommon::LineEditWithCompleterNg w;
    w.addCompletionItem(QStringLiteral("ff"));
    QCOMPARE(w.completer()->model()->rowCount(), 1);

    //Don't add same element
    w.addCompletionItem(QStringLiteral("ff"));
    QCOMPARE(w.completer()->model()->rowCount(), 1);

    w.addCompletionItem(QStringLiteral("ffss"));
    QCOMPARE(w.completer()->model()->rowCount(), 2);
}

void LineEditWithCompleterNgTest::shouldClearCompleter()
{
    PimCommon::LineEditWithCompleterNg w;
    for (int i = 0; i < 10 ;++i) {
        w.addCompletionItem(QStringLiteral("ff%1").arg(i));
    }
    QCOMPARE(w.completer()->model()->rowCount(), 10);
    w.slotClearHistory();
    QCOMPARE(w.completer()->model()->rowCount(), 0);
}