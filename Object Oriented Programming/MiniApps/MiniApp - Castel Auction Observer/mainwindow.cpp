#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Auctioneer* auct, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , auct{auct}
{
    ui->setupUi(this);
    this->populateList();

    // connect solt start for start button:
    QObject::connect(this->ui->start_pushButton, &QPushButton::clicked, [&]() {
       this->setCurrent();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateList() {
    this->ui->castles_listWidget->clear();

    for (auto c : this->auct->getCastles()) {
        QListWidgetItem* item = new QListWidgetItem{QString::fromStdString(c.getDescription())};
        this->ui->castles_listWidget->addItem(item);
    }

    if (this->ui->castles_listWidget->count() > 0) {
        this->ui->castles_listWidget->setCurrentRow(0);
    }
}

void MainWindow::setCurrent() {
    if (this->ui->castles_listWidget->count() == 0) {
        return;
    }
    // get selected index
    QModelIndexList index = this->ui->castles_listWidget->selectionModel()->selectedIndexes();
    if (index.size() == 0) {
        return;
    }

    int idx = index.at(0).row();
    this->auct->setCurrent(idx);
}

