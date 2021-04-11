#pragma once
#include <utility>

#include "Controller.h"


class RunicAltar {
private:
    Enchantment enchantment;
public:
    //Constructor for user interface
    explicit RunicAltar(Enchantment  ench) : enchantment(std::move(ench)) {}

    //Run function for main program
    void lightRunicAltar();

    //Run function for admin mode
    void communionPatternMage();

    //Run function for user mode
    void communionPatternApprentice();

    void setFilePath(const std::string& parametersLine);
private:
    //Prints a help menu for admin mode
    static void showEnchantmentsMage();


    //Prints a help menu for user mode
    static void showEnchantmentsApprentice();


    //Prints a help menu for main program
    static void showEnchantmentsFirstFire();


    //Adds a new item
    void addGuardianStatue(const std::string& parametersLine);


    //Deletes an item
    void deleteGuardianStatue(const std::string& parametersLine);


    //Updates an item
    void updateGuardianStatue(const std::string& parametersLine);


    //List all items
    void listAllGuardianStatues(const std::string& parametersLine);


    /////////////////////////////////////////////////////////


    //See the next Guardian Statue
    void nextGuardStatue(const std::string& parametersLine);


    //Saves the current Guardian Statue
    void saveGuardianStatue(const std::string& parametersLine);


    //Lists all apprentice's statues
    void listAllApprenticeStatues(const std::string& parametersLine);


    //List all apprentice's statues by material and age
    void listAllStatuesByMaterialAndAge(const std::string& parametersLine);

    void setUserFilePath(const std::string &parametersLine);
};