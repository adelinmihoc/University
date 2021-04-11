#ifndef USER_WINDOW_H
#define USER_WINDOW_H

#include <QWidget>
#include "Backend/controller.h"
#include "general_listview_model.h"


namespace Ui {
class User_window;
}

class User_window : public QWidget
{
    Q_OBJECT

public:
    explicit User_window(Controller* ctrl, QWidget *parent = nullptr);
    ~User_window();

private:
    Ui::User_window *ui;
    Controller* controller;
    General_listView_model* model;
    void connect_signals_and_slots();
    void mylist_button_handler();
    void save_button_handler();
    void next_button_handler();
    void filter_button_handler();
    void myfile_location_button_handler();
};

#endif // USER_WINDOW_H
