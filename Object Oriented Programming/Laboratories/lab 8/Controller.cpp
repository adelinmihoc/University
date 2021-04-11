#include "Controller.h"


void Enchantment::addGuardianStatue(const std::string& powerWordName, const std::string& material, const int& age, const std::string& corporealForm) {
    GuardianStatue guardStat = { powerWordName, material, age, corporealForm };
    try {
        encyclopedia.addGuardianStatueFile(guardStat);
    }
    catch (std::exception&) {
        throw std::exception();
    }
}


void Enchantment::deleteGuardianStatue(const std::string& powerWordName) {
    try {
        encyclopedia.deleteGuardianStatueFile(powerWordName);
    }
    catch (std::exception&) {
        throw std::exception();
    }
}


void Enchantment::updateGuardianStatue(const std::string& powerWordName, const std::string& newMaterial, const int& newAge, const std::string& newCorporealForm) {
    GuardianStatue guardStat = { powerWordName, newMaterial, newAge, newCorporealForm };
    try {
        encyclopedia.updateGuardianStatueFile(guardStat);
    }
    catch (std::exception&) {
        throw std::exception();
    }
}


int Enchantment::getSize() {
    return encyclopedia.sizeFile();
}


std::vector<GuardianStatue> Enchantment::getAllGuardianStatues() {
    return encyclopedia.getAllFile();
}


////////////////////////////////////////////////////////////////////////////


std::vector<GuardianStatue> Enchantment::getAllApprenticeGuardianStatues()
{
    return apprenticeEncyclopedia.getAllStatues();
}


void Enchantment::initialiseIterator() {
    std::vector<GuardianStatue> stats = this->encyclopedia.getAllFile();
    for (const auto & stat : stats) {
        this->encyclopediaIterator.add(stat);
    }
}


GuardianStatue Enchantment::nextGuardianStatues() {
    GuardianStatue nextStatue = this->encyclopediaIterator.getStatue();
    this->encyclopediaIterator.next();
    return nextStatue;
}


void Enchantment::saveGuardianStatue(const std::string& powerWordName) {
    int positionOfStat = this->searchGuardianStatue(powerWordName);
    if (positionOfStat == -1) {
        throw std::exception();
    }
    this->apprenticeEncyclopedia.addStatue(this->encyclopedia.getAllFile()[positionOfStat]);
}


int Enchantment::searchGuardianStatue(const std::string& powerWordName) {
    for (int i = 0; i < this->encyclopedia.sizeFile(); i++) {
        if (this->encyclopedia.getAllFile()[i].getPowerWordName() == powerWordName) {
            return i;
        }
    }
    return -1;
}


std::vector<GuardianStatue> Enchantment::getAllApprenticesStatuesByMaterial(const std::string& material) {
    std::vector<GuardianStatue> result;
    std::vector<GuardianStatue> allStatues = this->getAllApprenticeGuardianStatues();
    for (auto & allStatue : allStatues) {
        if (allStatue.getMaterial() == material) {
            result.push_back(allStatue);
        }
    }
    if (result.empty()) {
        return this->getAllGuardianStatues();
    }
    return result;
}



std::vector<GuardianStatue> Enchantment::getAllApprenticeStatuesByMaterialAndAge(const std::string& material, int age) {
    std::vector<GuardianStatue> result;
    std::vector<GuardianStatue> allStatues = this->getAllApprenticesStatuesByMaterial(material);
    for (auto & allStatue : allStatues) {
        if (allStatue.getAge() < age) {
            result.push_back(allStatue);
        }
    }
    return result;
}

void Enchantment::setFilePath(std::string& filepath) {
    this->encyclopedia.setFileName(filepath);
}
