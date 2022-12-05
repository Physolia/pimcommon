/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bingengineclienttest.h"
#include "../bingengineclient.h"
#include <QTest>
QTEST_MAIN(BingEngineClientTest)

BingEngineClientTest::BingEngineClientTest(QObject *parent)
    : QObject{parent}
{
}

void BingEngineClientTest::shouldHaveDefaultValues()
{
    BingEngineClient client;
    QCOMPARE(client.name(), QStringLiteral("bing"));
    QVERIFY(client.createTranslator());
    QVERIFY(!client.supportedLanguages().isEmpty());
}