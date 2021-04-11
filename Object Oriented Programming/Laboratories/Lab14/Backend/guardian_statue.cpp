#include "guardian_statue.h"
#include "utils.h"


Guardian_statue::Guardian_statue(std::string _n, std::string _m, int _a, std::string _c):
    power_word_name{_n},
    material{_m},
    age {_a},
    corporeal_form{_c} {

}

std::istream &operator>>(std::istream &is, Guardian_statue &g) {
    std::string line;
    getline(is, line);
    if (line.empty()) {
        return is;
    }
    std::vector<std::string> tokens = tokenize(line, ',');
    if (tokens.size() != 4) {
        return is;
    }
    g.power_word_name = tokens[0];
    g.material = tokens[1];
    g.age = std::stoi(tokens[2]);
    g.corporeal_form = tokens[3];
    return is;
}

std::ostream &operator<<(std::ostream &os, const Guardian_statue &g) {
    return os << g.get_power_word_name() << "," << g.get_material() << "," << g.get_age() << "," << g.get_corporeal_form() << "\n";
}

bool Guardian_statue::operator==(const Guardian_statue &g) {
    return this->get_power_word_name() == g.get_power_word_name();
}
