#ifndef MYLIST_WIDGET_H
#define MYLIST_WIDGET_H

#include <QWidget>
#include "general_listview_model.h"


namespace Ui {
class Mylist_widget;
}

class Mylist_widget : public QWidget
{
    Q_OBJECT

public:
    explicit Mylist_widget(General_listView_model* model, QWidget *parent = nullptr);
    ~Mylist_widget();

private:
    Ui::Mylist_widget *ui;
    General_listView_model* model;
};

#endif // MYLIST_WIDGET_H
