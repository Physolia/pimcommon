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

#include "hubic_gui.h"
#include "storageservice/hubic/hubicstorageservice.h"
#include <QWidget>
#include <QStandardPaths>

#include "pimcommon_debug.h"

#include <KLocalizedString>
#include <QApplication>
#include <KAboutData>
#include <QCommandLineParser>

HubicTestWidget::HubicTestWidget(QWidget *parent)
    : ServiceTestWidget(parent)
{
    setStorageService(new PimCommon::HubicStorageService(this));
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QStandardPaths::setTestModeEnabled(true);
    KAboutData aboutData(QStringLiteral("hubic_gui"), i18n("hubic_Gui"), QStringLiteral("1.0"));
    aboutData.setShortDescription(i18n("Test for short hubic"));
    QCommandLineParser parser;
    KAboutData::setApplicationData(aboutData);
    parser.addVersionOption();
    parser.addHelpOption();
    aboutData.setupCommandLine(&parser);
    parser.process(app);
    aboutData.processCommandLine(&parser);

    HubicTestWidget *w = new HubicTestWidget;
    w->show();
    return app.exec();
}
