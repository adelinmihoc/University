#include "Domain.h"
#include <sstream>


GuardianStatue::GuardianStatue() : powerWordName(""), material(""), age(0), corporealForm("") {}


GuardianStatue::GuardianStatue(const std::string& powerWordName, const std::string& material, const int& age, const std::string& corporealForm) {
    this->powerWordName = powerWordName;
    this->material = material;
    this->age = age;
    this->corporealForm = corporealForm;
}

std::string GuardianStatue::to_string() {
    std::stringstream buffer;
    buffer << this->powerWordName << " | " << this->material << " | " << this->age << " | " << this->corporealForm << "\n";
    return std::string(buffer.str());
}

