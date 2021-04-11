#ifndef LAB14_GUARDIAN_STATUE_H
#define LAB14_GUARDIAN_STATUE_H

#include <string>
#include <fstream>
#include <sstream>


class Guardian_statue {
private:
    std::string power_word_name;
    std::string material;
    int age;
    std::string corporeal_form;
public:
    Guardian_statue(std::string _n, std::string _m, int _a, std::string _c);
    std::string get_power_word_name() const { return power_word_name; }
    std::string get_material() const  { return material; }
    int get_age() const { return age; }
    std::string get_corporeal_form() const { return corporeal_form; }

    friend std::istream& operator>>(std::istream& is, Guardian_statue& g);
    friend std::ostream & operator<<(std::ostream& os, const Guardian_statue& g);
    bool operator==(const Guardian_statue& g);
};


#endif //LAB14_GUARDIAN_STATUE_H
