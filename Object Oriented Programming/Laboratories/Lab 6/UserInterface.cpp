#include "UserInterface.h"
#include <sstream> 
#include <vector>


void RunicAltar::lightRunicAltar() {
	while (true){
		showEnchantmentsFirstFire();
		std::string command;
		std::cout << ">>>";
		std::getline(std::cin, command);
		std::cout << "\n";
		if (command == "exit") {
			break;
		}
		if (command == "mode A") {
			communionPatternMage();
			break;
		}
		if (command == "mode B") {
			communionPatternApprentice();
			break;
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
		for (int i = 0; i < enchantmentLine.size(); i++) {
			if (!firstSpace && enchantmentLine[i] != ' ') {
				command += enchantmentLine[i];
			}
			else {
				if (!firstSpace && enchantmentLine[i] == ' ') {
					firstSpace = true;
				}
				else {
					parametersLine += enchantmentLine[i];
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
		for (int i = 0; i < enchantmentLine.size(); i++) {
			if (!firstSpace && enchantmentLine[i] != ' ') {
				command += enchantmentLine[i];
			}
			else {
				if (!firstSpace && enchantmentLine[i] == ' ') {
					firstSpace = true;
				}
				else {
					parametersLine += enchantmentLine[i];
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
	std::cout << "Or type 'exit'.\n\n";
}


void RunicAltar::addGuardianStatue(std::string parametersLine) {	
	std::vector <std::string> parameters;
	std::stringstream check1(parametersLine);
	std::string intermediate;
	while (std::getline(check1, intermediate, ',')) {
		parameters.push_back(intermediate);
	}


	for (int i = 0; i < parameters.size(); i++) {
		if (parameters[i][0] == ' ') {
			parameters[i].erase(parameters[i].begin());
		}
		if (parameters[i][parameters[i].size() - 1] == ' ') {
			parameters[i].erase(parameters[i].begin() + parameters[i].size() - 1);
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


void RunicAltar::deleteGuardianStatue(std::string parametersLine) {
	std::vector <std::string> parameters;
	std::stringstream check1(parametersLine);
	std::string intermediate;
	while (std::getline(check1, intermediate, ',')) {
		parameters.push_back(intermediate);
	}


	for (int i = 0; i < parameters.size(); i++) {
		if (parameters[i][0] == ' ') {
			parameters[i].erase(parameters[i].begin());
		}
		if (parameters[i][parameters[i].size() - 1] == ' ') {
			parameters[i].erase(parameters[i].begin() + parameters[i].size() - 1);
		}
	}

	if (parameters.size() != 1) {
		throw std::exception();
	}
	std::string powerWordName = parameters[0];
	this->enchantment.deleteGuardianStatue(powerWordName);
}


void RunicAltar::updateGuardianStatue(std::string parametersLine) {
	std::vector <std::string> parameters;
	std::stringstream check1(parametersLine);
	std::string intermediate;
	while (std::getline(check1, intermediate, ',')) {
		parameters.push_back(intermediate);
	}


	for (int i = 0; i < parameters.size(); i++) {
		if (parameters[i][0] == ' ') {
			parameters[i].erase(parameters[i].begin());
		}
		if (parameters[i][parameters[i].size() - 1] == ' ') {
			parameters[i].erase(parameters[i].begin() + parameters[i].size() - 1);
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


void RunicAltar::listAllGuardianStatues(std::string parametersLine) {
	std::vector <std::string> parameters;
	std::stringstream check1(parametersLine);
	std::string intermediate;
	while (std::getline(check1, intermediate, ',')) {
		parameters.push_back(intermediate);
	}


	for (int i = 0; i < parameters.size(); i++) {
		if (parameters[i][0] == ' ') {
			parameters[i].erase(parameters[i].begin());
		}
		if (parameters[i][parameters[i].size() - 1] == ' ') {
			parameters[i].erase(parameters[i].begin() + parameters[i].size() - 1);
		}
	}

	if (parameters.size() != 0) {
		throw std::exception();
	}
	DynamicVector<GuardianStatue> items = this->enchantment.getAllGuardianStatues();
	for (int i = 0; i < items.getSize(); i++) {
		GuardianStatue guarstat = items.getItem(i);
		std::cout << guarstat.getPowerWordName() << ", " << guarstat.getMaterial() << ", " << guarstat.getAge() << ", " << guarstat.getCorporealForm() << ".\n";
	}
}


////////////////////////////////////////////////////////////////////////////////////////


void RunicAltar::nextGuardStatue(std::string parametersLine) {
	std::vector <std::string> parameters;
	std::stringstream check1(parametersLine);
	std::string intermediate;
	while (std::getline(check1, intermediate, ',')) {
		parameters.push_back(intermediate);
	}


	for (int i = 0; i < parameters.size(); i++) {
		if (parameters[i][0] == ' ') {
			parameters[i].erase(parameters[i].begin());
		}
		if (parameters[i][parameters[i].size() - 1] == ' ') {
			parameters[i].erase(parameters[i].begin() + parameters[i].size() - 1);
		}
	}

	if (parameters.size() != 0) {
		throw std::exception();
	}

	GuardianStatue guardStat = this->enchantment.nextGuardianStatues();
	std::cout << guardStat.getPowerWordName() << ", " << guardStat.getMaterial() << ", " << guardStat.getAge() << ", " << guardStat.getCorporealForm() << ".\n";

}


void RunicAltar::saveGuardianStatue(std::string parametersLine) {
	std::vector <std::string> parameters;
	std::stringstream check1(parametersLine);
	std::string intermediate;
	while (std::getline(check1, intermediate, ',')) {
		parameters.push_back(intermediate);
	}


	for (int i = 0; i < parameters.size(); i++) {
		if (parameters[i][0] == ' ') {
			parameters[i].erase(parameters[i].begin());
		}
		if (parameters[i][parameters[i].size() - 1] == ' ') {
			parameters[i].erase(parameters[i].begin() + parameters[i].size() - 1);
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


void RunicAltar::listAllApprenticeStatues(std::string parametersLine) {
	std::vector <std::string> parameters;
	std::stringstream check1(parametersLine);
	std::string intermediate;
	while (std::getline(check1, intermediate, ',')) {
		parameters.push_back(intermediate);
	}


	for (int i = 0; i < parameters.size(); i++) {
		if (parameters[i][0] == ' ') {
			parameters[i].erase(parameters[i].begin());
		}
		if (parameters[i][parameters[i].size() - 1] == ' ') {
			parameters[i].erase(parameters[i].begin() + parameters[i].size() - 1);
		}
	}

	if (parameters.size() != 0) {
		throw std::exception();
	}
	DynamicVector<GuardianStatue> items = this->enchantment.getAllApprenticeGuardianStatues();
	for (int i = 0; i < items.getSize(); i++) {
		GuardianStatue guarstat = items.getItem(i);
		std::cout << guarstat.getPowerWordName() << ", " << guarstat.getMaterial() << ", " << guarstat.getAge() << ", " << guarstat.getCorporealForm() << ".\n";
	}
}


void RunicAltar::listAllStatuesByMaterialAndAge(std::string parametersLine) {
	std::vector <std::string> parameters;
	std::stringstream check1(parametersLine);
	std::string intermediate;
	while (std::getline(check1, intermediate, ',')) {
		parameters.push_back(intermediate);
	}


	for (int i = 0; i < parameters.size(); i++) {
		if (parameters[i][0] == ' ') {
			parameters[i].erase(parameters[i].begin());
		}
		if (parameters[i][parameters[i].size() - 1] == ' ') {
			parameters[i].erase(parameters[i].begin() + parameters[i].size() - 1);
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
	DynamicVector<GuardianStatue> stats = this->enchantment.getAllApprenticeStatuesByMaterialAndAge(material, age);
	for (int i = 0; i < stats.getSize(); i++) {
		GuardianStatue guarstat = stats.getItem(i);
		std::cout << guarstat.getPowerWordName() << ", " << guarstat.getMaterial() << ", " << guarstat.getAge() << ", " << guarstat.getCorporealForm() << ".\n";
	}
}
