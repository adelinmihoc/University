#ifndef QUESTION_H
#define QUESTION_H

#include <string>
#include "utils.h"


class Question
{
private:
    int id;
    std::string text;
    std::string correct_answer;
    int score;
public:
    friend std::ostream& operator<<(std::ostream& os, Question& q) {
        return os << q.id << "," << q.text << "," << q.correct_answer << "," << q.score << "\n";
    }
    friend std::istream& operator>>(std::istream& is, Question& q) {
        std::string line;
        getline(is, line);
        std::vector<std::string> tokens = tokenize(line, ',');
        if (tokens.size() != 4) {
            return is;
        }
        q.id = std::stoi(tokens[0]);
        q.text = tokens[1];
        q.correct_answer = tokens[2];
        q.score = std::stoi(tokens[3]);
        return is;
    }
    int get_id() const  { return id; }
    std::string get_text() const  { return text; }
    std::string get_correct_answer()  const { return correct_answer; }
    int get_score()  const { return score; }
    Question(int i) {
        this->id = i;
        this->text = "";
        this->correct_answer = "";
        this->score = 0;
    }
    Question() {
        this->id = 0;
        this->text = "";
        this->correct_answer = "";
        this->score = 0;
    }
    Question(int i, std::string t, std::string c, int s)
        : id{i}
        , text{t}
        , correct_answer{c}
        , score{s}
    {

    }
    ~Question() {

    }
};

#endif // QUESTION_H
