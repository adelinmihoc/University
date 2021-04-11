#ifndef USER_MESSAGE_H
#define USER_MESSAGE_H

#include "user.h"
#include "message.h"


class User_message {
private:
    User* user;
    Message* message;
public:
    User_message(User* u, Message* m) : user{u}, message{m} {}
    ~User_message() {
        //delete user;
        //delete message;
    }
    User* get_user() {return user;}
    Message* get_message() {return message;}
};

#endif // USER_MESSAGE_H
