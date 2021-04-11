#include "users.h"
#include <fstream>

Users::Users()
{
    this->load_from_file();
}

void Users::load_from_file() {
    std::ifstream f{"/home/adelin/OneDirToRuleThemAll/oop/Questions_and_answers/users.txt"};
    if (!f.is_open()) {
        return;
    }
    User u{""};
    while (f >> u) {
        users.push_back(u);
    }
}
