#ifndef LAB14_EXCEPTIONS_H
#define LAB14_EXCEPTIONS_H


#include <exception>
#include <string>


class Exception : public std::exception {
protected:
    std::string message;
public:
    Exception(const std::string& msg) : message{msg} {}
    virtual const char* what() {
        return message.c_str();
    }
};


#endif //LAB14_EXCEPTIONS_H
