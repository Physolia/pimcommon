/*
    simplestringlisteditor.cpp

    This file is part of KMail, the KDE mail client.
    Copyright (c) 2001 Marc Mutz <mutz@kde.org>

    Copyright (C) 2013-2017 Laurent Montel <montel@kde.org>

    KMail is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License, version 2, as
    published by the Free Software Foundation.

    KMail is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

    In addition, as a special exception, the copyright holders give
    permission to link the code of this program with any edition of
    the Qt library by Trolltech AS, Norway (or with modified versions
    of Qt that use the same license as Qt), and distribute linked
    combinations including the two.  You must obey the GNU General
    Public License in all respects for all of the code used other than
    Qt.  If you modify this file, you may extend this exception to
    your version of the file, but you are not obligated to do so.  If
    you do not wish to do so, delete this exception statement from
    your version.
*/

#include "simplestringlisteditor.h"

#include <qinputdialog.h>
#include <kiconloader.h>
#include <QIcon>
#include <KLocalizedString>
#include "pimcommon_debug.h"
#include <QPushButton>
#include <QMenu>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>

//********************************************************
// SimpleStringListEditor
//********************************************************
using namespace PimCommon;

class PimCommon::SimpleStringListEditorPrivate
{
public:
    SimpleStringListEditorPrivate()
        : mListBox(nullptr),
          mAddButton(nullptr),
          mRemoveButton(nullptr),
          mModifyButton(nullptr),
          mUpButton(nullptr),
          mDownButton(nullptr),
          mButtonLayout(nullptr)
    {

    }

    QListWidget   *mListBox;
    QPushButton   *mAddButton;
    QPushButton   *mRemoveButton;
    QPushButton   *mModifyButton;
    QPushButton   *mUpButton;
    QPushButton   *mDownButton;
    QVBoxLayout   *mButtonLayout;
    QString mAddDialogLabel;
};

