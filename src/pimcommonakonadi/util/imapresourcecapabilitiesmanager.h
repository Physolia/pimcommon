/*
  Copyright (c) 2015-2017 Montel Laurent <montel@kde.org>

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

#ifndef IMAPRESOURCECAPABILITIESMANAGER_H
#define IMAPRESOURCECAPABILITIESMANAGER_H

#include <QObject>
#include <QHash>

#include "pimcommonakonadi_export.h"
class QDBusPendingCallWatcher;
namespace Akonadi {
class AgentInstance;
}
namespace PimCommon {
class PIMCOMMONAKONADI_EXPORT ImapResourceCapabilitiesManager : public QObject
{
    Q_OBJECT
public:
    explicit ImapResourceCapabilitiesManager(QObject *parent = nullptr);
    ~ImapResourceCapabilitiesManager();

    bool hasAnnotationSupport(const QString &identifier) const;

private:
    void slotInstanceAdded(const Akonadi::AgentInstance &instance);
    void slotInstanceRemoved(const Akonadi::AgentInstance &instance);
    void slotCapabilities(QDBusPendingCallWatcher *watcher);

    void init();
    void searchCapabilities(const QString &identifier);
    QHash<QString, bool> mImapResource;
};
}

#endif // IMAPRESOURCECAPABILITIESMANAGER_H
