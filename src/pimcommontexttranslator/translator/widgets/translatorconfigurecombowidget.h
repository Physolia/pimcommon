/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "pimcommontexttranslator_export.h"
#include <QWidget>
class QComboBox;
class QToolButton;
namespace PimCommonTextTranslator
{
class PIMCOMMONTEXTTRANSLATOR_EXPORT TranslatorConfigureComboWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TranslatorConfigureComboWidget(QWidget *parent = nullptr);
    ~TranslatorConfigureComboWidget() override;

private:
    void slotConfigureEngine();
    QComboBox *const mEngineComboBox;
    QToolButton *const mConfigureEngine;
};
}
