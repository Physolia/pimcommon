/*
  SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "purposemenuwidgettest.h"

#include <QMenu>
#include <QTest>

QTEST_MAIN(PurposeMenuWidgetTest)

PurposeMenuWidgetTest::PurposeMenuWidgetTest(QObject *parent)
    : QObject(parent)
{
}

void PurposeMenuWidgetTest::shouldHaveDefaultValues()
{
    TestMenu w(nullptr);
    QVERIFY(w.menu());
    QCOMPARE(w.menu()->objectName(), QStringLiteral("purposesharemenu"));
}
