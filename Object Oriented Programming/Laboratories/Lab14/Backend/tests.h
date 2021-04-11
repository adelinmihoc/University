#ifndef LAB14_TESTS_H
#define LAB14_TESTS_H

#include <string>

class Tests {
private:
    std::string message = "tests result:\n";
    void test_domain();
    void test_repository();
    void test_controller();
    void test_action();

public:
    void test_all();
    std::string get_message() { return message; }
};


#endif //LAB14_TESTS_H
