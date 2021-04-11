#include "action.h"


Action_add::Action_add(Guardian_statue _s, Repository* _r) :
    statue{_s},
    repository{_r} {

}

void Action_add::execute_undo() {
    repository->remove(statue.get_power_word_name());
}

void Action_add::execute_redo() {
    repository->add(statue);
}



Action_remove::Action_remove(Guardian_statue _s, Repository* _r) :
    statue{_s},
    repository{_r} {

}

void Action_remove::execute_undo() {
    repository->add(statue);
}

void Action_remove::execute_redo() {
    repository->remove(statue.get_power_word_name());
}



Action_update::Action_update(Guardian_statue _s1, Guardian_statue _s2, Repository* _r) :
    statue1{_s1},
    statue2{_s2},
    repository{_r} {

}

void Action_update::execute_undo() {
    repository->update(statue1);
}

void Action_update::execute_redo() {
    repository->update(statue2);
}




