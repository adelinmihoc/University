#include "controller.h"
#include "validators.h"


Controller::Controller(Repository* _admin, Repository* _user) :
    admin_repository{_admin},
    user_repository{_user} {
    this->current = 0;
}

int Controller::get_admin_repository_size() {
    return this->admin_repository->get_size();
}

int Controller::get_user_repository_size() {
    return this->user_repository->get_size();
}

Repository* Controller::get_admin_repository() {
    return this->admin_repository;
}

void Controller::undo() {
    if (this->undo_stack.empty()) {
        throw Exception("No more undo!\n");
    }
    undo_stack.top()->execute_undo();
    redo_stack.push(move(undo_stack.top()));
    undo_stack.pop();
}

void Controller::redo() {
    if (this->redo_stack.empty()) {
        throw Exception("No more redo!\n");
    }
    redo_stack.top()->execute_redo();
    undo_stack.push(move(redo_stack.top()));
    redo_stack.pop();
}

void Controller::__admin_add_statue(std::string _n, std::string _m, int _a, std::string _c) {
    try {
        Guardian_statue new_statue{_n, _m, _a, _c};
        Guardian_statue_validator::validate_statue(new_statue);

        this->admin_repository->add(new_statue);

        std::unique_ptr<Action> action = std::make_unique<Action_add>(new_statue, admin_repository);
        undo_stack.push(move(action));
        while(!redo_stack.empty()) {
            redo_stack.pop();
        }
    } catch (Exception& e) {
        throw Exception(e.what());
    }
}

void Controller::__admin_remove_statue(std::string name) {
    try {
        Guardian_statue stat{"", "", 0, ""};
        for (auto s : admin_repository->get_all()) {
            if (s.get_power_word_name() == name) {
                stat = s;
                break;
            }
        }

        this->admin_repository->remove(name);

        std::unique_ptr<Action> action = std::make_unique<Action_remove>(stat, admin_repository);
        undo_stack.push(move(action));
        while(!redo_stack.empty()) {
            redo_stack.pop();
        }
    } catch (Exception& e) {
        throw Exception(e.what());
    }
}

void Controller::__admin_update_statue(std::string _n, std::string _m, int _a, std::string _c) {
    try {
        Guardian_statue new_statue{_n, _m, _a, _c};
        Guardian_statue_validator::validate_statue(new_statue);
        Guardian_statue statue{"", "", 0, ""};
        for (auto s : admin_repository->get_all()) {
            if (s.get_power_word_name() == _n) {
                statue = s;
                break;
            }
        }

        this->admin_repository->update(new_statue);

        std::unique_ptr<Action> action = std::make_unique<Action_update>(statue, new_statue, admin_repository);
        undo_stack.push(move(action));
        while(!redo_stack.empty()) {
            redo_stack.pop();
        }
    } catch (Exception& e) {
        throw Exception(e.what());
    }
}

std::vector<Guardian_statue> Controller::__admin_get_statues() {
    return this->admin_repository->get_all();
}

void Controller::__admin_set_file_path(std::string path) {
    std::ifstream f{path};
    if (!f.is_open()) {
        throw Exception("File does not exits!\n");
    }
    std::string filename = path;
    std::string::size_type idx = filename.rfind('.');
    if (idx != std::string::npos) {
        std::string extension = filename.substr(idx + 1);
        if (extension == "csv" && this->admin_repository->get_type() != "csv_file") {
            throw Exception("File not supported! HTML file required!\n");
        } else if (extension == "html" && this->admin_repository->get_type() != "html_file") {
            throw Exception("File not supported! CSV file required!\n");
        }
        this->admin_repository->set_filename(path);
    } else {
        throw Exception("File not supported! No extension found!\n");
    }
}



std::vector<Guardian_statue> Controller::__user_get_statues() {
    return this->user_repository->get_all();
}

Guardian_statue Controller::__user_next_statue() {
    if (this->admin_repository->get_size() == 0) {
        throw Exception("Admin repository empty!\n");
    }
    Guardian_statue result =  this->admin_repository->get_all()[this->current];
    this->current += 1;
    if (this->current >= this->admin_repository->get_size()) {
        this->current = 0;
    }
    return result;
}

void Controller::__user_save_statue(std::string name) {
    for (auto s : this->admin_repository->get_all()) {
        if (s.get_power_word_name() == name) {
            this->user_repository->add(s);
            return;
        }
    }
    throw Exception("Can't find statue!\n");
}

std::vector<Guardian_statue> Controller::__user_filter_statues(std::string _m, int _a) {
    std::vector<Guardian_statue> result;
    for (auto s : this->user_repository->get_all()) {
        if (s.get_material() == _m && s.get_age() < _a) {
            result.push_back(s);
        }
    }
    return result;
}

void Controller::__user_set_file_path(std::string path) {
    std::ifstream f{path};
    if (!f.is_open()) {
        throw Exception("File does not exist!\n");
    }
    std::string filename = path;
    std::string::size_type idx = filename.rfind('.');
    if (idx != std::string::npos) {
        std::string extension = filename.substr(idx + 1);
        if (extension == "csv" && this->user_repository->get_type() != "csv_file") {
            throw Exception("File not supported! HTML file required!\n");
        } else if (extension == "html" && this->user_repository->get_type() != "html_file") {
            throw Exception("File not supported! CSV file required!\n");
        }
        this->user_repository->set_filename(path);
    } else {
        throw Exception("File not supported! No extension found!\n");
    }
}


