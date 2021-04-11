#include "UserInterface.h"
#include <sstream>
#include <vector>


void RunicAltar::lightRunicAltar() {
    while (true){
        showEnchantmentsFirstFire();
        std::string enchantmentLine;
        std::cout << ">>>";
        std::getline(std::cin, enchantmentLine);
        std::cout << "\n";
        std::string command;
        std::string parametersLine;

        if (enchantmentLine == "exit") {
            break;
        }
        if (enchantmentLine == "mode A") {
            communionPatternMage();
            break;
        }
        if (enchantmentLine == "mode B") {
            communionPatternApprentice();
            break;
        }

        bool firstSpace = false;
        for (char i : enchantmentLine) {
            if (!firstSpace && i != ' ') {
                command += i;
            }
            else {
                if (!firstSpace) {
                    firstSpace = true;
                }
                else {
                    parametersLine += i;
                }
            }
        }
        std::cout << "\n" << command << "\n";
        /*if (command == "exit") {
            break;
        }
        if (command == "mode A") {
            communionPatternMage();
            break;
        }
        if (command == "mode B") {
            communionPatternApprentice();
            break;
        }*/
        if (command == "fileLocation") {
            setFilePath(parametersLine);
            continue;
        }
        std::cout << "Enchantment was spelled wrong!\n\n";
    }
}


void RunicAltar::communionPatternMage() {
    while (true) {
        showEnchantmentsMage();
        std::string enchantmentLine;
        std::cout << ">>>";
        std::getline(std::cin, enchantmentLine);
        std::cout << "\n";
        std::string command;
        std::string parametersLine;

        bool firstSpace = false;
        for (char i : enchantmentLine) {
            if (!firstSpace && i != ' ') {
                command += i;
            }
            else {
                if (!firstSpace) {
                    firstSpace = true;
                }
                else {
                    parametersLine += i;
                }
            }
        }

        if (command == "exit") {
            break;
        }
        else {
            if (command == "add") {
                try {
                    addGuardianStatue(parametersLine);
                }
                catch (std::exception&) {
                    std::cout << "Broken enchantment!\n\n";
                }
                continue;
            }
            if (command == "delete") {
                try {
                    deleteGuardianStatue(parametersLine);
                }
                catch (std::exception&) {
                    std::cout << "Broken enchantment!\n\n";
                }
                continue;
            }
            if (command == "update") {
                try {
                    updateGuardianStatue(parametersLine);
                }
                catch (std::exception&) {
                    std::cout << "Broken enchantment!\n\n";
                }
                continue;
            }
            if (command == "list") {
                try {
                    listAllGuardianStatues(parametersLine);
                    std::cout << "\n";
                }
                catch (std::exception&) {
                    std::cout << "Broken enchantment!\n\n";
                }
                continue;
            }
            std::cout << "Enchantment was spelled wrong!\n\n";

        }

    }
}


void RunicAltar::communionPatternApprentice() {
    this->enchantment.initialiseIterator();
    while (true) {
        showEnchantmentsApprentice();
        std::string enchantmentLine;
        std::cout << ">>>";
        std::getline(std::cin, enchantmentLine);
        std::cout << "\n";
        std::string command;
        std::string parametersLine;

        bool firstSpace = false;
        for (char i : enchantmentLine) {
            if (!firstSpace && i != ' ') {
                command += i;
            }
            else {
                if (!firstSpace) {
                    firstSpace = true;
                }
                else {
                    parametersLine += i;
                }
            }
        }

        if (command == "exit") {
            break;
        }
        else {
            if (command == "list") {
                try {
                    listAllStatuesByMaterialAndAge(parametersLine);
                    std::cout << "\n";
                }
                catch (std::exception&) {
                    std::cout << "Broken enchantment!\n\n";
                }
                continue;
            }
            if (command == "next") {
                try {
                    nextGuardStatue(parametersLine);
                    std::cout << "\n";
                }
                catch (std::exception&) {
                    std::cout << "Broken enchantment!\n\n";
                }
                continue;
            }
            if (command == "save") {
                try {
                    saveGuardianStatue(parametersLine);
                    std::cout << "\n";
                }
                catch (std::exception&) {
                    std::cout << "Broken enchantment!\n\n";
                }
                continue;
            }
            if (command == "mylist") {
                try {
                    listAllApprenticeStatues(parametersLine);
                    std::cout << "\n";
                }
                catch (std::exception&) {
                    std::cout << "Broken enchantment!\n\n";
                }
                continue;
            }
            std::cout << "Enchantment was spelled wrong!\n\n";

        }

    }
}


