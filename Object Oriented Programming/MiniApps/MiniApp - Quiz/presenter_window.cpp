#include "presenter_window.h"
#include "ui_presenter_window.h"
#include "QMessageBox"


Presenter_window::Presenter_window(Controller* ctrl, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Presenter)
    , controller{ctrl}
{
    ui->setupUi(this);

    this->controller->add_observer(this);

    this->populate();

    QObject::connect(this->ui->add_pushButton, &QPushButton::clicked, this, &Presenter_window::add_button_handler);
}

void Presenter_window::add_button_handler() {
    int id = this->ui->id_lineEdit->text().toInt();
    if (id == 0 && this->ui->id_lineEdit->text() != "0") {
        QMessageBox* mssg = new QMessageBox{};
        mssg->critical(this, "Error", "Id not number!");
        return;
    }
    std::string text = this->ui->text_lineEdit->text().toStdString();
    std::string correct_answer = this->ui->correct_answer_lineEdit->text().toStdString();
    int score = this->ui->score_lineEdit->text().toInt();
    if (score == 0 && this->ui->score_lineEdit->text() != "0") {
        QMessageBox* mssg = new QMessageBox{};
        mssg->critical(this, "Error", "Score not number!");
        return;
    }
    try {
        this->controller->add_question(id, text, correct_answer, score);
    } catch(std::exception&) {
        QMessageBox* mssg = new QMessageBox{};
        mssg->critical(this, "Error", "Question failed to add!");
        return;
    }
}

void Presenter_window::populate() {
    this->ui->questions_listWidget->clear();

    for (auto q : this->controller->get_question_sorted_id()) {
        QListWidgetItem* item = new QListWidgetItem{QString::fromStdString(std::to_string(q.get_id()) + " | " + q.get_text() + " | " + q.get_correct_answer() + " | " + std::to_string(q.get_score()))};
        this->ui->questions_listWidget->addItem(item);
    }
}

void Presenter_window::update() {
    this->populate();
}

Presenter_window::~Presenter_window()
{
    delete ui;
}

