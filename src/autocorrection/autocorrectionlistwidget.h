/*
  Copyright (c) 2012-2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef AutoCorrectionListWidget_H
#define AutoCorrectionListWidget_H

#include <QListWidget>

namespace PimCommon
{

class AutoCorrectionListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit AutoCorrectionListWidget(QWidget *parent = Q_NULLPTR);
    ~AutoCorrectionListWidget();

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

Q_SIGNALS:
    void deleteSelectedItems();
};

}

#endif // AutoCorrectionListWidget_H
