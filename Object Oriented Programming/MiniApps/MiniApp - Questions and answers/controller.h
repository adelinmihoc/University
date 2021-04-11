#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "questions.h"
#include "answers.h"
#include "observer.h"


class Controller : public Subject
{
private:
    Questions* questions;
    Answers* answers;
public:
    Controller(Questions* q, Answers* a)
        : questions{q}
        , answers{a}
    {

    }
    Questions* get_questions() { return questions; }
    Answers* get_answers() { return answers; }
    std::vector<Answer> get_answers_sorted(Question q);
    std::vector<Question> get_questions_sorted();
    int get_no_answers_question(Question q);
    std::string get_search_result(std::string input);
    std::string get_three_answers(Question q);
    void add_question(std::string id, std::string text, std::string name);
    void add_answer(std::string id, std::string qid, std::string name, std::string text, int no_of_votes);
    void increase_votes(Answer a, std::string name);
    void decrease_votes(Answer a, std::string name);
};

#endif // CONTROLLER_H
