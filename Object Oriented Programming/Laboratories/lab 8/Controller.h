#pragma once
#include "Repository.h"
#include "Iterator.h"
#include "UserFile.h"



class Enchantment {
private:
    //Encyclopedia encyclopedia;
    ArchmageEncyclopedia encyclopedia;
    Encyclopedia apprenticeEncyclopedia;
    ApprenticeIterator encyclopediaIterator;
public:
    //Constructor function for enchantment
    explicit Enchantment(ArchmageEncyclopedia& enclp/*Encyclopedia& enclp*/) : encyclopedia{ enclp }, apprenticeEncyclopedia(), encyclopediaIterator{ /*enclp.getAllStatues() */} {}


    //Function that creates a guardian statue and adds it in the encyclopedia
    void addGuardianStatue(const std::string& powerWordName, const std::string& material, const int& age, const std::string& corporealForm);


    //Function that deletes a guardian statue from the encyclopedia
    void deleteGuardianStatue(const std::string& powerWordName);


    //Function that updates a guardian statue
    void updateGuardianStatue(const std::string& powerWordName, const std::string& newMaterial, const int& newAge, const std::string& newCorporealForm);


    //Getter for size in the encyclopedia
    [[nodiscard]] int getSize();


    //Getter for all the statues
    std::vector<GuardianStatue> getAllGuardianStatues();


    void setFilePath(std::string& filepath);


    /////////////////////////////////////////////////////////////////


    //Getter for the apprentice's statues
    std::vector<GuardianStatue> getAllApprenticeGuardianStatues();


    //Initialise the 'statues' field of the iterator
    void initialiseIterator();


    //Getter function for the next guardian statue
    GuardianStatue nextGuardianStatues();


    //Saves the current guardian statue from the iterator in the apprenticeEncyclopedia
    void saveGuardianStatue(const std::string& powerWordName);


    //Searches for the statue by its name and returns its position or -1 if not found
    int searchGuardianStatue(const std::string& powerWordName);


    //Function that gets the statues by material
    std::vector<GuardianStatue> getAllApprenticesStatuesByMaterial(const std::string& material);


    //Function that gets all the apprentice statues by a given age
    std::vector<GuardianStatue> getAllApprenticeStatuesByMaterialAndAge(const std::string& material, int age);
};
