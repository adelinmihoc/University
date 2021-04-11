#include "chat_window.h"

#include <QApplication>
#include "user.h"
#include "chat_session.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Chat_session* ch = new Chat_session();

    User* user1 = new User{"abjectnicola", "Nicola"};
    User* user2 = new User{"stevesnyder", "Brian"};
    User* user3 = new User{"acidic_lewis", "Lewis"};
    User* user4 = new User{"helgeestebansnyder", "Esteban"};

    Chat_window w1{user1, ch};
    w1.setWindowTitle(QString::fromStdString(user1->get_username()));
    w1.show();
    Chat_window w2{user2, ch};
    w2.setWindowTitle(QString::fromStdString(user2->get_username()));
    w2.show();
    Chat_window w3{user3, ch};
    w3.setWindowTitle(QString::fromStdString(user3->get_username()));
    w3.show();
    Chat_window w4{user4, ch};
    w4.setWindowTitle(QString::fromStdString(user4->get_username()));
    w4.show();

    return a.exec();
}
