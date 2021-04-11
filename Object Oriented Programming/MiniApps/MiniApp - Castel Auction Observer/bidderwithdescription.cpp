#include "bidderwithdescription.h"
#include "ui_bidderwithdescription.h"

BidderWithDescription::BidderWithDescription(Auctioneer* auct, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BidderWithDescription),
    auct{auct}
{
    ui->setupUi(this);

    //add this (wich is an observer) to the list of observers of the Auctioneer
    this->auct->addObserver(this);

    this->connectSignals();
}

BidderWithDescription::~BidderWithDescription()
{
    delete ui;
    this->auct->removeObserver(this);
}

void BidderWithDescription::connectSignals() {
    QObject::connect(this->ui->add_100_pushButton, &QPushButton::clicked, [&]() {
       this->auct->changePrice(this->auct->getCurrent(), 100);
    });
    QObject::connect(this->ui->add_1000_pushButton, &QPushButton::clicked, [&]() {
       this->auct->changePrice(this->auct->getCurrent(), 1000);
    });
}

void BidderWithDescription::update() {
    std::vector<Castle> castles = auct->getCastles();
    int current = auct->getCurrent();
    if (current < 0 || current >= int(castles.size())) {
        return;
    }

    Castle currentCastle = castles[current];

    // set description
    this->ui->description_label->setText(QString::fromStdString(currentCastle.getDescription() + ", " + currentCastle.getLocation()));

    // set last bidding
    this->ui->price_label->setText(QString{ "Last bid: "} + QString::number(currentCastle.getLastBidPrice()) + QString{ " thousands pounds" });

}






















