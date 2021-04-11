#ifndef QUESTIONS_H
#define QUESTIONS_H

#include "question.h"
#include <fstream>

class Questions
{
private:
    std::vector<Question> questions;
public:
    std::vector<Question> get_questions() {
        this->load_from_file();
        return questions;
    }
    void add_question(Question q) {
        this->load_from_file();
        for (auto q1 : questions) {
            if (q1.get_id() == q.get_id()) {
                throw std::exception();
            }
        }
        this->questions.push_back(q);
        this->save_to_file();
    }
    void save_to_file() {
        std::ofstream f{"/home/adelin/OneDirToRuleThemAll/oop/Quiz/questions.txt"};
        for (auto q : questions) {
            f << q;
        }
        this->questions.clear();
        f.close();
    }
    void load_from_file() {
        std::ifstream f{"/home/adelin/OneDirToRuleThemAll/oop/Quiz/questions.txt"};
        if (!f.is_open()) {
            return;
        }
        this->questions.clear();
        Question q;
        while (f >> q) {
            questions.push_back(q);
        }
        f.close();
    }
    Questions() {
        this->load_from_file();
    }
};

#endif // QUESTIONS_H
