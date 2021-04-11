#ifndef LAB14_CONTROLLER_H
#define LAB14_CONTROLLER_H

#include "repository.h"
#include "html_file.h"
#include "csv_file.h"
#include <stack>
#include "action.h"
#include <memory>


class Controller {
private:
    Repository* admin_repository;
    Repository* user_repository;
    int current;
    std::stack<std::unique_ptr<Action>> undo_stack;
    std::stack<std::unique_ptr<Action>> redo_stack;
public:
    Controller(Repository* _admin, Repository* _user);

    int get_admin_repository_size();
    int get_user_repository_size();

    Repository* get_admin_repository();

    std::string get_admin_repository_type() {
        return this->admin_repository->get_type();
    }
    std::string get_user_repository_type() {
        return this->user_repository->get_type();
    }

    void undo();
    void redo();

    void __admin_add_statue(std::string _n, std::string _m, int _a, std::string _c);
    void __admin_remove_statue(std::string name);
    void __admin_update_statue(std::string _n, std::string _m, int _a, std::string _c);
    std::vector<Guardian_statue> __admin_get_statues();
    void __admin_set_file_path(std::string path);

    std::vector<Guardian_statue> __user_get_statues();
    Guardian_statue __user_next_statue();
    void __user_save_statue(std::string name);
    std::vector<Guardian_statue> __user_filter_statues(std::string _m, int _a);
    void __user_set_file_path(std::string path);
};


#endif //LAB14_CONTROLLER_H
