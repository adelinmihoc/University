#include "Tests.h"
#include "UserInterface.h"
#include "Exceptions.h"


int main() {

    Tests::testAll();
    {
        //Encyclopedia encl = Encyclopedia(); //Normal repository
        ArchmageEncyclopedia encl = ArchmageEncyclopedia(); // File repository
        Enchantment ench = Enchantment(encl); //Controller
        /*ench.addGuardianStatue("Piertotum Locomotor", "stone", 358, "Warrior with poleax");
        ench.addGuardianStatue("Laykyun Setkyar", "marble", 287, "Bouddha");
        ench.addGuardianStatue("Ushiku Daibutsu", "bronze", 890, "Amitabha");
        ench.addGuardianStatue("Guanyin", "stone", 78, "Guanyin");
        ench.addGuardianStatue("Emperors Yan and Huang", "rock", 46, "Yan Di et Huang Di");
        ench.addGuardianStatue("Dai", "marble", 1500, "White Daikannon");
        ench.addGuardianStatue("Peter the Great", "metal", 708, "Peter the Great");
        ench.addGuardianStatue("The legendary beauty of the Miao", "marble", 3, "Yang'asha");
        ench.addGuardianStatue("Birth of the New World", "metal", 236, "Christopher Colombus");*/

        /*ench.saveGuardianStatue("Birth of the New World");
        ench.saveGuardianStatue("Peter the Great");
        ench.saveGuardianStatue("Emperors Yan and Huang");
        ench.saveGuardianStatue("Ushiku Daibutsu");
        ench.saveGuardianStatue("Piertotum Locomotor");*/


       /* GuardianStatue g1 = {"asdf dfas asd", "adfs dsda", 123, "das"};
        std::ofstream out1;
        out1.open ("/home/adelin/CLionProjects/FirstTry/dataout.txt");
        if (out1.is_open()) {
            //out1 << "SAdjads\n";
            out1 << g1;
            out1 << g1;
        }
        else {
            std::cout << "FILE NOT OPEN!\n";
        }
        out1.close();
        GuardianStatue g3;
        GuardianStatue g4;
        std::ifstream in;
        in.open("/home/adelin/CLionProjects/FirstTry/dataout.txt");
        if (in.is_open()) {
            in >> g3;
            in >> g4;
        }
        in.close();
        std::cout << g3.getPowerWordName() << " | " << g3.getMaterial() << " | " << g3.getAge() << " | " << g4.getCorporealForm() << "\n";
*/
        RunicAltar runicAltar = RunicAltar(ench); //UI
        runicAltar.lightRunicAltar(); //Run program
    }

    return 0;
}