#include "questions.h"
#include <fstream>


Questions::Questions()
{
    this->load_from_file();
}

void Questions::load_from_file() {
    std::ifstream f{"/home/adelin/OneDirToRuleThemAll/oop/Questions_and_answers/questions.txt"};
    if (!f.is_open()) {
        return;
    }
    Question q{"", "", ""};
    while (f >> q) {
        questions.push_back(q);
    }
}
