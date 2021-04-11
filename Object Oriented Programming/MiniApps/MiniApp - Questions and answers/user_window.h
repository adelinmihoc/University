#ifndef USER_WINDOW_H
#define USER_WINDOW_H

#include <QMainWindow>
#include "controller.h"
#include "user.h"


QT_BEGIN_NAMESPACE
namespace Ui { class User_window; }
QT_END_NAMESPACE

class User_window : public QMainWindow, public Observer
{
    Q_OBJECT

private:
    void populate();
    void populate_answers();
    void add_question_button_handler();
    void add_answer_button_handler();
    void vote_answer();
    void put_range();

public:
    User_window(Controller* ctrl, User u, QWidget *parent = nullptr);
    ~User_window();

    void update() override;

private:
    Ui::User_window *ui;
    Controller* controller;
    User user;
};
#endif // USER_WINDOW_H
