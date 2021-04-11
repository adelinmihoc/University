#pragma once

#include "Repository.h"


class ApprenticeEncyclopedia : public Encyclopedia{
private:
    std::string encyclopediaName;
    std::string fileType;
    void csv_readAllFromFile();
    void csv_writeAllToFile();
    void html_readAllFromFile();
    void html_writeAllToFile();

public:
    explicit ApprenticeEncyclopedia() { this->encyclopediaName = "htmlfile.html"; this->fileType = "html"; }
    void setFileName(std::string name);
    void setFileType(std::string type);
    std::string getFileName() { return this->encyclopediaName; }
    void csv_saveGuardianStatueFile(const GuardianStatue & guardianStatue);
    std::vector<GuardianStatue> csv_getAllFile();
};