void RunicAltar::showEnchantmentsMage() {
    std::cout << "**ARCHMAGE MODE**\n";
    std::cout << "'add powerWordName, material, age, corporealForm' to add a Guardian Statue.\n";
    std::cout << "'update powerWordName, newMaterial, newAge, newCorporealForm' to update a Guardian Statue.\n";
    std::cout << "'delete powerWordName' to delete a Guardian Statue.\n";
    std::cout << "'list' to list all Guardian Statues.\n";
    std::cout << "'exit' to exit this mode.\n\n";
}


void RunicAltar::showEnchantmentsApprentice() {
    std::cout << "**APPRENTICE MODE**\n";
    std::cout << "'next' to see the next Guardian Statue from the Encyclopedia.\n";
    std::cout << "'save powerWordName' to save a statue into the apprentice list.\n";
    std::cout << "'list material, age' to see all statues of a given material, having an age less than a given number.\n";
    std::cout << "'mylist' to list all Guardian Statues from the apprentice list.\n";
    std::cout << "'exit' to exit this mode.\n\n";
}


void RunicAltar::showEnchantmentsFirstFire() {
    std::cout << "Are you a Mage or an apprentice?\n";
    std::cout << "The enchantment is 'mode A' for the Archmages and the elders of the Spire.\n";
    std::cout << "For apprentices the enchantment is 'mode B'.\n";
    std::cout << "To set a path to a file: 'fileLocation filepath'.\n";
    std::cout << "Or type 'exit'.\n\n";
}


void RunicAltar::addGuardianStatue(const std::string& parametersLine) {
    std::vector <std::string> parameters;
    std::stringstream check1(parametersLine);
    std::string intermediate;
    while (std::getline(check1, intermediate, ',')) {
        parameters.push_back(intermediate);
    }


    for (auto & parameter : parameters) {
        if (parameter[0] == ' ') {
            parameter.erase(parameter.begin());
        }
        if (parameter[parameter.size() - 1] == ' ') {
            parameter.erase(parameter.begin() + parameter.size() - 1);
        }
    }

    if (parameters.size() != 4) {
        throw std::exception();
    }
    std::string powerWordName = parameters[0];
    std::string material = parameters[1];
    int age = 0;
    try {
        age = std::stoi(parameters[2]);
    }
    catch (std::exception&) {
        throw std::exception();
    }
    std::string corporealForm = parameters[3];
    this->enchantment.addGuardianStatue(powerWordName, material, age, corporealForm);
}


void RunicAltar::deleteGuardianStatue(const std::string& parametersLine) {
    std::vector <std::string> parameters;
    std::stringstream check1(parametersLine);
    std::string intermediate;
    while (std::getline(check1, intermediate, ',')) {
        parameters.push_back(intermediate);
    }


    for (auto & parameter : parameters) {
        if (parameter[0] == ' ') {
            parameter.erase(parameter.begin());
        }
        if (parameter[parameter.size() - 1] == ' ') {
            parameter.erase(parameter.begin() + parameter.size() - 1);
        }
    }

    if (parameters.size() != 1) {
        throw std::exception();
    }
    std::string powerWordName = parameters[0];
    this->enchantment.deleteGuardianStatue(powerWordName);
}


void RunicAltar::updateGuardianStatue(const std::string& parametersLine) {
    std::vector <std::string> parameters;
    std::stringstream check1(parametersLine);
    std::string intermediate;
    while (std::getline(check1, intermediate, ',')) {
        parameters.push_back(intermediate);
    }


    for (auto & parameter : parameters) {
        if (parameter[0] == ' ') {
            parameter.erase(parameter.begin());
        }
        if (parameter[parameter.size() - 1] == ' ') {
            parameter.erase(parameter.begin() + parameter.size() - 1);
        }
    }

    if (parameters.size() != 4) {
        throw std::exception();
    }
    std::string powerWordName = parameters[0];
    std::string material = parameters[1];
    int age = 0;
    try {
        age = std::stoi(parameters[2]);
    }
    catch (std::exception&) {
        throw std::exception();
    }
    std::string corporealForm = parameters[3];
    this->enchantment.updateGuardianStatue(powerWordName, material, age, corporealForm);
}


void RunicAltar::listAllGuardianStatues(const std::string& parametersLine) {
    std::vector <std::string> parameters;
    std::stringstream check1(parametersLine);
    std::string intermediate;
    while (std::getline(check1, intermediate, ',')) {
        parameters.push_back(intermediate);
    }


    for (auto & parameter : parameters) {
        if (parameter[0] == ' ') {
            parameter.erase(parameter.begin());
        }
        if (parameter[parameter.size() - 1] == ' ') {
            parameter.erase(parameter.begin() + parameter.size() - 1);
        }
    }

    if (!parameters.empty()) {
        throw std::exception();
    }
    std::vector<GuardianStatue> items = this->enchantment.getAllGuardianStatues();
    for (const auto& guardianStatue : items) {
        std::cout << guardianStatue.getPowerWordName() << ", " << guardianStatue.getMaterial() << ", " << guardianStatue.getAge() << ", " << guardianStatue.getCorporealForm() << ".\n";
    }
}


