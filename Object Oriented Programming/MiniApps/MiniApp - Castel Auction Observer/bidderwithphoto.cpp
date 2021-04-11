#include "bidderwithphoto.h"
#include "ui_bidderwithphoto.h"

BidderWithPhot::BidderWithPhot(Auctioneer* auct, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BidderWithPhot),
    auct{auct}
{
    ui->setupUi(this);

    // add this as observer
    this->auct->addObserver(this);

    // handle signal from the button
    QObject::connect(this->ui->add2000_pushButton, &QPushButton::clicked, [&]() {
       this->auct->changePrice(this->auct->getCurrent(), 2000);
    });
}

BidderWithPhot::~BidderWithPhot()
{
    delete ui;
    this->auct->removeObserver(this);
}

void BidderWithPhot::update() {
    std::vector<Castle> castles = this->auct->getCastles();
    int current = this->auct->getCurrent();
    if (current < 0 || current > int(castles.size())) {
        return;
    }

    Castle currentCastle = castles[current];

    // set photo
    QPixmap pixmap(QString::fromStdString(currentCastle.getPhoto()));
    this->ui->photo_label->setPixmap(pixmap);

    // set last bidding price
    this->ui->price_label->setText(QString{"Last bid: "} + QString::number(currentCastle.getLastBidPrice()) + QString{" thousands pounds"});
}
