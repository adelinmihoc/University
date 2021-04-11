#include "answers.h"
#include <fstream>


Answers::Answers()
{
    this->load_from_file();
}

void Answers::load_from_file() {
    std::ifstream f{"/home/adelin/OneDirToRuleThemAll/oop/Questions_and_answers/answers.txt"};
    if (!f.is_open()) {
        return;
    }
    Answer a{"", "", "" , "", 0};
    while (f >> a) {
        answers.push_back(a);
    }
}

std::vector<Answer> Answers::get_answers_by_qid(std::string qid) {
    std::vector<Answer> result;
    for (auto a : answers) {
        if (a.get_qid() == qid) {
            result.push_back(a);
        }
    }
    return result;
}
