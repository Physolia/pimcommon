/*
  Copyright (c) 2013-2020 Laurent Montel <montel@kde.org>

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

#include "selectmulticollectiondialog.h"
#include "selectmulticollectionwidget.h"

#include <KLocalizedString>
#include <KConfigGroup>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

using namespace PimCommon;

class PimCommon::SelectMultiCollectionDialogPrivate
{
public:
    SelectMultiCollectionDialogPrivate()
    {
    }

    SelectMultiCollectionWidget *mSelectMultiCollection = nullptr;
};

SelectMultiCollectionDialog::SelectMultiCollectionDialog(const QString &mimetype, const QList<Akonadi::Collection::Id> &selectedCollection, QWidget *parent)
    : QDialog(parent)
    , d(new PimCommon::SelectMultiCollectionDialogPrivate)
{
    initialize(mimetype, selectedCollection);
}

SelectMultiCollectionDialog::SelectMultiCollectionDialog(const QString &mimetype, QWidget *parent)
    : QDialog(parent)
    , d(new PimCommon::SelectMultiCollectionDialogPrivate)
{
    initialize(mimetype);
}

SelectMultiCollectionDialog::~SelectMultiCollectionDialog()
{
    writeConfig();
    delete d;
}

void SelectMultiCollectionDialog::initialize(const QString &mimetype, const QList<Akonadi::Collection::Id> &selectedCollection)
{
    setWindowTitle(i18nc("@title:window", "Select Multiple Folders"));
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Close, this);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &SelectMultiCollectionDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SelectMultiCollectionDialog::reject);

    d->mSelectMultiCollection = new SelectMultiCollectionWidget(mimetype, selectedCollection, this);
    mainLayout->addWidget(d->mSelectMultiCollection);
    mainLayout->addWidget(buttonBox);
    readConfig();
}

void SelectMultiCollectionDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "SelectMultiCollectionDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(800, 600));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}

void SelectMultiCollectionDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "SelectMultiCollectionDialog");
    group.writeEntry("Size", size());
}

QVector<Akonadi::Collection> SelectMultiCollectionDialog::selectedCollection() const
{
    return d->mSelectMultiCollection->selectedCollection();
}
