#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include "utils.h"
#include <string>


class Participant
{
private:
    std::string name;
    int score;
    std::vector<int> answered_questions;
public:
    bool is_question_answered(int id) {
        for (auto s : answered_questions) {
            if (id == s) {
                return true;
            }
        }
        return false;
    }
    void add_answered_question(int id) { answered_questions.push_back(id); }
    friend std::istream& operator>>(std::istream& is, Participant& p) {
        std::string line;
        getline(is, line);
        std::vector<std::string> tokens = tokenize(line, ',');
        if (tokens.size() != 2) {
            return is;
        }
        p.name = tokens[0];
        p.score = std::stoi(tokens[1]);
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, Participant& p) {
        return os << p.name << "," << p.score << "\n";
    }
    void set_score(int s) { score = s; }
    int get_score() const { return  score; }
    std::string get_name() const { return name; }
    Participant() {
        name = "";
        score = 0;
    }
    Participant(std::string n, int s)
        : name{n}
        , score{s}
    {

    }
};

#endif // PARTICIPANT_H
