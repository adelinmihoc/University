#include "Controller.h"
#include "Exceptions.h"


void Enchantment::addGuardianStatue(const std::string& powerWordName, const std::string& material, const int& age, const std::string& corporealForm) {
    GuardianStatue guardStat = { powerWordName, material, age, corporealForm };
    try {
        GuardianStatueValidator::validate(guardStat);
        encyclopedia.addGuardianStatueFile(guardStat);
    }
    catch (std::exception & e) {
        throw RepositoryError(e.what());
    }
}


void Enchantment::deleteGuardianStatue(const std::string& powerWordName) {
    try {
        encyclopedia.deleteGuardianStatueFile(powerWordName);
    }
    catch (std::exception & e) {
        throw RepositoryError(e.what());
    }
}


void Enchantment::updateGuardianStatue(const std::string& powerWordName, const std::string& newMaterial, const int& newAge, const std::string& newCorporealForm) {
    GuardianStatue guardStat = { powerWordName, newMaterial, newAge, newCorporealForm };
    try {
        GuardianStatueValidator::validate(guardStat);
        encyclopedia.updateGuardianStatueFile(guardStat);
    }
    catch (std::exception & e) {
        throw RepositoryError(e.what());
    }
}


std::vector<GuardianStatue> Enchantment::getAllGuardianStatues() {
    return encyclopedia.getAllFile();
}


////////////////////////////////////////////////////////////////////////////


std::vector<GuardianStatue> Enchantment::getAllApprenticeGuardianStatues()
{
    return apprenticeEncyclopedia.csv_getAllFile();
}


void Enchantment::initialiseIterator() {
    try {
        std::vector<GuardianStatue> stats = this->encyclopedia.getAllFile();
        for (const auto & stat : stats) {
            this->encyclopediaIterator.add(stat);
        }
    }
    catch (std::exception & e) {
        throw ControllerError(e.what());
    }
    this->encyclopediaIterator.set_current();
}


GuardianStatue Enchantment::nextGuardianStatues() {
    if (!this->encyclopediaIterator.is_initialised()) {
        this->initialiseIterator();
    }
    GuardianStatue nextStatue = this->encyclopediaIterator.getStatue();
    this->encyclopediaIterator.next();
    return nextStatue;
}


void Enchantment::saveGuardianStatue(const std::string& powerWordName) {
    if (!this->encyclopediaIterator.is_initialised()) {
        this->initialiseIterator();
    }
    int positionOfStat = this->searchGuardianStatue(powerWordName);
    if (positionOfStat == -1) {
        throw ControllerError("Can't find statue!\n");
    }
    this->apprenticeEncyclopedia.csv_saveGuardianStatueFile(this->encyclopedia.getAllFile()[positionOfStat]);
    //this->apprenticeEncyclopedia.addStatue(this->encyclopedia.getAllFile()[positionOfStat]);
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
    //if (result.empty()) {
    //    return this->getAllGuardianStatues();
    //}
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


void Enchantment::setUserFilePath(std::string & path) {
    this->apprenticeEncyclopedia.setFileName(path);
}


void Enchantment::setUserFileType() {
    std::string fileName = this->apprenticeEncyclopedia.getFileName();
    std::string::size_type idx = fileName.rfind('.');
    if (idx != std::string::npos) {
        std::string extension = fileName.substr(idx + 1);
        this->apprenticeEncyclopedia.setFileType(extension);
    }
    else {
        throw FileError("No extension found!\n");
    }
}


void Enchantment::displayArchmageFile() {
    this->encyclopedia.display();
}


void Enchantment::displayApprenticeFile() {
    this->apprenticeEncyclopedia.display();
}
