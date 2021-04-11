#include "question.h"
#include "utils.h"
#include <fstream>


std::istream& operator>>(std::istream& is, Question& q) {
    std::string line;
    getline(is, line);
    if (line.empty()) {
        return is;
    }
    std::vector<std::string> tokens = tokenize(line, ',');
    if (tokens.size() != 3) {
        return is;
    }
    q.id = tokens[0];
    q.name = tokens[1];
    q.text = tokens[2];

    return is;
}
std::ostream& operator<<(std::ostream& os,const Question& q) {
    os << q.id << "," << q.text << "," << q.name << "\n";
    return os;
}
