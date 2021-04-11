#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>


class GuardianStatue {
private:
    std::string powerWordName;
    std::string material;
    int age;
    std::string corporealForm;
public:
    //Default constructor
    GuardianStatue();


    //Constructor function for GuardianStatue
    GuardianStatue(const std::string& powerWordName, const std::string& material, const int& age, const std::string& corporealForm);


    //Getter for powerWordName
    [[nodiscard]] std::string getPowerWordName() const { return powerWordName; }


    //Getter for material
    [[nodiscard]] std::string getMaterial() const { return material; }


    //Getter for age
    [[nodiscard]] int getAge() const { return age; }


    //Getter for corporealForm
    [[nodiscard]] std::string getCorporealForm() const { return corporealForm; }


    friend std::ostream & operator << (std::ostream & out, const GuardianStatue & obj) {
        out << obj.powerWordName << "," << obj.material << "," << obj.age << "," << obj.corporealForm << "\n";
        return out;
    }


    friend std::istream & operator >> (std::istream & in, GuardianStatue & obj) {
        std::string line;
        std::getline(in, line);
        if (line.empty()) {
            throw std::exception();
        }
        //std::cout << line << "\n";
        std::stringstream split(line);
        std::string token;
        std::vector<std::string> vec;
        while(std::getline(split, token, ',')) {
            vec.push_back(token);
        }
        /*for (auto & str : vec) {
            std::cout << str << " | ";
        }
        std::cout <<"\n";*/
        obj.powerWordName = vec[0];
        obj.material = vec[1];
        std::stringstream to_int(vec[2]);
        int i = 0;
        to_int >> i;
        obj.age = i;
        obj.corporealForm = vec[3];
        return in;
    }
};
