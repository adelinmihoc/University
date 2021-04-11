#ifndef AUCTIONEER_H
#define AUCTIONEER_H

#include "castle.h"
#include <vector>
#include "Observer.h"

class Auctioneer : public Observable {
private:
    std::vector<Castle> castles;
    int current;
public:
    Auctioneer() {}
    ~Auctioneer() {}
    void addCastle(std::string desc, std::string picture, std::string loc, int startPr, int lastBiddingPr) {
        castles.push_back(Castle{desc, picture, loc, startPr, lastBiddingPr});
    }
    std::vector<Castle> getCastles() {
        return this->castles;
    }
    int getCurrent() const {
        return this->current;
    }

    void changePrice(int castleIdx, int sumToAdd) {
        if (castleIdx < 0 || castleIdx >= int(this->castles.size())) {
            return;
        }
        Castle& currentCastle = this->castles[castleIdx];
        currentCastle.setLastBidPrice(currentCastle.getLastBidPrice() + sumToAdd);

        //!!
        this->notify();
    }
    void setCurrent(int c) {
        this->current = c;
        //!!
        this->notify();
    }
};


#endif // AUCTIONEER_H
