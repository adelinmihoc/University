#include "user_window.h"
#include "ui_user_window.h"
#include <QMessageBox>


User_window::User_window(Controller* ctrl, User u, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::User_window)
    , controller{ctrl}
    , user{u}
{
    ui->setupUi(this);

    this->controller->add_observer(this);

    this->populate();

    QObject::connect(this->ui->questions_listWidget, &QListWidget::itemSelectionChanged, this, &User_window::populate_answers);
    QObject::connect(this->ui->answers_listWidget, &QListWidget::itemSelectionChanged, this, &User_window::put_range);
    QObject::connect(this->ui->add_question_pushButton, &QPushButton::clicked, this, &User_window::add_question_button_handler);
    QObject::connect(this->ui->add_answer_pushButton, &QPushButton::clicked, this, &User_window::add_answer_button_handler);
}

void User_window::put_range() {
    if (this->ui->answers_listWidget->count() == 0) {
        this->ui->spinBox->setValue(0);
        return;
    }
    if (this->ui->questions_listWidget->count() == 0) {
        this->ui->spinBox->setValue(0);
        return;
    }

    QModelIndexList index = this->ui->questions_listWidget->selectionModel()->selectedIndexes();
    if (index.size() == 0) {
        this->ui->spinBox->setValue(0);
        return;
    }

    int idx = index.at(0).row();
    Question q = this->controller->get_questions_sorted()[idx];

    if (this->ui->answers_listWidget->count() == 0) {
        this->ui->spinBox->setValue(0);
        return;
    }
    QModelIndexList index2 = this->ui->answers_listWidget->selectionModel()->selectedIndexes();
    if (index2.size() == 0) {
        this->ui->spinBox->setValue(0);
        return;
    }
    int idx2 = index2.at(0).row();
    Answer a = this->controller->get_answers()->get_answers_by_qid(q.get_id())[idx2];

    this->ui->spinBox->setValue(a.get_no_of_votes());
}

void User_window::vote_answer() {
    if (this->ui->questions_listWidget->count() == 0) {
        return;
    }

    QModelIndexList index = this->ui->questions_listWidget->selectionModel()->selectedIndexes();
    if (index.size() == 0) {
        return;
    }

    int idx = index.at(0).row();
    Question q = this->controller->get_questions_sorted()[idx];

    if (this->ui->answers_listWidget->count() == 0) {
        return;
    }
    QModelIndexList index2 = this->ui->answers_listWidget->selectionModel()->selectedIndexes();
    if (index2.size() == 0) {
        return;
    }
    int idx2 = index2.at(0).row();
    Answer a = this->controller->get_answers()->get_answers_by_qid(q.get_id())[idx2];

    //this->ui->spinBox->setValue(a.get_no_of_votes());

}

void User_window::add_question_button_handler() {
    std::string id = this->ui->id_lineEdit->text().toStdString();
    std::string question_text = this->ui->question_lineEdit->text().toStdString();
    try {
        this->controller->add_question(id, question_text, this->user.get_name());
    } catch (std::exception&) {
        QMessageBox* mssg = new QMessageBox{};
        mssg->critical(this, "Error", "Question not good enough!");
    }
}

void User_window::add_answer_button_handler() {
   std::string id = this->ui->answer_id_lineEdit->text().toStdString();

   if (this->ui->questions_listWidget->count() == 0) {
       return;
   }
   QModelIndexList index = this->ui->questions_listWidget->selectionModel()->selectedIndexes();
   if (index.size() == 0) {
       return;
   }
   int idx = index.at(0).row();
   Question q = this->controller->get_questions_sorted()[idx];
   std::string qid = q.get_id();

   std::string name = this->user.get_name();

   std::string text = this->ui->answer_lineEdit->text().toStdString();

   int no_of_upvotes = 0;

   try {
       this->controller->add_answer(id, qid, name, text, no_of_upvotes);
   } catch (std::exception&) {
       QMessageBox* mssg = new QMessageBox{};
       mssg->critical(this, "Error", "Answer not good enough!");
   }

}

void User_window::populate_answers() {
    this->ui->answers_listWidget->clear();

    if (this->ui->questions_listWidget->count() == 0) {
        return;
    }

    QModelIndexList index = this->ui->questions_listWidget->selectionModel()->selectedIndexes();
    if (index.size() == 0) {
        return;
    }

    int idx = index.at(0).row();
    Question q = this->controller->get_questions_sorted()[idx];

    for (auto a : this->controller->get_answers()->get_answers_by_qid(q.get_id())) {
        QListWidgetItem* item = new QListWidgetItem{QString::fromStdString(a.get_id() + " | " + a.get_name() + " | " + a.get_text() + " | " + std::to_string(a.get_no_of_votes()))};
        if (a.get_name() == user.get_name()) {
            item->setData(Qt::BackgroundRole, QColor("yellow"));
        }
        this->ui->answers_listWidget->addItem(item);
    }
}

void User_window::populate() {
    this->ui->questions_listWidget->clear();

    for (auto q : this->controller->get_questions_sorted()) {
        QListWidgetItem* item = new QListWidgetItem{QString::fromStdString(q.get_id() + " | " + q.get_text() + " | " + q.get_name())};
        if (q.get_name() == user.get_name()) {
            item->setData(Qt::BackgroundRole, QColor("yellow"));
        }
        this->ui->questions_listWidget->addItem(item);
    }
}

void User_window::update() {
    this->populate();
}

User_window::~User_window()
{
    delete ui;
}

