#include "controller.h"
#include <algorithm>


void Controller::increase_votes(Answer a, std::string name) {
    if (a.get_name() == name) {
        return;
    }
    this->answers->increas_votes(a);
}


void Controller::decrease_votes(Answer a, std::string name) {
    if (a.get_name() == name) {
        return;
    }
    this->answers->decrease_votes(a);
}


void Controller::add_answer(std::string id, std::string qid, std::string name, std::string text, int no_of_votes) {
    Answer a{id, qid, name, text, no_of_votes};
    for (auto a1 : this->answers->get_all()) {
        if (a1.get_id() == a.get_id()) {
            throw std::exception();
        }
    }
    bool ok = false;
    for (auto q1 : this->questions->get_all()) {
        if (q1.get_id() == a.get_qid()) {
            ok = true;
        }
    }
    if (ok == false) {
        throw std::exception();
    }
    if (a.get_text() == "") {
        throw std::exception();
    }

    this->answers->add(a);

    this->notify();
}


void Controller::add_question(std::string id, std::string text, std::string name) {
    Question q{id, text, name};
    for (auto q1 : this->questions->get_all()) {
        if (q1.get_id() == q.get_id()) {
            throw std::exception();
        }
    }
    if (text == "") {
        throw std::exception();
    }

    this->questions->add(q);

    this->notify();
}

int Controller::get_no_answers_question(Question q) {
    int count = 0;
    for (auto a : this->answers->get_all()) {
        if (q.get_id() == a.get_qid()) {
            count += 1;
        }
    }
    return count;
}

std::vector<Question> Controller::get_questions_sorted() {
    std::vector<Question> result = this->questions->get_all();
    std::sort(result.begin(), result.end(), [this](Question q1, Question q2) {
        return this->get_no_answers_question(q1) > this->get_no_answers_question(q2);
    });
    return result;
}

std::vector<Answer> Controller::get_answers_sorted(Question q) {
    std::vector<Answer> result;
    for (auto a : this->answers->get_all()) {
        if (a.get_qid() == q.get_id()) {
            result.push_back(a);
        }
    }
    std::sort(result.begin(), result.end(), [](Answer a1, Answer a2) {
        return a1.get_no_of_votes() > a2.get_no_of_votes();
    });
    return result;
}

std::string Controller::get_three_answers(Question q) {
    std::string result = "";
    auto answers = this->get_answers_sorted(q);
    for (int i = 0; i < 3 && i < int(answers.size()); i += 1) {
        result += "\t";
        result += answers[i].get_id();
        result += " | ";
        result += answers[i].get_name();
        result += " | ";
        result += answers[i].get_text();
        result += " | ";
        result += std::to_string(answers[i].get_no_of_votes());
        result += "\n";
    }
    return result;
}

std::string Controller::get_search_result(std::string input) {
    std::string result = "";
    for (auto q : this->questions->get_all()) {
        std::size_t found = q.get_text().find(input);
        if (found != std::string::npos) {
            result += q.get_id();
            result += " | ";
            result += q.get_name();
            result += " | ";
            result += q.get_text();
            result += "\n";
            result += this->get_three_answers(q);
        }
    }
    return result;
}


