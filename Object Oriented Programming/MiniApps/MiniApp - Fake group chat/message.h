#ifndef MESSAGE_H
#define MESSAGE_H

#include <QDateTime>


class Message {
private:
    std::string timestamp;
    std::string message;
public:
    Message(std::string t, std::string m) : timestamp{t}, message{m} {}
    ~Message() {}
    std::string get_timestamp() {return timestamp;}
    std::string get_message() {return message;}
};

#endif // MESSAGE_H
