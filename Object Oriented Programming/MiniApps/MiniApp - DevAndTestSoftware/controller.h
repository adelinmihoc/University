#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "issue.h"
#include "user.h"
#include "observer.h"
#include <QDebug>


class Controller : public Subject {
private:
    std::vector<Issue> issues;
public:
    Controller() {}
    ~Controller() {}
    std::vector<Issue> get_issues() { return issues; }
    void add_issue(User u, std::string descr) {
        Issue is{descr, false, u.get_name(), ""};
        this->issues.push_back(is);

        this->notify();
    }
    void remove_issue(std::string descr) {
        Issue is{descr, 0, "", ""};
        auto it = std::find(this->issues.begin(), this->issues.end(), is);
        if (it != this->issues.end()) {
            if (it->get_status() == true) {
                this->issues.erase(it);
            }
        }

        this->notify();
    }
    void solve_issue(User u, std::string descr) {
        Issue is{descr, 0, "", ""};
        auto it = std::find(this->issues.begin(), this->issues.end(), is);
        if (it != issues.end()) {
            issues[std::distance(issues.begin(),it)].set_status_true();
            issues[std::distance(issues.begin(),it)].set_solver(u.get_name());
        }

        this->notify();
    }
};

#endif // CONTROLLER_H
