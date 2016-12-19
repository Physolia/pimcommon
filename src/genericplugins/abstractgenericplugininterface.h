/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

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

#ifndef AbstractGENERICPLUGININTERFACE_H
#define AbstractGENERICPLUGININTERFACE_H
#include <QObject>
#include "pimcommon_export.h"
class QAction;
class KActionCollection;
namespace PimCommon
{
class AbstractGenericPlugin;

class AbstractGenericPluginInterfacePrivate;
class PIMCOMMON_EXPORT AbstractGenericPluginInterface : public QObject
{
    Q_OBJECT
public:
    explicit AbstractGenericPluginInterface(QObject *parent = Q_NULLPTR);
    ~AbstractGenericPluginInterface();

    void setParentWidget(QWidget *parent);
    QWidget *parentWidget() const;

    void setPlugin(AbstractGenericPlugin *plugin);
    AbstractGenericPlugin *plugin() const;

    virtual void createAction(KActionCollection *ac) = 0;
    virtual void exec() = 0;

    virtual void showConfigureDialog(QWidget *parentWidget = Q_NULLPTR);

Q_SIGNALS:
    void emitPluginActivated(PimCommon::AbstractGenericPluginInterface *interface);

private:
    AbstractGenericPluginInterfacePrivate *const d;
};
}
#endif // AbstractGENERICPLUGININTERFACE_H