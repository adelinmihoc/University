#include "presenter_window.h"

#include <QApplication>
#include "controller.h"
#include "participants.h"
#include "participant_window.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Questions* questions = new Questions{};
    Participants* participants = new Participants{};
    Controller* ctrl = new Controller{questions};

    for (auto p : participants->get_participants()) {
        Participant_window* p_w = new Participant_window{ctrl, p};
        p_w->setWindowTitle(QString::fromStdString(p.get_name()));
        p_w->show();
    }

    Presenter_window* w = new Presenter_window{ctrl};
    w->setWindowTitle("Presenter");
    w->show();


    return a.exec();
}
