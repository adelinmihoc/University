#ifndef USERS_H
#define USERS_H

#include "user.h"
#include <vector>


class Users
{
private:
    std::vector<User> users;
public:
    Users();
    ~Users() {}
    std::vector<User> get_all() { return this->users; }
    void load_from_file();
};


#endif // USERS_H
