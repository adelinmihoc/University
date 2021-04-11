#include "html_file.h"
#include "exceptions.h"


void Html_file::read_from_file() {
    std::ifstream f{this->filename};
    if (!f.is_open()) {
        throw Exception("Can't open file!\n");
    }
    this->statues.clear();
    std::string uselessStr;
    getline(f, uselessStr);
    std::string name, material,age, form;
    bool flag = true;
    while(flag) {
        getline(f, uselessStr);
        if (uselessStr.empty() || uselessStr == "</table></body></html>") {
            flag = false;
        }
        else {
            getline(f, name);
            getline(f, uselessStr);
            getline(f, material);
            getline(f, uselessStr);
            getline(f, age);
            getline(f, uselessStr);
            getline(f, form);
            getline(f, uselessStr);
            int age1 = std::stoi(age);
            Guardian_statue statue{name, material, age1, form};
            this->statues.push_back(statue);
        }
    }
}

void Html_file::write_to_file() {
    std::ofstream f{this->filename};
    if (!f.is_open()) {
        throw Exception("Can't open file!\n");
    }
    f << "<!DOCTYPE html><html><head><title>Apprentice Encyclopedia</title></head><body><table border=\"1\"><tr><td>Power Word Name</td><td>Material</td><td>Age</td><td>Corporeal Form</td></tr>\n";
    for (auto & statue : this->statues) {
        f << "<tr><td>\n";
        f << statue.get_power_word_name() << "\n";
        f << "</td><td>\n";
        f << statue.get_material() << "\n";
        f << "</td><td>\n";
        f << statue.get_age() << "\n";
        f << "</td><td>\n";
        f << statue.get_corporeal_form() << "\n";
        f << "</td></tr>\n";
    }
    f << "</table></body></html>\n";

    this->statues.clear();
}

Html_file::Html_file(std::string &filename) {
    this->set_filename(filename);
}

std::string Html_file::get_type() {
    return "html_file";
}
