#ifndef LAB14_REPOSITORY_H
#define LAB14_REPOSITORY_H

#include <vector>
#include "guardian_statue.h"


class Repository {
protected:
    std::vector<Guardian_statue> statues;
public:
    Repository();
    virtual void add(Guardian_statue statue);
    virtual void remove(std::string name);
    virtual void update(Guardian_statue statue);
    std::vector<Guardian_statue>::iterator search(std::string name);
    virtual std::vector<Guardian_statue> get_all();
    virtual int get_size();
    virtual void set_filename(std::string& name);
    virtual std::string get_filename();
    virtual std::string get_type();
};


#endif //LAB14_REPOSITORY_H
