#include "user_window.h"

#include <QApplication>
#include "tests.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    test_all();
    Controller ctrl{};

    User u1{"Billy", "Tester"};
    User u2{"Nicola", "Programmer"};
    User u3{"Andrew", "Programmer"};
    User u4{"Jeani", "Tester"};

    User_window w1{&ctrl, &u1};
    w1.setWindowTitle(QString::fromStdString(u1.get_name() + " - " + u1.get_type()));
    w1.show();
    User_window w2{&ctrl, &u2};
    w2.setWindowTitle(QString::fromStdString(u2.get_name() + " - " + u2.get_type()));
    w2.show();

    /*
    User_window w3{&ctrl, &u3};
    w3.setWindowTitle(QString::fromStdString(u3.get_name() + " - " + u3.get_type()));
    w3.show();
    User_window w4{&ctrl, &u4};
    w4.setWindowTitle(QString::fromStdString(u4.get_name() + " - " + u4.get_type()));
    w4.show();
    */
    return a.exec();
}
