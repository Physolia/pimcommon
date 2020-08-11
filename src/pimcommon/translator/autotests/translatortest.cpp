/*
  SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "translatortest.h"
#include "translator/translatorwidget.h"
#include <KPIMTextEdit/PlainTextEditorWidget>

#include <QPushButton>

#include <QTest>
#include <qtestkeyboard.h>
#include <qtestmouse.h>
#include <QComboBox>
#include <QSignalSpy>
#include <QStandardPaths>
TranslatorTest::TranslatorTest()
{
    QStandardPaths::setTestModeEnabled(true);
}

void TranslatorTest::shouldHaveDefaultValuesOnCreation()
{
    PimCommon::TranslatorWidget edit;
    QComboBox *from = edit.findChild<QComboBox *>(QStringLiteral("from"));
    QComboBox *to = edit.findChild<QComboBox *>(QStringLiteral("to"));

    PimCommon::TranslatorTextEdit *inputtext = edit.findChild<PimCommon::TranslatorTextEdit *>(QStringLiteral("inputtext"));
    KPIMTextEdit::PlainTextEditorWidget *translatedText = edit.findChild<KPIMTextEdit::PlainTextEditorWidget *>(QStringLiteral("translatedtext"));
    QPushButton *translate = edit.findChild<QPushButton *>(QStringLiteral("translate-button"));
    QPushButton *clear = edit.findChild<QPushButton *>(QStringLiteral("clear-button"));
    QPushButton *invert = edit.findChild<QPushButton *>(QStringLiteral("invert-button"));
    QVERIFY(invert);
    QVERIFY(clear);
    QVERIFY(translate);
    QVERIFY(from);
    QVERIFY(to);
    QCOMPARE(from->count() > 0, true);
    QCOMPARE(to->count() > 0, true);
    QVERIFY(inputtext);
    QVERIFY(translatedText);
    QCOMPARE(inputtext->toPlainText(), QString());
    QCOMPARE(translatedText->toPlainText(), QString());
    QCOMPARE(translate->isEnabled(), false);
}

void TranslatorTest::shouldEnableTranslateButtonWhenTextToTranslateIsNotEmpty()
{
    PimCommon::TranslatorWidget edit;

    PimCommon::TranslatorTextEdit *inputtext = edit.findChild<PimCommon::TranslatorTextEdit *>(QStringLiteral("inputtext"));
    QPushButton *translate = edit.findChild<QPushButton *>(QStringLiteral("translate-button"));
    inputtext->setPlainText(QStringLiteral("Foo"));
    QCOMPARE(translate->isEnabled(), true);
}

void TranslatorTest::shouldDisableTranslateButtonAndClearTextWhenClickOnClearButton()
{
    PimCommon::TranslatorWidget edit;
    PimCommon::TranslatorTextEdit *inputtext = edit.findChild<PimCommon::TranslatorTextEdit *>(QStringLiteral("inputtext"));
    QPushButton *translate = edit.findChild<QPushButton *>(QStringLiteral("translate-button"));
    KPIMTextEdit::PlainTextEditorWidget *translatedText = edit.findChild<KPIMTextEdit::PlainTextEditorWidget *>(QStringLiteral("translatedtext"));
    inputtext->setPlainText(QStringLiteral("Foo"));
    QPushButton *clear = edit.findChild<QPushButton *>(QStringLiteral("clear-button"));
    QTest::mouseClick(clear, Qt::LeftButton);
    QCOMPARE(inputtext->toPlainText(), QString());
    QCOMPARE(translatedText->toPlainText(), QString());
    QCOMPARE(translate->isEnabled(), false);
}

void TranslatorTest::shouldInvertLanguageWhenClickOnInvertButton()
{
    PimCommon::TranslatorWidget edit;
    QComboBox *from = edit.findChild<QComboBox *>(QStringLiteral("from"));
    QComboBox *to = edit.findChild<QComboBox *>(QStringLiteral("to"));

    const int fromIndex = 5;
    const int toIndex = 7;
    from->setCurrentIndex(fromIndex);
    to->setCurrentIndex(toIndex);
    QPushButton *invert = edit.findChild<QPushButton *>(QStringLiteral("invert-button"));
    QTest::mouseClick(invert, Qt::LeftButton);
    const int newFromIndex = from->currentIndex();
    const int newToIndex = to->currentIndex();
    QCOMPARE(fromIndex != newFromIndex, true);
    QCOMPARE(toIndex != newToIndex, true);
}

void TranslatorTest::shouldHideWidgetWhenPressEscape()
{
    PimCommon::TranslatorWidget edit;
    edit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));
    QTest::keyPress(&edit, Qt::Key_Escape);
    QCOMPARE(edit.isVisible(), false);
}

void TranslatorTest::shouldEmitTranslatorWasClosedSignalWhenCloseIt()
{
    PimCommon::TranslatorWidget edit;
    edit.show();
    QVERIFY(QTest::qWaitForWindowExposed(&edit));
    QSignalSpy spy(&edit, &PimCommon::TranslatorWidget::toolsWasClosed);
    QTest::keyClick(&edit, Qt::Key_Escape);
    QCOMPARE(spy.count(), 1);
}

QTEST_MAIN(TranslatorTest)
