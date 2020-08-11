/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GENERICPLUGININTERFACE_H
#define GENERICPLUGININTERFACE_H

#include <QObject>
#include <PimCommon/AbstractGenericPluginInterface>
#include "pimcommonakonadi_export.h"
#include <AkonadiCore/Item>
namespace PimCommon {
class GenericPluginInterfacePrivate;
/**
 * @brief The GenericPluginInterface class
 * @author Laurent Montel <montel@kde.org>
 */
class PIMCOMMONAKONADI_EXPORT GenericPluginInterface : public AbstractGenericPluginInterface
{
    Q_OBJECT
public:
    explicit GenericPluginInterface(QObject *parent = nullptr);
    ~GenericPluginInterface();

    enum RequireType {
        None = 0,
        CurrentItems = 1,
        Items = 2,
        CurrentCollection = 3,
        Collections = 4
    };
    Q_ENUM(RequireType)
    Q_DECLARE_FLAGS(RequireTypes, RequireType)

    void setActionTypes(const QVector<ActionType> &type);
    void addActionType(ActionType type);
    Q_REQUIRED_RESULT QVector<ActionType> actionTypes() const;

    virtual void setCurrentItems(const Akonadi::Item::List &items);
    virtual void setItems(const Akonadi::Item::List &items);
    virtual void setCurrentCollection(const Akonadi::Collection &col);
    virtual void setCollections(const Akonadi::Collection::List &cols);

    virtual GenericPluginInterface::RequireTypes requires() const;

    virtual void updateActions(int numberOfSelectedItems, int numberOfSelectedCollections);

private:
    GenericPluginInterfacePrivate *const d;
};
}
Q_DECLARE_TYPEINFO(PimCommon::ActionType, Q_MOVABLE_TYPE);
#endif // GENERICPLUGININTERFACE_H
