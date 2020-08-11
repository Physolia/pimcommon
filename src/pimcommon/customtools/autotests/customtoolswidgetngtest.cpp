/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "customtoolswidgetngtest.h"
#include "customtools/customtoolswidgetng.h"
#include <QStackedWidget>
#include <QTest>
#include <QStandardPaths>

CustomToolsWidgetNgTest::CustomToolsWidgetNgTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

CustomToolsWidgetNgTest::~CustomToolsWidgetNgTest()
{
}

void CustomToolsWidgetNgTest::shouldHaveDefaultValue()
{
    PimCommon::CustomToolsWidgetNg widget;
    widget.show();

    QStackedWidget *stackWidget = widget.findChild<QStackedWidget *>(QStringLiteral("stackedwidget"));
    QVERIFY(stackWidget);
}

QTEST_MAIN(CustomToolsWidgetNgTest)
