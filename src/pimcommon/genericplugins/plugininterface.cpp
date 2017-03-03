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

#include "plugininterface.h"
#include "helper_p.h"
#include "genericpluginmanager.h"
#include "pimcommon_debug.h"

#include <KActionCollection>
#include <KXMLGUIClient>
#include <QAction>

#include "genericplugin.h"

using namespace PimCommon;

class PimCommon::PluginInterfacePrivate
{
public:
    PluginInterfacePrivate()
        : mParentWidget(nullptr),
          mActionCollection(nullptr)
    {

    }
    QString mPluginName;
    QString mServiceTypeName;
    QWidget *mParentWidget;
    KActionCollection *mActionCollection;
    QVector<PimCommon::GenericPluginInterface *> mListGenericInterface;
};

PluginInterface::PluginInterface(QObject *parent)
    : QObject(parent),
      d(new PimCommon::PluginInterfacePrivate)
{
}

PluginInterface::~PluginInterface()
{
    delete d;
}

void PimCommon::PluginInterface::setActionCollection(KActionCollection *ac)
{
    d->mActionCollection = ac;
}

void PluginInterface::initializePlugins()
{
    PimCommon::GenericPluginManager::self()->setPluginName(d->mPluginName);
    PimCommon::GenericPluginManager::self()->setServiceTypeName(d->mServiceTypeName);
    if (!PimCommon::GenericPluginManager::self()->initializePlugins()) {
        qCDebug(PIMCOMMON_LOG) << " Impossible to initialize plugins";
    }
}

void PluginInterface::setPluginName(const QString &name)
{
    d->mPluginName = name;
}

void PluginInterface::setServiceTypeName(const QString &name)
{
    d->mServiceTypeName = name;
}

void PluginInterface::createPluginInterface()
{
    if (!d->mActionCollection) {
        qCWarning(PIMCOMMON_LOG) << "Missing action collection";
        return;
    }
    Q_FOREACH (PimCommon::GenericPlugin *plugin, PimCommon::GenericPluginManager::self()->pluginsList()) {
        if (plugin->isEnabled()) {
            PimCommon::GenericPluginInterface *interface = static_cast<PimCommon::GenericPluginInterface *>(plugin->createInterface(d->mActionCollection, this));
            interface->setParentWidget(d->mParentWidget);
            interface->setPlugin(plugin);
            connect(interface, &PimCommon::GenericPluginInterface::emitPluginActivated, this, &PluginInterface::slotPluginActivated);
            d->mListGenericInterface.append(interface);
        }
    }
}

void PluginInterface::initializeInterfaceRequires(PimCommon::AbstractGenericPluginInterface *interface)
{
    Q_UNUSED(interface)
}

QString PluginInterface::actionXmlExtension(ActionType::Type type)
{
    switch (type) {
    case PimCommon::ActionType::Tools:
        return QStringLiteral("_plugins_tools");
    case PimCommon::ActionType::Edit:
        return QStringLiteral("_plugins_edit");
    case PimCommon::ActionType::File:
        return QStringLiteral("_plugins_file");
    case PimCommon::ActionType::Action:
        return QStringLiteral("_plugins_actions");
    case PimCommon::ActionType::PopupMenu:
        return QStringLiteral("_popupmenu_actions");
    case PimCommon::ActionType::ToolBar:
        return QStringLiteral("_toolbar_actions");
    }
    return {};
}

void PluginInterface::slotPluginActivated(PimCommon::AbstractGenericPluginInterface *interface)
{
    initializeInterfaceRequires(interface);
    if (interface) {
        interface->exec();
    }
}

void PluginInterface::setParentWidget(QWidget *widget)
{
    d->mParentWidget = widget;
}

void PluginInterface::initializePluginActions(const QString &prefix, KXMLGUIClient *guiClient)
{
    if (guiClient->factory()) {
        QHashIterator<PimCommon::ActionType::Type, QList<QAction *> > localActionsType(actionsType());
        while (localActionsType.hasNext()) {
            localActionsType.next();
            QList<QAction *> lst = localActionsType.value();
            if (!lst.isEmpty()) {
                const QString actionlistname = prefix + PimCommon::PluginInterface::actionXmlExtension(localActionsType.key());
                guiClient->unplugActionList(actionlistname);
                guiClient->plugActionList(actionlistname, lst);
            }
        }
    }
}

void PluginInterface::updateActions(int numberOfSelectedItems, int numberOfSelectedCollections)
{
    for (PimCommon::GenericPluginInterface *interface : qAsConst(d->mListGenericInterface)) {
        interface->updateActions(numberOfSelectedItems, numberOfSelectedCollections);
    }
}

QHash<PimCommon::ActionType::Type, QList<QAction *> > PluginInterface::actionsType()
{
    QHash<PimCommon::ActionType::Type, QList<QAction *> > listType;
    for (PimCommon::GenericPluginInterface *interface : qAsConst(d->mListGenericInterface)) {
        PimCommon::ActionType actionType = interface->actionType();
        PimCommon::ActionType::Type type = actionType.type();
        QList<QAction *> lst = listType.value(type);
        if (!lst.isEmpty()) {
            QAction *act = new QAction(this);
            act->setSeparator(true);
            lst << act << actionType.action();
            listType.insert(type, lst);
        } else {
            listType.insert(type, QList<QAction *>() << actionType.action());
        }
        if (interface->plugin()->hasPopupMenuSupport()) {
            type = PimCommon::ActionType::PopupMenu;
            QList<QAction *> lst = listType.value(type);
            if (!lst.isEmpty()) {
                QAction *act = new QAction(this);
                act->setSeparator(true);
                lst << act << actionType.action();
                listType.insert(type, lst);
            } else {
                listType.insert(type, QList<QAction *>() << actionType.action());
            }
        }
        if (interface->plugin()->hasToolBarSupport()) {
            type = PimCommon::ActionType::ToolBar;
            QList<QAction *> lst = listType.value(type);
            if (!lst.isEmpty()) {
                QAction *act = new QAction(this);
                act->setSeparator(true);
                lst << act << actionType.action();
                listType.insert(type, lst);
            } else {
                listType.insert(type, QList<QAction *>() << actionType.action());
            }
        }
    }

    return listType;
}

QVector<PimCommon::PluginUtilData> PluginInterface::pluginsDataList() const
{
    return GenericPluginManager::self()->pluginsDataList();
}

QString PluginInterface::configGroupName() const
{
    return GenericPluginManager::self()->configGroupName();
}

QString PluginInterface::configPrefixSettingKey() const
{
    return GenericPluginManager::self()->configPrefixSettingKey();
}

PimCommon::GenericPlugin *PluginInterface::pluginFromIdentifier(const QString &id)
{
    return GenericPluginManager::self()->pluginFromIdentifier(id);
}