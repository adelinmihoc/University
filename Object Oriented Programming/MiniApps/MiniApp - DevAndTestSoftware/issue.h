#ifndef ISSUE_H
#define ISSUE_H

#include <string>
#include <fstream>
#include <vector>
#include <sstream>


class Issue {
private:
    std::string description;
    bool status;
    std::string reporter;
    std::string solver;
public:
    Issue(std::string d, bool st, std::string r, std::string so)
        : description{d}
        , status{st}
        , reporter{r}
        , solver{so}
    {

    }
    ~Issue() {}
    std::string get_description() { return description; }
    bool get_status() { return status; }
    void set_status_true() { status = true; }
    std::string get_reporter() { return reporter; }
    std::string get_solver() { return solver; }
    void set_solver(std::string s) { solver = s; }
    friend std::istream& operator>>(std::istream& is, Issue& i) {
        std::string line;
        getline(is, line);
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if (int(tokens.size()) != 4) {
            return is;
        }
        i.description = tokens[0];
        if (tokens[1] == "1") {
            i.status = true;
        } else {
            i.status = false;
        }
        i.reporter = tokens[2];
        if (tokens[3] == "") {
            i.solver = "";
        } else {
            i.solver = tokens[3];
        }
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const Issue& i) {
        os << i.description << "," << i.status << "," << i.reporter << ",";
        if (i.solver == "") {
            os << ",";
        } else {
            os << i.solver;
        }
        os << "\n";
        return os;
    }
    bool operator==(Issue is) {
        return this->description == is.description;
    }
};

#endif // ISSUE_H
