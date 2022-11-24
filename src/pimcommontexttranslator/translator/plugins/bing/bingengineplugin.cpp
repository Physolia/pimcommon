/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bingengineplugin.h"

BingEnginePlugin::BingEnginePlugin(QObject *parent)
    : PimCommonTextTranslator::TranslatorEnginePlugin(parent)
{
}

BingEnginePlugin::~BingEnginePlugin() = default;

void BingEnginePlugin::translate()
{
    // TODO
}
