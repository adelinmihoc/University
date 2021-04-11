#ifndef LAB14_FILE_REPOSITORY_H
#define LAB14_FILE_REPOSITORY_H

#include "repository.h"


class File_repository : public Repository {
protected:
    std::string filename;
    virtual void read_from_file() = 0;
    virtual void write_to_file() = 0;
public:
    File_repository();
    virtual ~File_repository();

    void add(Guardian_statue statue) override;
    void remove(std::string name) override;
    void update(Guardian_statue statue) override;
    std::vector<Guardian_statue> get_all() override;
    int get_size() override;

    virtual void set_filename(std::string& name) override;
    virtual std::string get_type() override;
    std::string get_filename() override;
};


#endif //LAB14_FILE_REPOSITORY_H
