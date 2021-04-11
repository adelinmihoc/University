#ifndef LAB14_HTML_FILE_H
#define LAB14_HTML_FILE_H

#include "file_repository.h"


class Html_file : public File_repository {
private:
    void read_from_file() override;
    void write_to_file() override;

public:
    Html_file(std::string& filename);
    std::string get_type() override;
};


#endif //LAB14_HTML_FILE_H
