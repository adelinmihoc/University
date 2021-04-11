#include "UserFile.h"

#include <utility>
#include "Exceptions.h"
#include <stdlib.h>
//#include <Windows.h>


void ApprenticeEncyclopedia::csv_readAllFromFile() {
/*    if (this->encyclopediaName.empty()) {
       throw FileError("Path not set!\n");
    }*/
    this->statues.clear();
    std::ifstream in;
    in.open(this->encyclopediaName);
    if (in.is_open()) {
        GuardianStatue statue;
        bool flag = true;
        while(flag) {
            try {
                in >> statue;
                this->statues.push_back(statue);
            }
            catch (std::exception &) {
                flag = false;
            }
        }
    }
    else {
        throw FileError("Couldn't open file!\n");
    }
    in.close();
}

void ApprenticeEncyclopedia::csv_writeAllToFile() {
    std::ofstream out;
    out.open(this->encyclopediaName);
    if (out.is_open()) {
        //out.clear();
        for (auto & statue : this->statues) {
            out << statue;
        }
    }
    this->statues.clear();
    out.close();
}

void ApprenticeEncyclopedia::html_readAllFromFile() {
    this->statues.clear();
    std::ifstream in;
    in.open(this->encyclopediaName);
    std::string uselessStr;
    if (in.is_open()) {
        getline(in, uselessStr);
        std::string name, material,age, form;
        bool flag = true;
        while(flag) {
            getline(in, uselessStr);
            if (uselessStr.empty() || uselessStr == "</table></body></html>") {
                flag = false;
            }
            else {
                getline(in, name);
                getline(in, uselessStr);
                getline(in, material);
                getline(in, uselessStr);
                getline(in, age);
                getline(in, uselessStr);
                getline(in, form);
                getline(in, uselessStr);
                int age1 = std::stoi(age);
                GuardianStatue statue {name, material, age1, form};
                this->statues.push_back(statue);
            }
        }
    }
    else {
        throw FileError("Couldn't open file!\ndunno why :|\n");
    }
    in.close();
}

void ApprenticeEncyclopedia::html_writeAllToFile() {
    std::ofstream out;
    out.open(this->encyclopediaName);
    if (out.is_open()) {
        out << "<!DOCTYPE html><html><head><title>Apprentice Encyclopedia</title></head><body><table border=\"1\"><tr><td>Power Word Name</td><td>Material</td><td>Age</td><td>Corporeal Form</td></tr>\n";
        for (auto & statue : this->statues) {
            out << "<tr><td>\n";
            out << statue.getPowerWordName() << "\n";
            out << "</td><td>\n";
            out << statue.getMaterial() << "\n";
            out << "</td><td>\n";
            out << statue.getAge() << "\n";
            out << "</td><td>\n";
            out << statue.getCorporealForm() << "\n";
            out << "</td></tr>\n";
        }
        out << "</table></body></html>\n";
    }
    this->statues.clear();
    out.close();
}

void ApprenticeEncyclopedia::setFileName(std::string name) {
    this->encyclopediaName = std::move(name);
}

void ApprenticeEncyclopedia::setFileType(std::string type) {
    this->fileType = std::move(type);
}

void ApprenticeEncyclopedia::csv_saveGuardianStatueFile(const GuardianStatue &guardianStatue) {
    if (this->fileType == "html") {
        this->html_readAllFromFile();
    }
    else {
        this->csv_readAllFromFile();
    }

    this->addStatue(guardianStatue);

    if (this->fileType == "html") {
        this->html_writeAllToFile();
    }
    else {
        this->csv_writeAllToFile();
    }
}

std::vector<GuardianStatue> ApprenticeEncyclopedia::csv_getAllFile() {
    if (this->fileType == "html") {
        this->html_readAllFromFile();
    }
    else {
        this->csv_readAllFromFile();
    }
    return this->getAllStatues();
}

void ApprenticeEncyclopedia::display() {
    if(this->fileType != "html") {
        /*std::string aux = "notepad \"" + this->encyclopediaName + "\"";
        system(aux.c_str());*/
        //ShellExecuteA(NULL, NULL, "C:\\Program Files\\Windows NT\\Accessories\\wordpad.exe", this->encyclopediaName.c_str(), NULL, SW_SHOWMAXIMIZED);
    }
    else {
        //ShellExecuteA(NULL, NULL, "C:\\Program Files\\Internet Explorer\\iexplore.exe", this->encyclopediaName.c_str(), NULL, SW_SHOWMAXIMIZED);
    }
}


