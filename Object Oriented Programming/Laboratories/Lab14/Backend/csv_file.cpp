#include "csv_file.h"
#include "exceptions.h"


void Csv_file::read_from_file() {
    std::ifstream f{this->filename};
    if (!f.is_open()) {
        throw Exception("Can't open file!\n");
    }
    this->statues.clear();
    Guardian_statue statue{"","", 0,""};
    while (f >> statue) {
        this->statues.push_back(statue);
    }
}

void Csv_file::write_to_file() {
    std::ofstream f{this->filename};
    if (!f.is_open()) {
        throw Exception("Can't open file!\n");
    }
    for (auto s : this->statues) {
        f << s;
    }
    this->statues.clear();

}

Csv_file::Csv_file(std::string& filename) {
    this->set_filename(filename);
}

std::string Csv_file::get_type() {
    return "csv_file";
}
