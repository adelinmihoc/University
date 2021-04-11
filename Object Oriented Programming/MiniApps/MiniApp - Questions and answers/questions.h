#ifndef QUESTIONS_H
#define QUESTIONS_H

#include "question.h"
#include <vector>


class Questions
{
private:
    std::vector<Question> questions;
public:
    Questions();
    ~Questions() {}
    std::vector<Question> get_all() { return this->questions; }
    void load_from_file();
    void add(Question q) { this->questions.push_back(q); }
};

#endif // QUESTIONS_H
