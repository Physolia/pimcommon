/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "pimcommon_export.h"
#include <QNetworkReply>
#include <QObject>
namespace PimCommon
{
class PIMCOMMON_EXPORT TranslatorEngineBase : public QObject
{
    Q_OBJECT
public:
    enum TranslatorEngine {
        Google = 0,
        Bing = 1,
        Yandex = 2,
        LastEngine = Yandex,
    };

    virtual void translate() = 0;
    Q_REQUIRED_RESULT virtual QVector<QPair<QString, QString>> supportedLanguage() const = 0;

    explicit TranslatorEngineBase(QObject *parent = nullptr);
    ~TranslatorEngineBase() override;

    void setParentWidget(QWidget *parent);
    Q_REQUIRED_RESULT QString resultTranslate() const;
    void setInputText(const QString &text);
    void setFrom(const QString &language);
    void setTo(const QString &language);

    void debug();
    void clear();

Q_SIGNALS:
    void translateDone();
    void translateFailed(bool result, const QString &errorMessage = QString());

protected:
    QString mJsonData;
    QString mJsonDebug;
    QString mInputText;
    QString mFrom;
    QString mTo;
    QString mResult;
    bool mDebug = false;

    void slotError(QNetworkReply::NetworkError error);

private:
    QWidget *mParentWidget = nullptr;
};
}
