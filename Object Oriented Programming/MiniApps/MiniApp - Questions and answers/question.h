#ifndef QUESTION_H
#define QUESTION_H


#include <string>

class Question
{
private:
    std::string id;
    std::string text;
    std::string name;
public:
    Question(const std::string i, const std::string t, const std::string n)
        : id{i}
        , text{t}
        , name {n}
    {

    }
    ~Question() {}
    std::string get_id()const { return id; }
    std::string get_name()const { return name; }
    std::string get_text()const { return text; }
    friend std::istream& operator>>(std::istream& is, Question& q);
    friend std::ostream& operator<<(std::ostream& os,const Question& q);

};

#endif // QUESTION_H
