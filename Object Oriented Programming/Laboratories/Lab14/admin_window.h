#ifndef ADMIN_WINDOW_H
#define ADMIN_WINDOW_H

#include <QWidget>
#include "Backend/controller.h"
#include "general_listview_model.h"


namespace Ui {
class Admin_window;
}

class Admin_window : public QWidget
{
    Q_OBJECT

public:
    explicit Admin_window(General_listView_model* model, Controller* ctrl, QWidget *parent = nullptr);
    ~Admin_window();

private:
    Ui::Admin_window *ui;
    Controller* controller;
    General_listView_model* model;
    void connect_signals_and_slots();
    void change_selected_statue();
    void add_button_handler();
    void delete_button_handler();
    void update_button_handler();
    void undo_button_handler();
    void redo_button_handler();
    int get_selected_index();
    void save_file_location_button_handler();

signals:
    void data_changed_signal();

public slots:
    void data_changed_slot();
};

#endif // ADMIN_WINDOW_H
