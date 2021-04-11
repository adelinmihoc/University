#include "Controller.h"
#include "Exceptions.h"


void Enchantment::addGuardianStatue(const std::string& powerWordName, const std::string& material, const int& age, const std::string& corporealForm) {
    GuardianStatue guardStat = { powerWordName, material, age, corporealForm };
    try {
        GuardianStatueValidator::validate(guardStat);
        if (this->admin_repo_type == "file") {
            encyclopedia.addGuardianStatueFile(guardStat);
        } else {
            encyclopedia.addStatue(guardStat);
        }
    }
    catch (std::exception & e) {
        throw RepositoryError(e.what());
    }
}


void Enchantment::deleteGuardianStatue(const std::string& powerWordName) {
    try {
        if (this->admin_repo_type == "file") {
            encyclopedia.deleteGuardianStatueFile(powerWordName);
        } else {
            encyclopedia.deleteStatue(powerWordName);
        }
    }
    catch (std::exception & e) {
        throw RepositoryError(e.what());
    }
}


void Enchantment::updateGuardianStatue(const std::string& powerWordName, const std::string& newMaterial, const int& newAge, const std::string& newCorporealForm) {
    GuardianStatue guardStat = { powerWordName, newMaterial, newAge, newCorporealForm };
    try {
        GuardianStatueValidator::validate(guardStat);
        if (this->admin_repo_type == "file") {
            encyclopedia.updateGuardianStatueFile(guardStat);
        } else {
            encyclopedia.updateStatue(guardStat);
        }
    }
    catch (std::exception & e) {
        throw RepositoryError(e.what());
    }
}


std::vector<GuardianStatue> Enchantment::getAllGuardianStatues() {
    if (this->admin_repo_type == "file") {
        return encyclopedia.getAllFile();
    } else {
        return encyclopedia.getAllStatues();
    }
}


////////////////////////////////////////////////////////////////////////////


std::vector<GuardianStatue> Enchantment::getAllApprenticeGuardianStatues() {
    return apprenticeEncyclopedia.csv_getAllFile();
}


void Enchantment::initialiseIterator() {
    try {
        std::vector<GuardianStatue> stats;
        if (this->admin_repo_type == "file") {
            stats = this->encyclopedia.getAllFile();
        } else {
            stats = this->encyclopedia.getAllStatues();
        }
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
    if (this->admin_repo_type == "file") {
        this->apprenticeEncyclopedia.csv_saveGuardianStatueFile(this->encyclopedia.getAllFile()[positionOfStat]);
        //this->apprenticeEncyclopedia.addStatue(this->encyclopedia.getAllFile()[positionOfStat]);
    } else {
        this->apprenticeEncyclopedia.csv_saveGuardianStatueFile(this->encyclopedia.getAllStatues()[positionOfStat]);
    }
}


int Enchantment::searchGuardianStatue(const std::string& powerWordName) {
    for (int i = 0; i < this->encyclopedia.sizeFile(); i++) {
        if (this->admin_repo_type == "file") {
            if (this->encyclopedia.getAllFile()[i].getPowerWordName() == powerWordName) {
                return i;
            }
        } else {
            if (this->encyclopedia.getAllStatues()[i].getPowerWordName() == powerWordName) {
                return i;
            }
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
