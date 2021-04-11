#ifndef USER_GUI_H
#define USER_GUI_H
#include <QLabel>
#include <qwidget.h>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QListWidget>
#include <lab9/Controller.h>



class USER_GUI : public QWidget {
    Q_OBJECT;
public:
    USER_GUI(Enchantment ctrl, QWidget* parent = 0);
    ~USER_GUI();
private:
    Enchantment controller;

    // title
    QLabel* title;

    // upper part
    QLabel* current_statue_box_text_label;
    QLabel* current_statue_text_label;
    QPushButton* next_statue_button;

    // middle part
    QPushButton* mylist_button;
    QLineEdit* statue_name_edit;
    QPushButton* save_statue_button;

    QLineEdit* statue_material_edit;
    QLineEdit* statue_age_edit;
    QPushButton* filer_statues_button;

    QListWidget* statues_list;

    // bottom part
    QLineEdit* myfile_location_edit;
    QPushButton* myfile_location_button;
    QPushButton* admin_mode_button;

    void init_user_gui();
    void connect_signal_and_slots();
    void next_statue_button_handler();
    void populate_statues_list_mylist();
    void populate_statues_list_filter();
    void save_statue_button_handler();
    void admin_mode_button_handler();
    void myfile_location_button_handler();
    void mylist_button_handler();
    void filter_statues_button_handler();

signals:
    void statues_updated_mylist_signal();
    void statues_uptade_filter_signal();
    void add_statue_signal(const std::string& _name);

public slots:
    void update_buttons_background();
    void add_statue(const std::string& _name);
};

#endif // USER_GUI_H
