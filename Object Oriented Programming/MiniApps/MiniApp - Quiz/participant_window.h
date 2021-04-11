#ifndef PARTICIPANT_WINDOW_H
#define PARTICIPANT_WINDOW_H

#include <QWidget>
#include "observer.h"
#include "controller.h"
#include "participant.h"


namespace Ui {
class Participant_window;
}

class Participant_window : public QWidget, public Observer
{
    Q_OBJECT
private:
    void populate();
    void answer_button_handler();

public:
    explicit Participant_window(Controller* ctrl, Participant p, QWidget *parent = nullptr);
    ~Participant_window();

    void update() override;

private:
    Ui::Participant_window *ui;
    Controller* controller;
    Participant participant;
};

#endif // PARTICIPANT_WINDOW_H