////////////////////////////////////////////////////////////////////////////////////////


void RunicAltar::nextGuardStatue(const std::string& parametersLine) {
    std::vector <std::string> parameters;
    std::stringstream check1(parametersLine);
    std::string intermediate;
    while (std::getline(check1, intermediate, ',')) {
        parameters.push_back(intermediate);
    }


    for (auto & parameter : parameters) {
        if (parameter[0] == ' ') {
            parameter.erase(parameter.begin());
        }
        if (parameter[parameter.size() - 1] == ' ') {
            parameter.erase(parameter.begin() + parameter.size() - 1);
        }
    }

    if (!parameters.empty()) {
        throw std::exception();
    }

    GuardianStatue guardStat = this->enchantment.nextGuardianStatues();
    std::cout << guardStat.getPowerWordName() << ", " << guardStat.getMaterial() << ", " << guardStat.getAge() << ", " << guardStat.getCorporealForm() << ".\n";

}


void RunicAltar::saveGuardianStatue(const std::string& parametersLine) {
    std::vector <std::string> parameters;
    std::stringstream check1(parametersLine);
    std::string intermediate;
    while (std::getline(check1, intermediate, ',')) {
        parameters.push_back(intermediate);
    }


    for (auto & parameter : parameters) {
        if (parameter[0] == ' ') {
            parameter.erase(parameter.begin());
        }
        if (parameter[parameter.size() - 1] == ' ') {
            parameter.erase(parameter.begin() + parameter.size() - 1);
        }
    }

    if (parameters.size() != 1) {
        throw std::exception();
    }
    std::string powerWordName = parameters[0];
    try {
        this->enchantment.saveGuardianStatue(powerWordName);
    }
    catch (std::exception&) {
        throw std::exception();
    }
}


void RunicAltar::listAllApprenticeStatues(const std::string& parametersLine) {
    std::vector <std::string> parameters;
    std::stringstream check1(parametersLine);
    std::string intermediate;
    while (std::getline(check1, intermediate, ',')) {
        parameters.push_back(intermediate);
    }


    for (auto & parameter : parameters) {
        if (parameter[0] == ' ') {
            parameter.erase(parameter.begin());
        }
        if (parameter[parameter.size() - 1] == ' ') {
            parameter.erase(parameter.begin() + parameter.size() - 1);
        }
    }

    if (!parameters.empty()) {
        throw std::exception();
    }
    std::vector<GuardianStatue> items = this->enchantment.getAllApprenticeGuardianStatues();
    for (auto guardianStatue : items) {
        std::cout << guardianStatue.getPowerWordName() << ", " << guardianStatue.getMaterial() << ", " << guardianStatue.getAge() << ", " << guardianStatue.getCorporealForm() << ".\n";
    }
}


void RunicAltar::listAllStatuesByMaterialAndAge(const std::string& parametersLine) {
    std::vector <std::string> parameters;
    std::stringstream check1(parametersLine);
    std::string intermediate;
    while (std::getline(check1, intermediate, ',')) {
        parameters.push_back(intermediate);
    }


    for (auto & parameter : parameters) {
        if (parameter[0] == ' ') {
            parameter.erase(parameter.begin());
        }
        if (parameter[parameter.size() - 1] == ' ') {
            parameter.erase(parameter.begin() + parameter.size() - 1);
        }
    }

    if (parameters.size() != 2) {
        throw std::exception();
    }
    std::string material = parameters[0];
    int age = 0;
    try {
        age = std::stoi(parameters[1]);
    }
    catch (std::exception&) {
        throw std::exception();
    }
    //DynamicVector<GuardianStatue> stats = this->enchantment.getAllApprenticeStatuesByAge(age);
    std::vector<GuardianStatue> stats = this->enchantment.getAllApprenticeStatuesByMaterialAndAge(material, age);
    for (const auto& guardianStatue : stats) {
        std::cout << guardianStatue.getPowerWordName() << ", " << guardianStatue.getMaterial() << ", " << guardianStatue.getAge() << ", " << guardianStatue.getCorporealForm() << ".\n";
    }
}

void RunicAltar::setFilePath(const std::string& parametersLine) {
    this->enchantment.setFilePath(const_cast<std::string &>(parametersLine));
}
