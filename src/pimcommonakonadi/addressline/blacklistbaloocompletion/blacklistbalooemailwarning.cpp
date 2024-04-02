/*
  SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#include "blacklistbalooemailwarning.h"
using namespace Qt::Literals::StringLiterals;

#include <KLocalizedString>
#include <QAction>

using namespace PimCommon;

BlackListBalooEmailWarning::BlackListBalooEmailWarning(QWidget *parent)
    : KMessageWidget(parent)
{
    setVisible(false);
    setCloseButtonVisible(false);
    setMessageType(Warning);
    setWordWrap(true);

    setText(i18n("The list was changed. Do you want to save before to make another search ?"));
    auto saveAction = new QAction(i18n("Save"), this);
    saveAction->setObjectName("saveblacklist"_L1);
    connect(saveAction, &QAction::triggered, this, &BlackListBalooEmailWarning::slotSaveBlackList);
    addAction(saveAction);

    auto searchAction = new QAction(i18n("Search"), this);
    searchAction->setObjectName("search"_L1);
    connect(searchAction, &QAction::triggered, this, &BlackListBalooEmailWarning::slotSearch);
    addAction(searchAction);

    auto cancelAction = new QAction(i18n("Cancel"), this);
    cancelAction->setObjectName("cancel"_L1);
    connect(cancelAction, &QAction::triggered, this, &BlackListBalooEmailWarning::animatedHide);
    addAction(cancelAction);
}

BlackListBalooEmailWarning::~BlackListBalooEmailWarning() = default;

void BlackListBalooEmailWarning::slotSaveBlackList()
{
    animatedHide();
    Q_EMIT saveChanges();
}

void BlackListBalooEmailWarning::slotSearch()
{
    animatedHide();
    Q_EMIT newSearch();
}

#include "moc_blacklistbalooemailwarning.cpp"
