/*
  Copyright (c) 2014-2017 Montel Laurent <montel@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.

*/

#ifndef INCIDENCESFORWIDGET_H
#define INCIDENCESFORWIDGET_H

#include "pimcommonakonadi_export.h"
#include <QWidget>

namespace PimCommon
{
class IncidencesForWidgetPrivate;
class PIMCOMMONAKONADI_EXPORT IncidencesForWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IncidencesForWidget(QWidget *parent = nullptr);
    ~IncidencesForWidget();

    int currentIndex() const;
    void setCurrentIndex(int index);

Q_SIGNALS:
    void currentIndexChanged(int value);

private:
    IncidencesForWidgetPrivate *const d;
};
}

#endif // INCIDENCESFORWIDGET_H