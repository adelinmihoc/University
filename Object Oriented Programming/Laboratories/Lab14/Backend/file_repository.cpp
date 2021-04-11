#include "file_repository.h"


File_repository::File_repository() :
    Repository{},
    filename{""} {

}

File_repository::~File_repository() {

}

void File_repository::add(Guardian_statue statue) {
    this->read_from_file();
    Repository::add(statue);
    this->write_to_file();
}

void File_repository::remove(std::string name) {
    this->read_from_file();
    Repository::remove(name);
    this->write_to_file();
}

void File_repository::update(Guardian_statue statue) {
    this->read_from_file();
    Repository::update(statue);
    this->write_to_file();
}

std::vector<Guardian_statue> File_repository::get_all() {
    this->read_from_file();
    return Repository::get_all();
}

int File_repository::get_size() {
    this->read_from_file();
    return Repository::get_size();
}

void File_repository::set_filename(std::string& name) {
    this->filename = name;
}

std::string File_repository::get_type() {
    return "file";
}

std::string File_repository::get_filename() {
    return this->filename;
}
