#ifndef PRESENTER_H
#define PRESENTER_H

#include <QWidget>
#include "controller.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Presenter; }
QT_END_NAMESPACE

class Presenter_window : public QWidget, public Observer
{
    Q_OBJECT
private:
    void populate();
    void add_button_handler();
public:
    Presenter_window(Controller* ctrl, QWidget *parent = nullptr);
    ~Presenter_window();
    void update() override;

private:
    Ui::Presenter *ui;
    Controller* controller;
};
#endif // PRESENTER_H
