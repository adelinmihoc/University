#ifndef ANSWER_H
#define ANSWER_H

#include <string>


class Answer
{
private:
    std::string id;
    std::string qid;
    std::string name;
    std::string text;
    int no_of_votes;
public:
    Answer(const std::string i,
           const std::string q,
           const std::string n,
           const std::string t,
           int v)
        : id{i}
        , qid{q}
        , name{n}
        , text{t}
        , no_of_votes{v}
    {

    }
    ~Answer() {}
    std::string get_id() const { return id; }
    std::string get_qid()const { return qid; }
    std::string get_name()const { return name; }
    std::string get_text()const { return text; }
    int get_no_of_votes()const { return no_of_votes; }
    friend std::istream &operator>>(std::istream &is, Answer &a);
    friend std::ostream &operator>>(std::ostream &os, const Answer &a);
    void increase_votes() { this->no_of_votes += 1; }
    void decrease_votes() { this->no_of_votes -= 1; }

};

#endif // ANSWER_H
