#include "UserFile.h"

#include <utility>


void ArchmageEncyclopedia::readAllFromFile() {
    if (this->encyclopediaName == "newFile.txt") {
        std::ofstream newFile("newFile.txt");
        newFile.close();
    }
    this->statues.clear();
    std::ifstream in;
    in.open(this->encyclopediaName);
    if (in.is_open()) {
        GuardianStatue statue;
        bool flag = true;
        while(flag) {
            try {
                in >> statue;
                this->statues.push_back(statue);
            }
            catch (std::exception &) {
                flag = false;
            }
        }
    }
    else {
        throw std::exception();
    }
    in.close();
}


void ArchmageEncyclopedia::writeAllToFile() {
    std::ofstream out;
    out.open(this->encyclopediaName);
    if (out.is_open()) {
        //out.clear();
        for (auto & statue : this->statues) {
            out << statue;
        }
    }
    this->statues.clear();
    out.close();
}


int ArchmageEncyclopedia::sizeFile() {
    this->readAllFromFile();
    return this->getSize();
}


void ArchmageEncyclopedia::addGuardianStatueFile(const GuardianStatue &guardianStatue) {
    this->readAllFromFile();
    this->addStatue(guardianStatue);
    this->writeAllToFile();
}


void ArchmageEncyclopedia::deleteGuardianStatueFile(const std::string &powerName) {
    this->readAllFromFile();
    this->deleteStatue(powerName);
    this->writeAllToFile();
}


void ArchmageEncyclopedia::updateGuardianStatueFile(const GuardianStatue &guardianStatue) {
    this->readAllFromFile();
    this->updateStatue(guardianStatue);
    this->writeAllToFile();
}


std::vector<GuardianStatue> ArchmageEncyclopedia::getAllFile() {
    this->readAllFromFile();
    return this->getAllStatues();
}


void ArchmageEncyclopedia::setFileName(std::string& filename) {
    this->encyclopediaName = filename;
}

