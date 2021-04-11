#ifndef BIDDERWITHPHOT_H
#define BIDDERWITHPHOT_H

#include <QWidget>
#include "auctioneer.h"

namespace Ui {
class BidderWithPhot;
}

class BidderWithPhot : public QWidget, public Observer
{
    Q_OBJECT

public:
    explicit BidderWithPhot(Auctioneer* auct, QWidget *parent = nullptr);
    ~BidderWithPhot();

    // implements the update method of the observer -
    // it will update the description of the current house and the price
    void update() override;

private:
    Ui::BidderWithPhot *ui;
    Auctioneer* auct;
};

#endif // BIDDERWITHPHOT_H
