/*
  Copyright (c) 2013-2016 Montel Laurent <montel@kde.org>

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

#include "webdavsettingsdialog.h"

#include <KLocalizedString>
#include <QLineEdit>

#include <QLabel>
#include <QVBoxLayout>
#include <KConfigGroup>
#include <QDialogButtonBox>
#include <QPushButton>

using namespace PimCommon;

WebDavSettingsDialog::WebDavSettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18n("WebDav Settings"));
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    mOkButton = buttonBox->button(QDialogButtonBox::Ok);
    mOkButton->setDefault(true);
    mOkButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &WebDavSettingsDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &WebDavSettingsDialog::reject);
    QWidget *w = new QWidget;

    QVBoxLayout *lay = new QVBoxLayout;

    QLabel *lab = new QLabel(i18n("Service Location (e.g. https://dav.example.com/)"));
    lay->addWidget(lab);

    mServiceLocation = new QLineEdit;
    mServiceLocation->setClearButtonEnabled(true);
    lay->addWidget(mServiceLocation);

    //Hide for the moment not implemented.
    lab = new QLabel(i18n("Public location (Optional)"));
    lab->hide();
    lay->addWidget(lab);

    mPublicLocation = new QLineEdit;
    mPublicLocation->hide();
    lay->addWidget(mPublicLocation);

    w->setLayout(lay);
    mainLayout->addWidget(w);
    mainLayout->addWidget(buttonBox);
    connect(mServiceLocation, &QLineEdit::textChanged, this, &WebDavSettingsDialog::slotServiceLocationChanged);
    mOkButton->setEnabled(false);
}

WebDavSettingsDialog::~WebDavSettingsDialog()
{

}

void WebDavSettingsDialog::slotServiceLocationChanged(const QString &text)
{
    mOkButton->setEnabled(!text.isEmpty() && (text.startsWith(QLatin1String("http://")) || text.startsWith(QLatin1String("https://"))));
}

QString WebDavSettingsDialog::serviceLocation() const
{
    return mServiceLocation->text().trimmed();
}

QString WebDavSettingsDialog::publicLocation() const
{
    return mPublicLocation->text().trimmed();
}

