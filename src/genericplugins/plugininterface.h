/*
  Copyright (c) 2015-2016 Montel Laurent <montel@kde.org>

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

#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QObject>
#include <QVector>
#include <pimcommon/genericplugininterface.h>
#include "pimcommon_export.h"
class KActionCollection;
class QAction;
class KXMLGUIClient;
namespace PimCommon
{
class PluginInterfacePrivate;
class PIMCOMMON_EXPORT PluginInterface : public QObject
{
    Q_OBJECT
public:
    explicit PluginInterface(KActionCollection *ac, QObject *parent = Q_NULLPTR);
    ~PluginInterface();

    void setParentWidget(QWidget *widget);
    QHash<PimCommon::ActionType::Type, QList<QAction *> > actionsType() const;
    void createPluginInterface();

    void setPluginName(const QString &name);
    void setServiceTypeName(const QString &name);
    void initializePlugins();
    virtual void initializeInterfaceRequires(PimCommon::GenericPluginInterface *interface);
    static QString actionXmlExtension(PimCommon::ActionType::Type type);

    void initializePluginActions(const QString &prefix, KXMLGUIClient *guiClient);
    void updateActions(int numberOfSelectedItems, int numberOfSelectedCollections);

private Q_SLOTS:
    void slotPluginActivated(PimCommon::GenericPluginInterface *interface);

private:
    PluginInterfacePrivate *const d;
};
}

#endif // PLUGININTERFACE_H
