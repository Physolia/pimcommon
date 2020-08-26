/*
  Copyright (c) 2016-2020 Laurent Montel <montel@kde.org>

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

#include "configurepluginslistwidget.h"

#include <KSharedConfig>
#include <KLocalizedString>

#include <QPushButton>
#include <QToolButton>
#include <QTreeWidget>
#include <QHeaderView>
#include <QAction>
#include <QVBoxLayout>

using namespace PimCommon;
ConfigurePluginsListWidget::ConfigurePluginsListWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mListWidget = new QTreeWidget(this);
    mListWidget->setSortingEnabled(true);
    mListWidget->sortItems(0, Qt::AscendingOrder);
    mListWidget->setObjectName(QStringLiteral("listwidget"));
    mListWidget->setHeaderHidden(true);
    mListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    mListWidget->setColumnCount(2);
    mListWidget->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);

    connect(mListWidget, &QTreeWidget::itemSelectionChanged, this, &ConfigurePluginsListWidget::slotItemSelectionChanged);
    connect(mListWidget, &QTreeWidget::itemChanged, this, &ConfigurePluginsListWidget::slotItemChanged);

    mainLayout->addWidget(mListWidget);
}

ConfigurePluginsListWidget::~ConfigurePluginsListWidget()
{
}

void ConfigurePluginsListWidget::slotItemChanged(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(item);
    if (mInitializeDone) {
        if (column == 0) {
            Q_EMIT changed();
        }
    }
}

void ConfigurePluginsListWidget::slotItemSelectionChanged()
{
    QTreeWidgetItem *item = mListWidget->currentItem();
    if (PluginItem *pluginItem = dynamic_cast<PluginItem *>(item)) {
        Q_EMIT descriptionChanged(pluginItem->mDescription);
    }
}

void ConfigurePluginsListWidget::save()
{
}

void ConfigurePluginsListWidget::doLoadFromGlobalSettings()
{
    initialize();
    initializeDone();
}

void ConfigurePluginsListWidget::doResetToDefaultsOther()
{
}

void ConfigurePluginsListWidget::defaults()
{
}

void ConfigurePluginsListWidget::initialize()
{
}

void ConfigurePluginsListWidget::initializeDone()
{
    mInitializeDone = true;
}

void ConfigurePluginsListWidget::savePlugins(const QString &groupName, const QString &prefixSettingKey, const QVector<PluginItem *> &listItems)
{
    if (listItems.isEmpty()) {
        return;
    }
    QStringList enabledPlugins;
    QStringList disabledPlugins;
    for (PluginItem *item : listItems) {
        if (item->checkState(0) == Qt::Checked) {
            enabledPlugins << item->mIdentifier;
        } else {
            disabledPlugins << item->mIdentifier;
        }
    }
    PimCommon::PluginUtil::savePluginSettings(groupName,
                                              prefixSettingKey,
                                              enabledPlugins, disabledPlugins);
}

void ConfigurePluginsListWidget::fillTopItems(const QVector<PimCommon::PluginUtilData> &lst, const QString &topLevelItemName, const QString &groupName, const QString &prefixKey, QVector<PluginItem *> &itemsList, const QString &configureGroupName, bool checkable)
{
    itemsList.clear();
    if (!lst.isEmpty()) {
        QTreeWidgetItem *topLevel = new QTreeWidgetItem(mListWidget, {topLevelItemName});
        topLevel->setFlags(topLevel->flags() & ~Qt::ItemIsSelectable);
        const QPair<QStringList, QStringList> pair = PimCommon::PluginUtil::loadPluginSetting(groupName, prefixKey);
        for (const PimCommon::PluginUtilData &data : lst) {
            PluginItem *subItem = new PluginItem(topLevel);
            subItem->setText(0, data.mName);
            subItem->mIdentifier = data.mIdentifier;
            subItem->mDescription = data.mDescription;
            subItem->mEnableByDefault = data.mEnableByDefault;
            subItem->mHasConfigureSupport = data.mHasConfigureDialog;
            if (checkable) {
                const bool isPluginActivated = PimCommon::PluginUtil::isPluginActivated(pair.first, pair.second, data.mEnableByDefault, data.mIdentifier);
                subItem->mEnableFromUserSettings = isPluginActivated;
                subItem->setCheckState(0, isPluginActivated ? Qt::Checked : Qt::Unchecked);
            }
            if (data.mHasConfigureDialog) {
                QToolButton *but = new QToolButton(mListWidget);
                QAction *act = new QAction(but);
                const QStringList actData {
                    configureGroupName, data.mIdentifier
                };
                act->setData(actData);
                but->setDefaultAction(act);
                but->setIcon(QIcon::fromTheme(QStringLiteral("configure")));
                but->setText(i18n("..."));
                but->setFixedWidth(28);
                but->setToolTip(i18n("Configure"));
                but->setAutoFillBackground(true);
                but->setEnabled(subItem->mHasConfigureSupport);
                mListWidget->setItemWidget(subItem, 1, but);
                connect(but, &QToolButton::triggered, this, &ConfigurePluginsListWidget::slotConfigureClicked);
            }
            itemsList.append(subItem);
        }
    }
}

void ConfigurePluginsListWidget::slotConfigureClicked(QAction *act)
{
    if (act) {
        const QStringList lst = act->data().toStringList();
        if (lst.count() == 2) {
            Q_EMIT configureClicked(lst.at(0), lst.at(1));
        }
    }
}

void ConfigurePluginsListWidget::changeState(const QVector<PluginItem *> &items)
{
    for (PluginItem *item : items) {
        item->setCheckState(0, item->mEnableByDefault ? Qt::Checked : Qt::Unchecked);
    }
}

void ConfigurePluginsListWidget::resetToUserSettings(const QVector<PluginItem *> &items)
{
    for (PluginItem *item : items) {
        item->setCheckState(0, item->mEnableFromUserSettings ? Qt::Checked : Qt::Unchecked);
    }
}
