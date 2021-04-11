#ifndef ANSWERS_H
#define ANSWERS_H

#include "answer.h"
#include <vector>


class Answers
{
private:
    std::vector<Answer> answers;
public:
    Answers();
    ~Answers() {}
    std::vector<Answer> get_all() { return this->answers; }
    void load_from_file();
    std::vector<Answer> get_answers_by_qid(std::string qid);
    void add(Answer a) { this->answers.push_back(a); }
    void increas_votes(Answer a) {
        for (auto a1 : answers) {
            if (a1.get_id() == a.get_id()) {
                a1.increase_votes();
            }
        }
    }
    void decrease_votes(Answer a) {
        for (auto a1 : answers) {
            if (a1.get_id() == a.get_id()) {
                a1.decrease_votes();
            }
        }
    }
};

#endif // ANSWERS_H