SimpleStringListEditor::SimpleStringListEditor(QWidget *parent,
        ButtonCode buttons,
        const QString &addLabel,
        const QString &removeLabel,
        const QString &modifyLabel,
        const QString &addDialogLabel)
    : QWidget(parent),
      d(new SimpleStringListEditorPrivate)
{
    setAddDialogLabel(addDialogLabel);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    QHBoxLayout *hlay = new QHBoxLayout(this);
    hlay->setMargin(0);

    d->mListBox = new QListWidget(this);

    d->mListBox->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(d->mListBox, &QListWidget::customContextMenuRequested, this, &SimpleStringListEditor::slotContextMenu);

    d->mListBox->setSelectionMode(QAbstractItemView::ExtendedSelection);
    hlay->addWidget(d->mListBox, 1);

    if (buttons == None) {
        qCDebug(PIMCOMMON_LOG) << "SimpleStringListBox called with no buttons."
                               "Consider using a plain QListBox instead!";
    }

    d->mButtonLayout = new QVBoxLayout(); // inherits spacing
    hlay->addLayout(d->mButtonLayout);

    if (buttons & Add) {
        if (addLabel.isEmpty()) {
            d->mAddButton = new QPushButton(i18n("&Add..."), this);
        } else {
            d->mAddButton = new QPushButton(addLabel, this);
        }
        d->mAddButton->setAutoDefault(false);
        d->mButtonLayout->addWidget(d->mAddButton);
        connect(d->mAddButton, &QPushButton::clicked, this, &SimpleStringListEditor::slotAdd);
    }

    if (buttons & Modify) {
        if (modifyLabel.isEmpty()) {
            d->mModifyButton = new QPushButton(i18n("&Modify..."), this);
        } else {
            d->mModifyButton = new QPushButton(modifyLabel, this);
        }
        d->mModifyButton->setAutoDefault(false);
        d->mModifyButton->setEnabled(false);   // no selection yet
        d->mButtonLayout->addWidget(d->mModifyButton);
        connect(d->mModifyButton, &QPushButton::clicked, this, &SimpleStringListEditor::slotModify);
        connect(d->mListBox, &QListWidget::itemDoubleClicked, this, &SimpleStringListEditor::slotModify);
    }

    if (buttons & Remove) {
        if (removeLabel.isEmpty()) {
            d->mRemoveButton = new QPushButton(i18n("&Remove"), this);
        } else {
            d->mRemoveButton = new QPushButton(removeLabel, this);
        }
        d->mRemoveButton->setAutoDefault(false);
        d->mRemoveButton->setEnabled(false);   // no selection yet
        d->mButtonLayout->addWidget(d->mRemoveButton);
        connect(d->mRemoveButton, &QPushButton::clicked, this, &SimpleStringListEditor::slotRemove);
    }

    if (buttons & Up) {
        if (!(buttons & Down)) {
            qCDebug(PIMCOMMON_LOG) << "Are you sure you want to use an Up button"
                                   "without a Down button??";
        }
        d->mUpButton = new QPushButton(QString(), this);
        d->mUpButton->setIcon(QIcon::fromTheme(QStringLiteral("go-up")));
        d->mUpButton->setIconSize(QSize(KIconLoader::SizeSmall, KIconLoader::SizeSmall));
        d->mUpButton->setAutoDefault(false);
        d->mUpButton->setEnabled(false);   // no selection yet
        d->mButtonLayout->addWidget(d->mUpButton);
        connect(d->mUpButton, &QPushButton::clicked, this, &SimpleStringListEditor::slotUp);
    }

    if (buttons & Down) {
        if (!(buttons & Up)) {
            qCDebug(PIMCOMMON_LOG) << "Are you sure you want to use a Down button"
                                   "without an Up button??";
        }
        d->mDownButton = new QPushButton(QString(), this);
        d->mDownButton->setIcon(QIcon::fromTheme(QStringLiteral("go-down")));
        d->mDownButton->setIconSize(QSize(KIconLoader::SizeSmall, KIconLoader::SizeSmall));
        d->mDownButton->setAutoDefault(false);
        d->mDownButton->setEnabled(false);   // no selection yet
        d->mButtonLayout->addWidget(d->mDownButton);
        connect(d->mDownButton, &QPushButton::clicked, this, &SimpleStringListEditor::slotDown);
    }

    d->mButtonLayout->addStretch(1);   // spacer

    connect(d->mListBox, &QListWidget::currentItemChanged, this, &SimpleStringListEditor::slotSelectionChanged);
    connect(d->mListBox, &QListWidget::itemSelectionChanged, this, &SimpleStringListEditor::slotSelectionChanged);
}

SimpleStringListEditor::~SimpleStringListEditor()
{
    delete d;
}

void SimpleStringListEditor::setUpDownAutoRepeat(bool b)
{
    if (d->mUpButton) {
        d->mUpButton->setAutoRepeat(b);
    }
    if (d->mDownButton) {
        d->mDownButton->setAutoRepeat(b);
    }
}

void SimpleStringListEditor::setStringList(const QStringList &strings)
{
    d->mListBox->clear();
    d->mListBox->addItems(strings);
}

void SimpleStringListEditor::appendStringList(const QStringList &strings)
{
    d->mListBox->addItems(strings);
}

QStringList SimpleStringListEditor::stringList() const
{
    QStringList result;
    const int numberOfItem(d->mListBox->count());
    result.reserve(numberOfItem);
    for (int i = 0; i < numberOfItem; ++i) {
        result << (d->mListBox->item(i)->text());
    }
    return result;
}

bool SimpleStringListEditor::containsString(const QString &str)
{
    const int numberOfItem(d->mListBox->count());
    for (int i = 0; i < numberOfItem; ++i) {
        if (d->mListBox->item(i)->text() == str) {
            return true;
        }
    }
    return false;
}

