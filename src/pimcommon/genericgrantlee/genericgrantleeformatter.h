/*
  Copyright (c) 2016-2019 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef GENERICGRANTLEEFORMATTER_H
#define GENERICGRANTLEEFORMATTER_H

#include "pimcommon_export.h"
#include <QObject>
#include <QVariantHash>

#include <memory>

namespace PimCommon {
class GenericGrantleeFormatterPrivate;
class PIMCOMMON_EXPORT GenericGrantleeFormatter : public QObject
{
    Q_OBJECT
public:
    explicit GenericGrantleeFormatter(QObject *parent = nullptr);
    explicit GenericGrantleeFormatter(const QString &defaultHtmlMain, const QString &themePath, QObject *parent = nullptr);
    ~GenericGrantleeFormatter();

    void setDefaultHtmlMainFile(const QString &name);

    void changeGrantleePath(const QString &path);
    Q_REQUIRED_RESULT QString errorMessage() const;

    Q_REQUIRED_RESULT QString render(const QVariantHash &mapping) const;

    //For debug
    void setContent(const QString &content);
    void refreshTemplate();
private:
    std::unique_ptr<GenericGrantleeFormatterPrivate> const d;
};
}
#endif // GENERICGRANTLEEFORMATTER_H
