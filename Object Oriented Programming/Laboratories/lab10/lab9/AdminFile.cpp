#include "AdminFile.h"
#include "Exceptions.h"
//#include <Windows.h>


void ArchmageEncyclopedia::readAllFromFile() {
/*    if (this->encyclopediaName.empty()) {
        throw FileError("Path not set!\n");
    }*/
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
        throw FileError("Couldn't open file!\n");
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

void ArchmageEncyclopedia::display() {
    /*std::string aux = "notepad \"" + this->encyclopediaName + "\"";
    system(aux.c_str());*/
    //ShellExecuteA(NULL, NULL, "C:\\Program Files\\Windows NT\\Accessories\\wordpad.exe", this->encyclopediaName.c_str(), NULL, SW_SHOWMAXIMIZED);
}

