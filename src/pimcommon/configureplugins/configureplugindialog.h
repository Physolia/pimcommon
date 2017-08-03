/*
  Copyright (c) 2016-2017 Montel Laurent <montel@kde.org>

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

#ifndef CONFIGUREPLUGINDIALOG_H
#define CONFIGUREPLUGINDIALOG_H

#include <QDialog>
#include "pimcommon_export.h"
class QDialogButtonBox;
namespace PimCommon {
class PIMCOMMON_EXPORT ConfigurePluginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConfigurePluginDialog(QWidget *parent = nullptr);
    ~ConfigurePluginDialog();

    void initLayout();

protected:
    void showHelp(const QString &name, const QString &anchor);
    virtual QWidget *createLayout() = 0;
    virtual void save() = 0;
    virtual void load() = 0;
    virtual void reset();

    virtual void help();

    QDialogButtonBox *buttonBox() const;

private:
    void slotHelpClicked();
    void slotAccepted();
    void slotRestoreDefaultClicked();
    void saveConfig();
    void readConfig();
    QDialogButtonBox *mButtonBox;
};
}
#endif // CONFIGUREPLUGINDIALOG_H
