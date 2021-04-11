#ifndef ADMIN_LISTVIEW_MODEL_H
#define ADMIN_LISTVIEW_MODEL_H

#include <qabstractitemmodel.h>
#include "Backend/controller.h"


class General_listView_model : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit General_listView_model(Controller* ctrl);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void set_type_of_data(std::string type);

private:
    Controller* controller;
    std::string type_of_data;
};

#endif // ADMIN_LISTVIEW_MODEL_H
