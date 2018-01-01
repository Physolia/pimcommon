/*
  Copyright (c) 2016-2018 Montel Laurent <montel@kde.org>

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

#include "configurepluginswidget.h"
#include "configurepluginslistwidget.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KMessageWidget>
#include <KSharedConfig>

#include <QSplitter>
#include <QTextEdit>
#include <QVBoxLayout>

using namespace PimCommon;

ConfigurePluginsWidget::ConfigurePluginsWidget(QWidget *parent)
    : QWidget(parent)
{
    initLayout();
}

ConfigurePluginsWidget::ConfigurePluginsWidget(ConfigurePluginsListWidget *configurePluginListWidget, QWidget *parent)
    : QWidget(parent)
{
    initLayout(configurePluginListWidget);
}

ConfigurePluginsWidget::~ConfigurePluginsWidget()
{
    writeConfig();
}

void ConfigurePluginsWidget::initLayout(ConfigurePluginsListWidget *configurePluginListWidget)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);

    KMessageWidget *messageWidget = new KMessageWidget(this);
    messageWidget->setObjectName(QStringLiteral("messagewidget"));
    messageWidget->setText(i18n("Restart is necessary for applying the changes."));
    messageWidget->setCloseButtonVisible(false);
    layout->addWidget(messageWidget);

    mSplitter = new QSplitter(this);
    mSplitter->setObjectName(QStringLiteral("splitter"));
    mSplitter->setChildrenCollapsible(false);
    layout->addWidget(mSplitter);

    if (!configurePluginListWidget) {
        mConfigureListWidget = new ConfigurePluginsListWidget(this);
    } else {
        mConfigureListWidget = configurePluginListWidget;
    }
    mConfigureListWidget->setObjectName(QStringLiteral("configureListWidget"));
    mSplitter->addWidget(mConfigureListWidget);

    mDescription = new QTextEdit(this);
    mDescription->setObjectName(QStringLiteral("description"));
    mDescription->setReadOnly(true);

    mSplitter->addWidget(mDescription);

    connect(mConfigureListWidget, &ConfigurePluginsListWidget::descriptionChanged, mDescription, &QTextEdit::setText);
    connect(mConfigureListWidget, &ConfigurePluginsListWidget::changed, this, &ConfigurePluginsWidget::changed);

    initialize();
    readConfig();
}

void ConfigurePluginsWidget::save()
{
    mConfigureListWidget->save();
}

void ConfigurePluginsWidget::defaults()
{
    mConfigureListWidget->defaults();
}

void ConfigurePluginsWidget::doLoadFromGlobalSettings()
{
    mConfigureListWidget->doLoadFromGlobalSettings();
}

void ConfigurePluginsWidget::doResetToDefaultsOther()
{
    mConfigureListWidget->doResetToDefaultsOther();
}

void ConfigurePluginsWidget::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "ConfigurePluginsWidget");
    const QList<int> size = {400, 100};
    mSplitter->setSizes(group.readEntry("splitter", size));
}

void ConfigurePluginsWidget::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "ConfigurePluginsWidget");
    group.writeEntry("splitter", mSplitter->sizes());
}

void ConfigurePluginsWidget::initialize()
{
    mConfigureListWidget->initialize();
}
