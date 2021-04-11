#ifndef SEARCH_WINDOW_H
#define SEARCH_WINDOW_H

#include <QWidget>
#include "controller.h"


namespace Ui {
class Search_window;
}

class Search_window : public QWidget
{
    Q_OBJECT
private:
    void populate();

public:
    explicit Search_window(Controller* ctrl, QWidget *parent = nullptr);
    ~Search_window();

private:
    Ui::Search_window *ui;
    Controller* controler;
};

#endif // SEARCH_WINDOW_H
