/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommonTextTranslator/TranslatorEngineClient>

class LibreTranslateEngineClient : public PimCommonTextTranslator::TranslatorEngineClient
{
    Q_OBJECT
public:
    explicit LibreTranslateEngineClient(QObject *parent = nullptr);
    ~LibreTranslateEngineClient() override;

    Q_REQUIRED_RESULT QString name() const override;
    Q_REQUIRED_RESULT QString translatedName() const override;
    Q_REQUIRED_RESULT PimCommonTextTranslator::TranslatorEnginePlugin *createTranslator() override;
    Q_REQUIRED_RESULT QVector<QPair<QString, QString>> supportedLanguages() override;

private:
    QVector<QPair<QString, QString>> mLanguages;
};