void SimpleStringListEditor::setButtonText(ButtonCode button, const QString &text)
{
    switch (button) {
    case Add:
        if (!d->mAddButton) {
            break;
        }
        d->mAddButton->setText(text);
        return;
    case Remove:
        if (!d->mRemoveButton) {
            break;
        }
        d->mRemoveButton->setText(text);
        return;
    case Modify:
        if (!d->mModifyButton) {
            break;
        }
        d->mModifyButton->setText(text);
        return;
    case Up:
    case Down:
        qCDebug(PIMCOMMON_LOG) << "SimpleStringListEditor: Cannot change text of"
                               "Up and Down buttons: they don't contains text!";
        return;
    default:
        if (button & All) {
            qCDebug(PIMCOMMON_LOG) << "No such button!";
        } else {
            qCDebug(PIMCOMMON_LOG) << "Can only set text for one button at a time!";
        }
        return;
    }

    qCDebug(PIMCOMMON_LOG) << "The requested button has not been created!";
}

void SimpleStringListEditor::addNewEntry()
{
    bool ok = false;
    const QString newEntry = QInputDialog::getText(this, i18n("New Value"),
                             d->mAddDialogLabel, QLineEdit::Normal, QString(),
                             &ok);
    if (ok && !newEntry.trimmed().isEmpty()) {
        insertNewEntry(newEntry);
    }
}

void SimpleStringListEditor::insertNewEntry(const QString &entry)
{
    QString newEntry = entry;
    // let the user verify the string before adding
    Q_EMIT aboutToAdd(newEntry);
    if (!newEntry.isEmpty() && !containsString(newEntry)) {
        d->mListBox->addItem(newEntry);
        slotSelectionChanged();
        Q_EMIT changed();
    }
}

void SimpleStringListEditor::slotAdd()
{
    addNewEntry();
}

void SimpleStringListEditor::slotRemove()
{
    const QList<QListWidgetItem *> selectedItems = d->mListBox->selectedItems();
    if (selectedItems.isEmpty()) {
        return;
    }
    for (QListWidgetItem *item : selectedItems) {
        delete d->mListBox->takeItem(d->mListBox->row(item));
    }
    slotSelectionChanged();
    Q_EMIT changed();
}

QString SimpleStringListEditor::modifyEntry(const QString &text)
{
    bool ok = false;
    QString newText = QInputDialog::getText(this, i18n("Change Value"),
                                            d->mAddDialogLabel, QLineEdit::Normal, text,
                                            &ok);
    Q_EMIT aboutToAdd(newText);

    if (!ok || newText.trimmed().isEmpty() || newText == text) {
        return QString();
    }

    return newText;
}

void SimpleStringListEditor::slotModify()
{
    QListWidgetItem *item = d->mListBox->currentItem();
    if (!item) {
        return;
    }
    const QString newText = modifyEntry(item->text());
    if (!newText.isEmpty()) {
        item->setText(newText);
        Q_EMIT changed();
    }
}

QList<QListWidgetItem *> SimpleStringListEditor::selectedItems() const
{
    QList<QListWidgetItem *> listWidgetItem;
    const int numberOfFilters = d->mListBox->count();
    for (int i = 0; i < numberOfFilters; ++i) {
        if (d->mListBox->item(i)->isSelected()) {
            listWidgetItem << d->mListBox->item(i);
        }
    }
    return listWidgetItem;
}

void SimpleStringListEditor::setAddDialogLabel(const QString &addDialogLabel)
{
    d->mAddDialogLabel = addDialogLabel.isEmpty() ? i18n("New entry:") : addDialogLabel;
}

void SimpleStringListEditor::slotUp()
{
    QList<QListWidgetItem *> listWidgetItem = selectedItems();
    if (listWidgetItem.isEmpty()) {
        return;
    }

    const int numberOfItem(listWidgetItem.count());
    const int currentRow = d->mListBox->currentRow();
    if ((numberOfItem == 1) && (currentRow == 0)) {
        qCDebug(PIMCOMMON_LOG) << "Called while the _topmost_ filter is selected, ignoring.";
        return;
    }
    bool wasMoved = false;

    for (int i = 0; i < numberOfItem; ++i) {
        const int posItem = d->mListBox->row(listWidgetItem.at(i));
        if (posItem == i) {
            continue;
        }
        QListWidgetItem *item = d->mListBox->takeItem(posItem);
        d->mListBox->insertItem(posItem - 1, item);

        wasMoved = true;
    }
    if (wasMoved) {
        Q_EMIT changed();
        d->mListBox->setCurrentRow(currentRow - 1);
    }
}

