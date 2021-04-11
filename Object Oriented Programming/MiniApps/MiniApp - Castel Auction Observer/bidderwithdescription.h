#ifndef BIDDERWITHDESCRIPTION_H
#define BIDDERWITHDESCRIPTION_H

#include <QWidget>
#include "auctioneer.h"


namespace Ui {
class BidderWithDescription;
}

class BidderWithDescription : public QWidget, public Observer
{
    Q_OBJECT

public:
    explicit BidderWithDescription(Auctioneer* auct, QWidget *parent = nullptr);
    ~BidderWithDescription();

    void update() override;

private:
    Ui::BidderWithDescription *ui;
    Auctioneer* auct;
    void connectSignals();
};

#endif // BIDDERWITHDESCRIPTION_H
