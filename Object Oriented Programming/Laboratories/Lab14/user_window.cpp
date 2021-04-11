#include "user_window.h"
#include "ui_user_window.h"
#include "mylist_widget.h"
#include "Backend/exceptions.h"
#include <QMessageBox>


User_window::User_window(Controller* ctrl, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::User_window),
    controller(ctrl)
{
    ui->setupUi(this);
    this->connect_signals_and_slots();
    General_listView_model* _model = new General_listView_model{this->controller};
    _model->set_type_of_data("user_statues");
    this->model = _model;
}

User_window::~User_window()
{
    delete ui;
}

void User_window::connect_signals_and_slots() {
    QObject::connect(this->ui->mylist_pushButton, &QPushButton::clicked, this, &User_window::mylist_button_handler);
    QObject::connect(this->ui->next_pushButton, &QPushButton::clicked, this, &User_window::next_button_handler);
    QObject::connect(this->ui->save_pushButton, &QPushButton::clicked, this, &User_window::save_button_handler);
    QObject::connect(this->ui->filter_pushButton, &QPushButton::clicked, this, &User_window::filter_button_handler);
    QObject::connect(this->ui->myfile_location_pushButton, &QPushButton::clicked, this, &User_window::myfile_location_button_handler);
}

void User_window::mylist_button_handler() {
    try {
        Mylist_widget* myl_w = new Mylist_widget{this->model};
        myl_w->show();
    } catch (Exception& e) {
        QMessageBox::critical(this, "Exception", e.what());
    }
}

void User_window::filter_button_handler() {
    try {
        std::string material = this->ui->material_lineEdit->text().toStdString();
        int age = this->ui->age_lineEdit->text().toInt();
        this->ui->filter_listWidget->clear();
        for (auto s : this->controller->__user_filter_statues(material, age)) {
            QListWidgetItem* item = new QListWidgetItem{QString::fromStdString(s.get_power_word_name() + " | " + s.get_material() + " | " + std::to_string(s.get_age()) + " | " + s.get_corporeal_form())};
            this->ui->filter_listWidget->addItem(item);
        }
    } catch (Exception& e) {
        QMessageBox::critical(this, "Exception", e.what());
    }
}

void User_window::next_button_handler() {
    try {
        Guardian_statue stat = this->controller->__user_next_statue();
        this->ui->next_lineEdit->setText(QString::fromStdString(stat.get_power_word_name()));
    } catch (Exception& e) {
        QMessageBox::critical(this, "Exception", e.what());
    }
}

void User_window::save_button_handler() {
    std::string name = this->ui->name_lineEdit->text().toStdString();
    try {
        this->controller->__user_save_statue(name);
        QModelIndex idx1 = model->index(0);
        QModelIndex idx2 = model->index(this->controller->get_admin_repository_size());
        this->model->dataChanged(idx1, idx2);
    } catch (Exception& e) {
        QMessageBox::critical(this, "Exception", e.what());
    }
}


void User_window::myfile_location_button_handler() {
    try {
        this->controller->__user_set_file_path(this->ui->myfile_location_lineEdit->text().toStdString());
        QModelIndex idx1 = model->index(0);
        QModelIndex idx2 = model->index(this->controller->get_admin_repository_size());
        this->model->dataChanged(idx1, idx2);
    } catch (Exception& e) {
        QMessageBox::critical(this, "Exception", e.what());

    }
}