void SimpleStringListEditor::slotDown()
{
    QList<QListWidgetItem *> listWidgetItem = selectedItems();
    if (listWidgetItem.isEmpty()) {
        return;
    }

    const int numberOfElement(d->mListBox->count());
    const int numberOfItem(listWidgetItem.count());
    const int currentRow = d->mListBox->currentRow();
    if ((numberOfItem == 1) && (currentRow == numberOfElement - 1)) {
        qCDebug(PIMCOMMON_LOG) << "Called while the _last_ filter is selected, ignoring.";
        return;
    }

    int j = 0;
    bool wasMoved = false;
    for (int i = numberOfItem - 1; i >= 0; --i, j++) {
        const int posItem = d->mListBox->row(listWidgetItem.at(i));
        if (posItem == (numberOfElement - 1 - j)) {
            continue;
        }
        QListWidgetItem *item = d->mListBox->takeItem(posItem);
        d->mListBox->insertItem(posItem + 1, item);
        wasMoved = true;
    }
    if (wasMoved) {
        Q_EMIT changed();
        d->mListBox->setCurrentRow(currentRow + 1);
    }
}

void SimpleStringListEditor::slotSelectionChanged()
{

    QList<QListWidgetItem *> lstSelectedItems = d->mListBox->selectedItems();
    const int numberOfItemSelected(lstSelectedItems.count());
    const bool uniqItemSelected = (numberOfItemSelected == 1);
    // if there is one, item will be non-null (ie. true), else 0
    // (ie. false):
    if (d->mRemoveButton) {
        d->mRemoveButton->setEnabled(!lstSelectedItems.isEmpty());
    }

    if (d->mModifyButton) {
        d->mModifyButton->setEnabled(uniqItemSelected);
    }

    const int currentIndex = d->mListBox->currentRow();

    const bool aItemIsSelected = !lstSelectedItems.isEmpty();
    const bool allItemSelected = (d->mListBox->count() == numberOfItemSelected);
    const bool theLast = (currentIndex >= d->mListBox->count() - 1);
    const bool theFirst = (currentIndex == 0);

    if (d->mUpButton) {
        d->mUpButton->setEnabled(aItemIsSelected && ((uniqItemSelected && !theFirst) ||
                                 (!uniqItemSelected)) && !allItemSelected);
    }
    if (d->mDownButton) {
        d->mDownButton->setEnabled(aItemIsSelected &&
                                   ((uniqItemSelected && !theLast) ||
                                    (!uniqItemSelected)) && !allItemSelected);
    }
}

void SimpleStringListEditor::slotContextMenu(const QPoint &pos)
{
    QList<QListWidgetItem *> lstSelectedItems = d->mListBox->selectedItems();
    const bool hasItemsSelected = !lstSelectedItems.isEmpty();
    QMenu *menu = new QMenu(this);
    if (d->mAddButton) {
        menu->addAction(d->mAddButton->text(), this, &SimpleStringListEditor::slotAdd);
    }
    if (d->mModifyButton && (lstSelectedItems.count() == 1)) {
        menu->addAction(d->mModifyButton->text(), this, &SimpleStringListEditor::slotModify);
    }
    if (d->mRemoveButton && hasItemsSelected) {
        menu->addSeparator();
        menu->addAction(d->mRemoveButton->text(), this, &SimpleStringListEditor::slotRemove);
    }
    menu->exec(d->mListBox->mapToGlobal(pos));
    delete menu;
}

QSize SimpleStringListEditor::sizeHint() const
{
    // Override height because we want the widget to be tall enough to fit the
    // button columns, but we want to allow it to be made smaller than list
    // sizeHint().height()
    QSize sh = QWidget::sizeHint();
    sh.setHeight(d->mButtonLayout->minimumSize().height());
    return sh;
}
