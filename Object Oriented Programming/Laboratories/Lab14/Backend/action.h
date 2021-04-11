#ifndef ACTION_H
#define ACTION_H

#include "Backend/repository.h"

class Action {
public:
    virtual void execute_undo() = 0;
    virtual void execute_redo() = 0;
};


class Action_add : public Action {
private:
    Guardian_statue statue;
    Repository* repository;
public:
    Action_add(Guardian_statue _s, Repository* _r);
    void execute_undo() override;
    void execute_redo() override;
};


class Action_remove : public Action {
private:
    Guardian_statue statue;
    Repository* repository;
public:
    Action_remove(Guardian_statue _s, Repository* _r);
    void execute_undo() override;
    void execute_redo() override;
};


class Action_update : public Action {
private:
    Guardian_statue statue1;
    Guardian_statue statue2;
    Repository* repository;
public:
    Action_update(Guardian_statue _s1, Guardian_statue _s2, Repository* _r);
    void execute_undo() override;
    void execute_redo() override;
};

#endif // ACTION_H
