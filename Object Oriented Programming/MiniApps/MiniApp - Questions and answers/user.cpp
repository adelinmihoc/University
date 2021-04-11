#include "user.h"
#include "utils.h"


std::istream& operator>>(std::istream& is, User& u) {
    std::string line;
    getline(is, line);
    if (line.empty()) {
        return is;
    }
    std::vector<std::string> tokens = tokenize(line, ',');
    if (tokens.size() != 1) {
        return is;
    }
    u.name = tokens[0];

    return is;
}


std::ostream& operator<<(std::ostream& os,const User& u) {
    os << u.name << "\n";
    return os;
}
