#include "Repository.h"


/*int Encyclopedia::getSize() const {
    return statues.getSize();
}*/
int Encyclopedia::getSize() const {
    return statues.size();
}


/*void Encyclopedia::addStatue(const GuardianStatue& guardStat) {
    for (int i = 0; i < statues.getSize(); i++) {
        if (statues.getItem(i).getPowerWordName() == guardStat.getPowerWordName()) {
            throw std::exception();
        }
    }
    statues.addItem(guardStat);
}*/
void Encyclopedia::addStatue(const GuardianStatue &guardStat) {
    for (auto & statue : statues) {
        if (statue.getPowerWordName() == guardStat.getPowerWordName()) {
            throw std::exception();
        }
    }
    statues.push_back(guardStat);
}


/*void Encyclopedia::deleteStatue(const std::string& powerWordName) {
    for (int i = 0; i < statues.getSize(); i++) {
        if (statues.getItem(i).getPowerWordName() == powerWordName) {
            statues.deleteItem(i);
            return;
        }
    }
    throw std::exception();
}*/
void Encyclopedia::deleteStatue(const std::string &powerWordName) {
    for (int i = 0; i < statues.size(); i++) {
        if (statues[i].getPowerWordName() == powerWordName) {
            auto it = statues.begin() + i;
            statues.erase(it);
            return;
        }
    }
    throw  std::exception();
}


/*void Encyclopedia::updateStatue(const GuardianStatue& guardStat) {
    for (int i = 0; i < statues.getSize(); i++) {
        if (statues.getItem(i).getPowerWordName() == guardStat.getPowerWordName()) {
            statues.updateItem(i, guardStat);
            return;
        }
    }
    throw std::exception();
}*/
void Encyclopedia::updateStatue(const GuardianStatue &guardStat) {
    for (auto & statue : statues) {
        if (statue.getPowerWordName() == guardStat.getPowerWordName()) {
            statue = guardStat;
            return;
        }
    }
    throw std::exception();
}


/*
DynamicVector<GuardianStatue> Encyclopedia::getAllStatues() {
    auto allStatues = DynamicVector<GuardianStatue>();
    for (int i = 0; i < statues.getSize(); i++) {
        allStatues.addItem(statues.getItem(i));
    }
    return allStatues;
}*/
std::vector<GuardianStatue> Encyclopedia::getAllStatues() {
    auto allStatues = std::vector<GuardianStatue>();
    for (const auto & statue : statues) {
        allStatues.push_back(statue);
    }
    return allStatues;
}

