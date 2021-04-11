#include "general_listview_model.h"
#include <iostream>


General_listView_model::General_listView_model(Controller* ctrl) :
    controller{ctrl}
{

}

void General_listView_model::set_type_of_data(std::string type) {
    this->type_of_data = type;
}

int General_listView_model::rowCount(const QModelIndex &parent) const
{
    if (this->type_of_data == "admin_statues") {
        return this->controller->get_admin_repository_size();
    }

    if (this->type_of_data == "user_statues") {
        return this->controller->get_user_repository_size();
    }
    if (!parent.isValid()) {
        return 0;
    }
    return 0;
}

QVariant General_listView_model::data(const QModelIndex &index, int role) const
{
    int row = index.row();

    Guardian_statue current_statue{"", "", 0, ""};

    if (this->type_of_data == "admin_statues") {
        current_statue = this->controller->__admin_get_statues()[row];
    }

    if (this->type_of_data == "user_statues") {
        current_statue = this->controller->__user_get_statues()[row];
    }

    if (role == Qt::DisplayRole) {
        return QString::fromStdString(current_statue.get_power_word_name() + " | " + current_statue.get_material() + " | " + std::to_string(current_statue.get_age()) + " | " + current_statue.get_corporeal_form());
    }

    return QVariant();
}
