#ifndef CONTROLLER_H
#define CONTROLLER_H


#include "questions.h"
#include "observer.h"

class Controller : public Subject
{
private:
    Questions* questions;
public:
    std::vector<Question> get_question_sorted_score() {
        auto result = this->questions->get_questions();
        std::sort(result.begin(), result.end(), [](Question q1, Question q2) {
            return q1.get_score() > q2.get_score();
        });
        return result;
    }
    std::vector<Question> get_question_sorted_id() {
        auto result = this->questions->get_questions();
        std::sort(result.begin(), result.end(), [](Question q1, Question q2) {
            return q1.get_id() < q2.get_id();
        });
        return result;
    }
    std::vector<Question> get_all_questions() { return questions->get_questions(); }
    void add_question(int id, std::string text, std::string correct_answer, int score) {
        Question q{id, text, correct_answer, score};
        if (q.get_text() == "") {
            throw std::exception();
        }
        if (q.get_correct_answer() == "") {
            throw std::exception();
        }
        try {
            questions->add_question(q);
            this->notify();
        } catch (std::exception()) {
            throw std::exception();
        }

    }
    Controller(Questions* q)
        : questions{q}
    {

    }
};

#endif // CONTROLLER_H
