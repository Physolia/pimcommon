/*
  SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "yandexengineplugin.h"

#include <PimCommonTextTranslator/TranslatorEngineAccessManager>

#include <KLocalizedString>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

QString YandexEnginePlugin::sYandexKey;

YandexEnginePlugin::YandexEnginePlugin(QObject *parent)
    : PimCommonTextTranslator::TranslatorEnginePlugin(parent)
{
}

YandexEnginePlugin::~YandexEnginePlugin() = default;

void YandexEnginePlugin::translate()
{
    if (sYandexKey.isEmpty()) {
        const QUrl url(QStringLiteral("https://translate.yandex.com"));

        QNetworkReply *reply = PimCommonTextTranslator::TranslatorEngineAccessManager::self()->networkManager()->get(QNetworkRequest(url));
        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            parseCredentials(reply);
        });
        connect(reply, &QNetworkReply::errorOccurred, this, [this, reply](QNetworkReply::NetworkError error) {
            slotError(error);
            reply->deleteLater();
        });
    } else {
        translateText();
    }
}

void YandexEnginePlugin::parseCredentials(QNetworkReply *reply)
{
    // Check availability of service
    const QByteArray webSiteData = reply->readAll();
    reply->deleteLater();
    if (webSiteData.isEmpty() || webSiteData.contains("<title>Oops!</title>") || webSiteData.contains("<title>302 Found</title>")) {
        Q_EMIT translateFailed(false,
                               i18n("Error: Engine systems have detected suspicious traffic "
                                    "from your computer network. Please try your request again later."));
        return;
    }
    // qCDebug(PIMCOMMON_LOG) << "webSiteData  " << webSiteData;
    const QByteArray sidBeginString = "SID: '";
    const int sidBeginStringPos = webSiteData.indexOf(sidBeginString);

    if (sidBeginStringPos == -1) {
        Q_EMIT translateFailed(false, i18n("Error: Unable to find Yandex SID in web version."));
        return;
    }

    const int sidBeginPosition = sidBeginStringPos + sidBeginString.size();
    const int sidEndPosition = webSiteData.indexOf('\'', sidBeginPosition);

    if (sidEndPosition == -1) {
        Q_EMIT translateFailed(false, i18n("Error: Unable to extract Yandex SID from web version."));
        return;
    }

    // Yandex show reversed parts of session ID, need to decode

    const QString sid = QString::fromUtf8(webSiteData.mid(sidBeginPosition, sidEndPosition - sidBeginPosition));

    QStringList sidParts = sid.split(QLatin1Char('.'));

    for (int i = 0; i < sidParts.size(); ++i) {
        std::reverse(sidParts[i].begin(), sidParts[i].end());
    }

    sYandexKey = sidParts.join(QLatin1Char('.'));
    translateText();
}

void YandexEnginePlugin::translateText()
{
    if (verifyFromAndToLanguage()) {
        return;
    }

    clear();
    QString lang;
    if (from() == QStringLiteral("auto")) {
        lang = to();
    } else {
        lang = from() + QLatin1Char('-') + to();
    }
    // qDebug() << " lang " << lang;
    // Generate API url
    QUrl url(QStringLiteral("https://translate.yandex.net/api/v1/tr.json/translate"));
    url.setQuery(QStringLiteral("id=%1-2-0&srv=tr-text&text=%2&lang=%3").arg(sYandexKey, QString::fromUtf8(QUrl::toPercentEncoding(inputText())), lang));

    // Setup request
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, QLatin1String("application/x-www-form-urlencoded"));
    request.setUrl(url);

    // Make reply
    QNetworkReply *reply = PimCommonTextTranslator::TranslatorEngineAccessManager::self()->networkManager()->post(request, QByteArray());
    connect(reply, &QNetworkReply::errorOccurred, this, [this, reply](QNetworkReply::NetworkError error) {
        slotError(error);
        reply->deleteLater();
    });

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        parseTranslation(reply);
    });
}

void YandexEnginePlugin::parseTranslation(QNetworkReply *reply)
{
    const QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    const QJsonObject jsonData = jsonResponse.object();
    reply->deleteLater();

    // Parse language
    if (from() == QStringLiteral("auto")) {
        QString sourceCode = jsonData.value(QStringLiteral("lang")).toString();
        sourceCode = sourceCode.left(sourceCode.indexOf(QLatin1Char('-')));
        // m_sourceLang       = language(Yandex, sourceCode);
#if 0
        if (m_sourceLang == NoLanguage)
        {
            Q_EMIT translateFailed(false, i18n("Error: Unable to parse autodetected language"));
            return;
        }
#endif
    }

    appendResult(jsonData.value(QStringLiteral("text")).toArray().at(0).toString());
    Q_EMIT translateDone();
}