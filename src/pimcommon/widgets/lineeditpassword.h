/*
  Copyright (c) 2017 Montel Laurent <montel@kde.org>

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

#ifndef LINEEDITPASSWORD_H
#define LINEEDITPASSWORD_H

#include <QWidget>
#include "pimcommon_export.h"
class QLineEdit;
class QAction;
namespace PimCommon
{
class LineEditPasswordPrivate;
class PIMCOMMON_EXPORT LineEditPassword : public QWidget
{
public:
    explicit LineEditPassword(QWidget *parent = nullptr);
    ~LineEditPassword();

    void setPassword(const QString &p);
    QString password() const;

    QAction *toggleEchoModeAction() const;

    QLineEdit *passwordLineEdit() const;

private:
    void initialize();
    void toggleEchoMode();
    void showToggleEchoModeAction(const QString &text);
    class LineEditPasswordPrivate;
    LineEditPasswordPrivate *const d;
};
}

#endif // LINEEDITPASSWORD_H
