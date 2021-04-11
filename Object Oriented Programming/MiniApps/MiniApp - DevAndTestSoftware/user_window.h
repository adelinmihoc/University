#ifndef USER_WINDOW_H
#define USER_WINDOW_H

#include <QMainWindow>
#include "controller.h"


QT_BEGIN_NAMESPACE
namespace Ui { class User_window; }
QT_END_NAMESPACE

class User_window : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    User_window(Controller* c, User* u, QWidget *parent = nullptr);
    ~User_window();

    void update() override;

private:
    Ui::User_window *ui;
    User* user;
    Controller* controller;

    void populate_issues_list();

    void add_button_handler();
    void remove_button_handler();
    void solve_button_handler();
};
#endif // USER_WINDOW_H
