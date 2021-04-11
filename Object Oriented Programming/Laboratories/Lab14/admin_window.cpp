#include "admin_window.h"
#include "ui_admin_window.h"
#include "Backend/exceptions.h"
#include <QMessageBox>
#include <qshortcut.h>


Admin_window::Admin_window(General_listView_model* model, Controller* ctrl, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin_window),
    controller(ctrl),
    model(model)
{
    ui->setupUi(this);
    this->connect_signals_and_slots();
    this->ui->statues_listView->setModel(this->model);
    this->model->set_type_of_data("admin_statues");
    if (this->controller->get_admin_repository_size() > 0) {
        QModelIndex idx = model->index(0);
        this->ui->statues_listView->setCurrentIndex(idx);
        this->change_selected_statue();
    }
    this->ui->file_location_lineEdit->setText(QString::fromStdString(this->controller->get_admin_repository()->get_filename()));
}

void Admin_window::connect_signals_and_slots() {
    QObject::connect(this->ui->statues_listView, &QListView::entered, this, &Admin_window::change_selected_statue);
    QObject::connect(this->ui->statues_listView, &QListView::pressed, this, &Admin_window::change_selected_statue);
    QObject::connect(this->ui->statues_listView, &QListView::activated, this, &Admin_window::change_selected_statue);
    QObject::connect(this->ui->add_pushButton, &QPushButton::clicked, this, &Admin_window::add_button_handler);
    QObject::connect(this->ui->delete_pushButton, &QPushButton::clicked, this, &Admin_window::delete_button_handler);
    QObject::connect(this->ui->update_pushButton, &QPushButton::clicked, this, &Admin_window::update_button_handler);
    QObject::connect(this->ui->undo_pushButton, &QPushButton::clicked, this, &Admin_window::undo_button_handler);
    QObject::connect(this->ui->redo_pushButton, &QPushButton::clicked, this, &Admin_window::redo_button_handler);
    QShortcut* undo_shortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
    QObject::connect(undo_shortcut, &QShortcut::activated, this, &Admin_window::undo_button_handler);
    QShortcut* redo_shortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);
    QObject::connect(redo_shortcut, &QShortcut::activated, this, &Admin_window::redo_button_handler);
    QObject::connect(this, SIGNAL(data_changed_signal()), this, SLOT(data_changed_slot()));
    QObject::connect(this->ui->save_file_location_pushButton, &QPushButton::clicked, this, &Admin_window::save_file_location_button_handler);
}

void Admin_window::save_file_location_button_handler() {
    try {
        this->controller->__admin_set_file_path(this->ui->file_location_lineEdit->text().toStdString());
        emit data_changed_signal();
    } catch (Exception& e) {
        QMessageBox::critical(this, "Exception", e.what());
    }
}

void Admin_window::add_button_handler() {
    std::string name = this->ui->name_lineEdit->text().toStdString();
    std::string material = this->ui->material_lineEdit->text().toStdString();
    int age = this->ui->age_lineEdit->text().toInt();
    if (age == 0 && this->ui->age_lineEdit->text().toStdString() != "0") {
        QMessageBox::critical(this, "Exception", "<Age> invalid");
        return;
    }
    std::string form = this->ui->form_lineEdit->text().toStdString();
    try {
        this->controller->__admin_add_statue(name, material, age, form);
        emit data_changed_signal();
    } catch (Exception& e) {
        QMessageBox::critical(this, "Exception", e.what());
    }
}

void Admin_window::delete_button_handler() {
    std::string name = this->ui->name_lineEdit->text().toStdString();
    try {
        this->controller->__admin_remove_statue(name);
        emit data_changed_signal();
    } catch (Exception& e) {
        QMessageBox::critical(this, "Exception", e.what());
    }
}

void Admin_window::update_button_handler() {
    std::string name = this->ui->name_lineEdit->text().toStdString();
    std::string material = this->ui->material_lineEdit->text().toStdString();
    int age = this->ui->age_lineEdit->text().toInt();
    if (age == 0 && this->ui->age_lineEdit->text().toStdString() != "0") {
        QMessageBox::critical(this, "Exception", "<Age> invalid");
        return;
    }
    std::string form = this->ui->form_lineEdit->text().toStdString();
    try {
        this->controller->__admin_update_statue(name, material, age, form);
        emit data_changed_signal();
    } catch (Exception& e) {
        QMessageBox::critical(this, "Exception", e.what());
    }
}

void Admin_window::undo_button_handler() {
    try {
        this->controller->undo();
        emit data_changed_signal();
    } catch (Exception& e) {
        QMessageBox::critical(this, "Exception", e.what());
    }
}

void Admin_window::redo_button_handler() {
    try {
        this->controller->redo();
        emit data_changed_signal();
    } catch (Exception& e) {
        QMessageBox::critical(this, "Exception", e.what());
    }
}


void Admin_window::data_changed_slot() {
    this->ui->name_lineEdit->clear();
    this->ui->material_lineEdit->clear();
    this->ui->age_lineEdit->clear();
    this->ui->form_lineEdit->clear();
    QModelIndex idx1 = model->index(0);
    QModelIndex idx2 = model->index(this->controller->get_admin_repository_size());
    this->model->dataChanged(idx1, idx2);
    if (this->controller->get_admin_repository_size() > 0) {
        QModelIndex idx = model->index(0);
        this->ui->statues_listView->setCurrentIndex(idx);
        this->change_selected_statue();
    }
}

int Admin_window::get_selected_index() {
    if (this->controller->get_admin_repository_size() < 1) {
        return -1;
    }
    QModelIndexList index = this->ui->statues_listView->selectionModel()->selectedIndexes();
    if (index.size() == 0) {
        this->ui->name_lineEdit->clear();
        this->ui->material_lineEdit->clear();
        this->ui->age_lineEdit->clear();
        this->ui->form_lineEdit->clear();
        return -1;
    }
    return index.at(0).row();
}

void Admin_window::change_selected_statue() {
    int idx = this->get_selected_index();
    if (idx == -1) {
        return;
    }
    Guardian_statue statue = this->controller->__admin_get_statues()[idx];
    this->ui->name_lineEdit->setText(QString::fromStdString(statue.get_power_word_name()));
    this->ui->material_lineEdit->setText(QString::fromStdString(statue.get_material()));
    this->ui->age_lineEdit->setText(QString::number(statue.get_age()));
    this->ui->form_lineEdit->setText(QString::fromStdString(statue.get_corporeal_form()));
}

Admin_window::~Admin_window()
{
    delete ui;
}
