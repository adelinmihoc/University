#include "chat_window.h"
#include "ui_chat_window.h"
#include "QKeyEvent"
#include "qshortcut.h"

Chat_window::Chat_window(User* u, Chat_session* cs, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Chat_window)
    , user{u}
    , chat_session{cs}
{
    ui->setupUi(this);
    // add this as an observer for the subject chat_session
    this->chat_session->add_observer(this);

    // connect the slot send message
    QObject::connect(this->ui->pushButton, &QPushButton::clicked, this, &Chat_window::send_button_handler);

    QShortcut* enter_short = new QShortcut(QKeySequence(Qt::Key_Enter), this);
    QObject::connect(enter_short, &QShortcut::activated, this, &Chat_window::send_button_handler);

    // populate list (it is useful only for future implementation with archive messages) *not gonna happen
    this->populate_list();
}

Chat_window::~Chat_window()
{
    delete ui;
    this->chat_session->remove_observer(this);
}

void Chat_window::populate_list() {
    this->ui->messages_listWidget->clear();

    for (auto u_m : this->chat_session->get_messages()) {
        if (u_m->get_user() == this->user) {
            QString string_message ="[" + QString::fromStdString(u_m->get_message()->get_timestamp());
            string_message += "]\n";
            string_message += QString::fromStdString(u_m->get_message()->get_message());
            QListWidgetItem* item = new QListWidgetItem{string_message};
            item->setTextAlignment(Qt::AlignRight);
            item->setForeground(Qt::blue);
            this->ui->messages_listWidget->addItem(item);
        } else {
            QString string_message ="[" + QString::fromStdString(u_m->get_message()->get_timestamp());
            string_message += "]\n";
            string_message += QString::fromStdString(u_m->get_user()->get_name());
            string_message += ": ";
            string_message += QString::fromStdString(u_m->get_message()->get_message());
            QListWidgetItem* item = new QListWidgetItem{string_message};
            item->setTextAlignment(Qt::AlignLeft);
            this->ui->messages_listWidget->addItem(item);
        }
    }
}

void Chat_window::update() {
    this->populate_list();
}

void Chat_window::send_button_handler() {
    QString qtime = QTime::currentTime().toString();
    std::string time = qtime.toStdString();
    QString qmessage = this->ui->text_lineEdit->text();
    std::string message = qmessage.toStdString();
    Message* m = new Message{time, message};
    this->chat_session->add_message(this->user, m);
    this->ui->text_lineEdit->clear();
}
