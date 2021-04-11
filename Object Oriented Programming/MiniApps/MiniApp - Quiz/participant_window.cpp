#include "participant_window.h"
#include "ui_participant_window.h"

Participant_window::Participant_window(Controller* ctrl, Participant p, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Participant_window),
    controller{ctrl},
    participant{p}
{
    ui->setupUi(this);

    this->controller->add_observer(this);

    this->populate();

    QObject::connect(this->ui->answer_pushButton, &QPushButton::clicked, this, &Participant_window::answer_button_handler);
}

void Participant_window::answer_button_handler() {
    if (this->ui->questions_listWidget->count() == 0) {
        return;
    }
    QModelIndexList index = this->ui->questions_listWidget->selectionModel()->selectedIndexes();
    if (index.size() == 0) {
        return;
    }
    int idx = index.at(0).row();
    Question q = this->controller->get_question_sorted_score()[idx];

    std::string text_answer = this->ui->answer_lineEdit->text().toStdString();
    if (text_answer == q.get_correct_answer()) {
        this->participant.set_score(this->participant.get_score() + q.get_score());
    }
    this->participant.add_answered_question(q.get_id());

    this->update();
}

void Participant_window::populate() {
    this->ui->score_lineEdit->setText(QString::number(this->participant.get_score()));
    this->ui->questions_listWidget->clear();

    for (auto q : this->controller->get_question_sorted_score()) {
        QListWidgetItem* item = new QListWidgetItem{QString::fromStdString(std::to_string(q.get_id()) + " | " + q.get_text() + " | " + std::to_string(q.get_score()))};
        if (this->participant.is_question_answered(q.get_id())) {
            item->setData(Qt::BackgroundRole, QColor("green"));
        }
        this->ui->questions_listWidget->addItem(item);
    }
}

void Participant_window::update() {
    this->populate();
}

Participant_window::~Participant_window()
{
    delete ui;
}
