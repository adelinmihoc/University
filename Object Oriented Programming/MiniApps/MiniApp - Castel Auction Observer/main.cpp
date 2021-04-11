#include "mainwindow.h"

#include <QApplication>
#include "auctioneer.h"
#include "bidderwithdescription.h"
#include "bidderwithphoto.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Auctioneer* auct = new Auctioneer();
    auct->addCastle("Highclere Castle", "/home/adelin/OneDirToRuleThemAll/oop/CastelAuctionObserver/highclere.jpg", "England", 4000, 4000);
    auct->addCastle("Chambord Castle", "/home/adelin/OneDirToRuleThemAll/oop/CastelAuctionObserver/chambord.jpg", "France", 3200, 3200);

    BidderWithDescription bidderDesc1 { auct };
    bidderDesc1.show();
    BidderWithDescription bidderDesc2 { auct };
    bidderDesc2.show();

    BidderWithPhot bidderPhot { auct };
    bidderPhot.show();

    MainWindow w { auct };
    w.show();
    return a.exec();
}
