#include "repository.h"
#include <algorithm>
#include "exceptions.h"

Repository::Repository() {

}

void Repository::add(Guardian_statue statue) {
    if (this->search(statue.get_power_word_name()) == statues.end()) {
        this->statues.push_back(statue);
    } else {
        throw Exception("Statue already exists!\n");
    }
}

void Repository::remove(std::string name) {
    if (this->search(name) != statues.end()) {
        this->statues.erase(this->search(name));
    } else {
        throw Exception("Statue does not exists!\n");
    }
}

void Repository::update(Guardian_statue statue) {
    std::vector<Guardian_statue>::iterator it = search(statue.get_power_word_name());
    if (it != statues.end()) {
        statues.erase(it);
        statues.insert(it, statue);
    } else {
        throw Exception("Statue does not exists!\n");
    }
}

std::vector<Guardian_statue>::iterator Repository::search(std::string name) {
    std::vector<Guardian_statue>::iterator it;
    Guardian_statue stat {name, "", 0, ""};
    it = find(statues.begin(), statues.end(), stat);
    return it;
}

std::vector<Guardian_statue> Repository::get_all() {
    return this->statues;
}

int Repository::get_size() {
    return statues.size();
}

void Repository::set_filename(std::string &name) {
    name = "";
}

std::string Repository::get_filename() {
    return "";
}

std::string Repository::get_type() {
    return "memory";
}



