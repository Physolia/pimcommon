/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "translatorconfigurecombowidget.h"
#include <QHBoxLayout>

using namespace PimCommonTextTranslator;
TranslatorConfigureComboWidget::TranslatorConfigureComboWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});
}

TranslatorConfigureComboWidget::~TranslatorConfigureComboWidget() = default;
