#ifndef ADMIN_GUI_H
#define ADMIN_GUI_H

#include <qwidget.h>
#include <QLabel>
#include <QListWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTimer>
#include "lab9/Controller.h"


class ADMIN_GUI : public QWidget {
    Q_OBJECT
public:
    ADMIN_GUI(Enchantment* ctrl, QWidget* parent = 0);
    ~ADMIN_GUI();

private:
    Enchantment* controller;


    // title
    QLabel* title;

    // statues list
    QListWidget* statues_list;

    // form data
    QLineEdit* statue_name_edit;
    QLineEdit* statue_material_edit;
    QLineEdit* statue_age_edit;
    QLineEdit* statue_form_edit;

    // buttons from middle
    QPushButton* add_statue_button;
    QPushButton* delete_statue_button;
    QPushButton* update_statue_button;

    // bottom part
    QLineEdit* file_location_edit;
    QPushButton* file_location_button;
    QPushButton* user_mode_button;

    void init_admin_gui();
    void connect_signals_and_slots();
    void populate_statues_list();
    void list_item_changed();
    void add_statue_button_handler();
    void delete_statue_button_handler();
    void update_statue_button_handler();
    void user_mode_button_handler();
    void file_location_button_handler();

    int get_selected_index();

signals:
    void statues_update_signal();
    void add_statue_signal(const std::string& _name, const std::string& _material, const int _age, const std::string& _form);

public slots:
    void add_statue(const std::string& _name, const std::string& _material, const int _age, const std::string& _form);
    void update_buttons_colour();
};

#endif // ADMIN_GUI_H
