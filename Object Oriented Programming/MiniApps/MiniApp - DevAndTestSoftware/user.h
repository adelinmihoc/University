#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <sstream>


class User {
private:
    std::string name;
    std::string type;
public:
    User(std::string n, std::string t) : name{n}, type{t} {}
    ~User() {}
    std::string get_name() { return name; }
    std::string get_type() { return type; }
    friend std::istream& operator>>(std::istream& is, User& u) {
        std::string line;
        getline(is, line);
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if (int(tokens.size()) != 2) {
            return is;
        }
        u.name = tokens[0];
        u.type = tokens[1];
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const User& u) {
        os << u.name << "," << u.type << "\n";
        return os;
    }
};

#endif // USER_H
