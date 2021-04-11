#include "search_window.h"
#include "ui_search_window.h"

Search_window::Search_window(Controller* ctrl, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Search_window),
    controler{ctrl}
{
    ui->setupUi(this);

    QObject::connect(this->ui->search_lineEdit, &QLineEdit::textChanged, this, &Search_window::populate);
}

void Search_window::populate() {
    std::string input = this->ui->search_lineEdit->text().toStdString();
    std::string result = this->controler->get_search_result(input);
    this->ui->textEdit->setText(QString::fromStdString(result));
    if (input == "") {
        this->ui->textEdit->setText("");
    }
}

Search_window::~Search_window()
{
    delete ui;
}
