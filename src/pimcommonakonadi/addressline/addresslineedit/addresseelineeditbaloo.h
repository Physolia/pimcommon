/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "pimcommonakonadi_private_export.h"
#include <QStringList>

namespace PimCommon
{
class BalooCompletionEmail;
class PIMCOMMONAKONADI_TESTS_EXPORT AddresseeLineEditBaloo
{
public:
    AddresseeLineEditBaloo();
    ~AddresseeLineEditBaloo();

    [[nodiscard]] int balooCompletionSource() const;
    void setBalooCompletionSource(int value);
    void loadBalooBlackList();
    [[nodiscard]] QStringList cleanupEmailList(const QStringList &inputList);

    [[nodiscard]] QStringList balooBlackList() const;
    [[nodiscard]] QStringList domainExcludeList() const;

private:
    PimCommon::BalooCompletionEmail *const mBalooCompletionEmail;
    int mBalooCompletionSource = 0;
};
}
