#include "Repository.h"
#include "Exceptions.h"


int Encyclopedia::getSize() const {
    return statues.size();
}


void Encyclopedia::addStatue(const GuardianStatue &guardStat) {
    for (auto & statue : statues) {
        if (statue.getPowerWordName() == guardStat.getPowerWordName()) {
            throw RepositoryError("Statue already exists!\n");
        }
    }
    statues.push_back(guardStat);
}


void Encyclopedia::deleteStatue(const std::string &powerWordName) {
    for (int i = 0; i < statues.size(); i++) {
        if (statues[i].getPowerWordName() == powerWordName) {
            auto it = statues.begin() + i;
            statues.erase(it);
            return;
        }
    }
    throw  RepositoryError("Statue doesn't exist!\n");
}


void Encyclopedia::updateStatue(const GuardianStatue &guardStat) {
    for (auto & statue : statues) {
        if (statue.getPowerWordName() == guardStat.getPowerWordName()) {
            statue = guardStat;
            return;
        }
    }
    throw RepositoryError("Statue doesn't exist!\n");
}


std::vector<GuardianStatue> Encyclopedia::getAllStatues() {
    auto allStatues = std::vector<GuardianStatue>();
    for (const auto & statue : statues) {
        allStatues.push_back(statue);
    }
    return allStatues;
}

