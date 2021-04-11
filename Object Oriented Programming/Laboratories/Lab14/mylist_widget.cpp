#include "mylist_widget.h"
#include "ui_mylist_widget.h"

Mylist_widget::Mylist_widget(General_listView_model* model, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mylist_widget),
    model{model}
{
    ui->setupUi(this);
    this->ui->statues_listView->setModel(this->model);
}

Mylist_widget::~Mylist_widget()
{
    delete ui;
}
