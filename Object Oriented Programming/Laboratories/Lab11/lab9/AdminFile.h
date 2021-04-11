#include "Repository.h"


class ArchmageEncyclopedia : public Encyclopedia {
private:
    std::string encyclopediaName;
    void readAllFromFile();
    void writeAllToFile();
public:
    explicit ArchmageEncyclopedia() { this->encyclopediaName = ""; }
    void setFileName(std::string& filename);
    [[nodiscard]] int sizeFile();
    void addGuardianStatueFile(const GuardianStatue & guardianStatue);
    void deleteGuardianStatueFile(const std::string & powerName);
    void updateGuardianStatueFile(const GuardianStatue& guardianStatue);
    std::vector<GuardianStatue> getAllFile();
    void display();

};