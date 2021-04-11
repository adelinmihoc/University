#include "user_window.h"

#include <QApplication>
#include "users.h"
#include "search_window.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Questions* questions = new Questions{};
    Answers* answers = new Answers{};
    Users* users = new Users{};

    Controller* ctrl = new Controller{questions, answers};

    for (auto u : users->get_all()) {
        User_window* w = new User_window{ctrl, u};
        w->setWindowTitle(QString::fromStdString(u.get_name()));
        w->show();
    }

    Search_window* s_w = new Search_window{ctrl};
    s_w->setWindowTitle("Search window");
    s_w->show();

    return a.exec();
}
