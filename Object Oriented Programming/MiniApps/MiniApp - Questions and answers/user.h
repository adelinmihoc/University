#ifndef USER_H
#define USER_H


#include <string>


class User
{
private:
    std::string name;
public:
    User(const std::string n)
        : name{n}
    {

    }
    ~User() {}
    std::string get_name() const { return name; }
    friend std::istream& operator>>(std::istream& is, User& u);
    friend std::ostream& operator<<(std::ostream& os,const User& u);
};

#endif // USER_H
