/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later

*/

#pragma once

#include "pimcommonakonadi_export.h"

#include <QDialog>
class KConfig;
namespace KLDAPWidgets
{
class LdapClientSearch;
}
namespace PimCommon
{
class CompletionConfigureDialogPrivate;
/**
 * @brief The CompletionConfigureDialog class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT CompletionConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CompletionConfigureDialog(QWidget *parent = nullptr);
    ~CompletionConfigureDialog() override;

    void load();
    void setEmailBlackList(const QStringList &lst);
    void setLdapClientSearch(KLDAPWidgets::LdapClientSearch *ldapSearch);
    void setRecentAddresses(const QStringList &lst);
    [[nodiscard]] bool recentAddressWasChanged() const;
    void storeAddresses(KConfig *config);

private:
    PIMCOMMONAKONADI_NO_EXPORT void slotSaveAndClose();
    PIMCOMMONAKONADI_NO_EXPORT void slotSave();
    PIMCOMMONAKONADI_NO_EXPORT void readConfig();
    PIMCOMMONAKONADI_NO_EXPORT void writeConfig();
    std::unique_ptr<CompletionConfigureDialogPrivate> const d;
};
}
