#include "user_window.h"
#include "ui_user_window.h"

User_window::User_window(Controller* c, User* u, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::User_window)
    , user{u}
    , controller{c}
{
    ui->setupUi(this);

    this->controller->add_observer(this);

    if (user->get_type() == "Tester") {
        this->ui->solve_pushButton->hide();
    }
    if (user->get_type() == "Programmer") {
        this->ui->add_pushButton->hide();
    }

    this->populate_issues_list();

    // connect some slots
    QObject::connect(this->ui->add_pushButton, &QPushButton::clicked, this, &User_window::add_button_handler);
    QObject::connect(this->ui->remove_pushButton, &QPushButton::clicked, this, &User_window::remove_button_handler);
    QObject::connect(this->ui->solve_pushButton, &QPushButton::clicked, this, &User_window::solve_button_handler);
}

User_window::~User_window()
{
    delete ui;
    this->controller->remove_observer(this);
}

void User_window::update() {
    this->populate_issues_list();
}

void User_window::populate_issues_list() {
    this->ui->issues_listWidget->clear();

    for (auto is : this->controller->get_issues()) {
        QListWidgetItem* item = new QListWidgetItem{QString::fromStdString(is.get_description() + " | " + std::to_string(is.get_status()) + " | " + is.get_reporter() + " | " + is.get_solver())};
        this->ui->issues_listWidget->addItem(item);
    }
}

void User_window::add_button_handler() {
    this->controller->add_issue(*this->user, this->ui->description_lineEdit->text().toStdString());
}

void User_window::remove_button_handler() {
    this->controller->remove_issue(this->ui->description_lineEdit->text().toStdString());
}

void User_window::solve_button_handler() {
    this->controller->solve_issue(*this->user, this->ui->description_lineEdit->text().toStdString());
}

