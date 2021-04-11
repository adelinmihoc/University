#ifndef USER_H
#define USER_H

#include <string>


class User {
private:
    std::string username;
    std::string name;
public:
    User(std::string un, std::string n) : username{un}, name{n} {}
    //~User() {}
    std::string get_username() {return username;}
    std::string get_name() {return name;}
    void set_username(std::string un) {username = un;}
    void set_name(std::string n) {name = n;}

};

#endif // USER_H
