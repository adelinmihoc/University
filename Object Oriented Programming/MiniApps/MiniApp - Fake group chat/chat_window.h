#ifndef CHAT_WINDOW_H
#define CHAT_WINDOW_H

#include <QWidget>
#include "Observer.h"
#include "user.h"
#include "chat_session.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Chat_window; }
QT_END_NAMESPACE

class Chat_window : public QWidget, public Observer
{
    Q_OBJECT

public:
    Chat_window(User* u, Chat_session* cs, QWidget *parent = nullptr);
    ~Chat_window();

    void update() override;

private:
    Ui::Chat_window *ui;
    User* user;
    Chat_session* chat_session;

    void populate_list();
    void send_button_handler();

};
#endif // CHAT_WINDOW_H








