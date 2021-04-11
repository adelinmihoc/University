#include "answer.h"
#include "utils.h"


std::istream &operator>>(std::istream &is, Answer &a) {
    std::string line;
    getline(is, line);
    if (line.empty()) {
        return is;
    }
    std::vector<std::string> tokens = tokenize(line, ',');
    if (tokens.size() != 5) {
        return is;
    }
    a.id = tokens[0];
    a.qid = tokens[1];
    a.name = tokens[2];
    a.text = tokens[3];
    a.no_of_votes =std::stoi(tokens[4]);

    return is;

}

std::ostream &operator>>(std::ostream &os, const Answer &a) {
    os << a.id << "," << a.qid << "," << a.name << "," <<a.text << "," << a.no_of_votes << "\n";
    return os;
}
