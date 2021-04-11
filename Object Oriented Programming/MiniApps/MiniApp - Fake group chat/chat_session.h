#ifndef CHAT_SESSION_H
#define CHAT_SESSION_H

#include "user_message.h"
#include <vector>
#include "Observer.h"


class Chat_session : public Subject {
private:
    std::vector<User_message*> messages;
public:
    Chat_session() {}
    ~Chat_session() {}

    std::vector<User_message*> get_messages() {return messages;}
    void add_message(User* u, Message* m) {
        User_message* new_user_message = new User_message{u,m};
        this->messages.push_back(new_user_message);

        this->notify();
    }
};

#endif // CHAT_SESSION_H
