/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommonTextTranslator/TranslatorEngineClient>

class BingEngineClient : public PimCommonTextTranslator::TranslatorEngineClient
{
    Q_OBJECT
public:
    explicit BingEngineClient(QObject *parent = nullptr);
    ~BingEngineClient() override;

    Q_REQUIRED_RESULT QString name() const override;
    Q_REQUIRED_RESULT QString translatedName() const override;
    Q_REQUIRED_RESULT PimCommonTextTranslator::TranslatorEnginePlugin *createTranslator() override;
    Q_REQUIRED_RESULT QVector<QPair<QString, QString>> supportedLanguages() override;

private:
    QVector<QPair<QString, QString>> mLanguages;
};
