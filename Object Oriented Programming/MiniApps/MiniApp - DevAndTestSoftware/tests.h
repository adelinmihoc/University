#ifndef TESTS_H
#define TESTS_H

#include <QDebug>
#include <cassert>
#include <fstream>
#include "controller.h"


void test_user() {
    qDebug("Testing user!");
    User u{"James", "Tester"};
    assert(u.get_name() == "James");
    assert(u.get_type() == "Tester");

    qDebug("Testing user file writing!");
    std::ofstream f_write("user_file_test.txt");
    User u1{"name1", "type1"};
    User u2{"name2", "type2"};
    User u3{"name3", "type3"};
    User u4{"name4", "type4"};
    User u5{"name5", "type5"};
    f_write << u1;
    f_write << u2;
    f_write << u3;
    f_write << u4;
    f_write << u5;
    f_write.close();

    qDebug("Testing user file reading!");
    std::ifstream f_read("user_file_test.txt");
    if (!f_read.is_open()) {
        assert(false);
    }
    assert(true);
    std::vector<User> users;
    while(f_read >> u) {
        users.push_back(u);
    }
    assert(int(users.size()) == 5);

    assert(users[0].get_name() == "name1");
    assert(users[1].get_name() == "name2");
    assert(users[2].get_name() == "name3");
    assert(users[3].get_name() == "name4");
    assert(users[4].get_name() == "name5");

    assert(users[0].get_type() == "type1");
    assert(users[1].get_type() == "type2");
    assert(users[2].get_type() == "type3");
    assert(users[3].get_type() == "type4");
    assert(users[4].get_type() == "type5");
}

void test_issue() {
    qDebug("Testing issue!");
    Issue is{"description", true, "James", "Andrew"};
    assert(is.get_description() == "description");
    assert(is.get_status() == true);
    assert(is.get_reporter() == "James");
    assert(is.get_solver() == "Andrew");

    qDebug("Testing issue file writing!");
    std::ofstream f_write{"issue_file_test.txt"};
    Issue is1{"description1", true, "reporter1", "solver1"};
    Issue is2{"description2", false, "reporter2", ""};
    Issue is3{"description3", true, "reporter3", "solver3"};
    Issue is4{"description4", false, "reporter4", ""};
    Issue is5{"description5", true, "reporter5", "solver5"};
    f_write << is1;
    f_write << is2;
    f_write << is3;
    f_write << is4;
    f_write << is5;
    f_write.close();

    qDebug("Testing issue file reading!");
    std::ifstream f_read{"issue_file_test.txt"};
    if (!f_read.is_open()) {
        assert(false);
    }
    assert(true);
    std::vector<Issue> issues;
    while(f_read >> is) {
        issues.push_back(is);
    }
    assert(int(issues.size()) == 5);

    assert(issues[0].get_description() == "description1");
    assert(issues[1].get_description() == "description2");
    assert(issues[2].get_description() == "description3");
    assert(issues[3].get_description() == "description4");
    assert(issues[4].get_description() == "description5");

    assert(issues[0].get_status() == true);
    assert(issues[1].get_status() == false);
    assert(issues[2].get_status() == true);
    assert(issues[3].get_status() == false);
    assert(issues[4].get_status() == true);

    assert(issues[0].get_reporter() == "reporter1");
    assert(issues[1].get_reporter() == "reporter2");
    assert(issues[2].get_reporter() == "reporter3");
    assert(issues[3].get_reporter() == "reporter4");
    assert(issues[4].get_reporter() == "reporter5");

    assert(issues[0].get_solver() == "solver1");
    assert(issues[1].get_solver() == "");
    assert(issues[2].get_solver() == "solver3");
    assert(issues[3].get_solver() == "");
    assert(issues[4].get_solver() == "solver5");
}

void test_controller() {
    qDebug("Testing controller!");
    Controller ctrl{};
    assert(int(ctrl.get_issues().size()) == 0);
    User u{"James", "Tester"};
    ctrl.add_issue(u, "Description1");
    ctrl.add_issue(u, "Description2");
    ctrl.add_issue(u, "Description3");
    ctrl.add_issue(u, "Description4");
    ctrl.add_issue(u, "Description5");
    assert(int(ctrl.get_issues().size()) == 5);

    ctrl.remove_issue("Description1");
    assert(int(ctrl.get_issues().size()) == 5);

    ctrl.solve_issue(u, "Description1");
    assert(ctrl.get_issues()[0].get_status() == true);

    ctrl.remove_issue("Description1");
    assert(int(ctrl.get_issues().size()) == 4);


}

void test_all() {
    test_user();
    test_issue();
    test_controller();
    qDebug("All tests good!");
}

#endif // TESTS_H
