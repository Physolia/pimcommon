/*
  Copyright (c) 2013-2017 Montel Laurent <montel@kde.org>

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

#include "addservicestoragedialog.h"
#include "storageservicecombobox.h"

#include <QDialog>
#include <KLocalizedString>

#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

using namespace PimCommon;

AddServiceStorageDialog::AddServiceStorageDialog(const QList<StorageServiceAbstract::Capability> &lstCap, const QStringList &excludeService, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18n("Add Service"));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mService = new StorageServiceComboBox(lstCap, excludeService, this);
    mStackedWidget = new QStackedWidget;
    mainLayout->addWidget(mStackedWidget);
    QLabel *label = new QLabel(i18n("All services were added."));
    mStackedWidget->addWidget(label);
    mComboboxWidget = new QWidget;
    QHBoxLayout *hbox = new QHBoxLayout;
    mComboboxWidget->setLayout(hbox);
    hbox->setMargin(0);
    hbox->addWidget(mService);
    mStackedWidget->addWidget(mComboboxWidget);
    if (mService->count() > 0) {
        mStackedWidget->setCurrentWidget(mComboboxWidget);
        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
        okButton->setDefault(true);
        okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
        connect(buttonBox, &QDialogButtonBox::accepted, this, &AddServiceStorageDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &AddServiceStorageDialog::reject);
        mainLayout->addWidget(buttonBox);
    } else {
        mStackedWidget->setCurrentWidget(label);
        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
        connect(buttonBox, &QDialogButtonBox::accepted, this, &AddServiceStorageDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &AddServiceStorageDialog::reject);
        mainLayout->addWidget(buttonBox);
    }
}

AddServiceStorageDialog::~AddServiceStorageDialog()
{

}

PimCommon::StorageServiceManager::ServiceType AddServiceStorageDialog::serviceSelected() const
{
    if (mStackedWidget->currentWidget() == mComboboxWidget) {
        return mService->service();
    } else {
        return PimCommon::StorageServiceManager::Unknown;
    }
}