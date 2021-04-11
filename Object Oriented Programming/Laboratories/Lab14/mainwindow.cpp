#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Backend/tests.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QLineEdit>
#include <fstream>
#include <QTimer>
#include "admin_window.h"
#include "user_window.h"
#include "general_listview_model.h"
#include "Backend/exceptions.h"


MainWindow::MainWindow(Controller* _c, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controller(_c)
{
    ui->setupUi(this);
    this->connect_signals_and_slots();
    this->set_file_extensions_in_lineEdit();
    General_listView_model* _model = new General_listView_model{this->controller};
    this->model = _model;
}

void MainWindow::connect_signals_and_slots() {
    QObject::connect(this->ui->admin_pushButton, &QPushButton::clicked, this, &MainWindow::admin_mode_button_handler);
    QObject::connect(this->ui->user_pushButton, &QPushButton::clicked, this, &MainWindow::user_mode_button_handler);
    QObject::connect(this->ui->file_location_pushButton, &QPushButton::clicked, this, &MainWindow::file_location_button_handler);
    QObject::connect(this->ui->myfile_location_pushButton, &QPushButton::clicked, this, &MainWindow::myfile_location_button_handler);

}

void MainWindow::admin_mode_button_handler() {
    try {
        Admin_window* a_w = new Admin_window{this->model, this->controller};
        a_w->show();
    } catch (Exception& e) {
        QMessageBox::critical(this, "Exception", e.what());
    }
}

void MainWindow::user_mode_button_handler() {
    try {
        User_window* u_w = new User_window{this->controller};
        u_w->show();
    } catch (Exception& e) {
        QMessageBox::critical(this, "Exception", e.what());
    }
}

void MainWindow::set_file_extensions_in_lineEdit() {
    if (this->controller->get_admin_repository_type() == "memory") {
        this->ui->admin_lineEdit->hide();
        this->ui->admin_label->hide();
        this->ui->file_location_pushButton->hide();
    } else if (this->controller->get_admin_repository_type() == "csv_file") {
        this->ui->admin_lineEdit->setText("csv_file1.csv");
        this->ui->admin_lineEdit->setStyleSheet("QLineEdit {background-color: solid white;}");
    } else {
        this->ui->admin_lineEdit->setText("html_file1.html");
        this->ui->admin_lineEdit->setStyleSheet("QLineEdit {background-color: solid white;}");
    }
    if (this->controller->get_user_repository_type() == "memory") {
        this->ui->user_lineEdit->hide();
        this->ui->user_label->hide();
        this->ui->myfile_location_pushButton->hide();
    } else if (this->controller->get_user_repository_type() == "csv_file") {
        this->ui->user_lineEdit->setText("csv_file2.csv");
        this->ui->user_lineEdit->setStyleSheet("QLineEdit {background-color: solid white;}");
    } else {
        this->ui->user_lineEdit->setText("html_file1.html");
        this->ui->user_lineEdit->setStyleSheet("QLineEdit {background-color: solid white;}");
    }
}

void MainWindow::file_location_button_handler() {
    try {
        this->controller->__admin_set_file_path(this->ui->admin_lineEdit->text().toStdString());
        this->ui->file_location_pushButton->setStyleSheet("background-color:green");
        QTimer::singleShot(1500, this, SLOT(reset_button_color()));
    } catch (Exception& e) {
        QMessageBox::critical(this, "Exception", e.what());
    }

}

void MainWindow::reset_button_color() {
    QFont f{"DejaVu Sans", 15};
    this->ui->file_location_pushButton->setStyleSheet("background-color:solid white");
    this->ui->file_location_pushButton->setFont(f);
    this->ui->myfile_location_pushButton->setStyleSheet("background-color:solid white");
    this->ui->myfile_location_pushButton->setFont(f);
}

void MainWindow::myfile_location_button_handler() {
    try {
        this->controller->__user_set_file_path(this->ui->user_lineEdit->text().toStdString());
        this->ui->myfile_location_pushButton->setStyleSheet("background-color:green");
        QTimer::singleShot(1500, this, SLOT(reset_button_color()));
    } catch (Exception& e) {
        QMessageBox::critical(this, "Exception", e.what());
    }
}

void MainWindow::test_backend() {
    Tests test;
    test.test_all();
    qDebug("%s", test.get_message().c_str());
}

MainWindow::~MainWindow()
{
    delete ui;
}

