#ifndef PARTICIPANTS_H
#define PARTICIPANTS_H


#include "participant.h"
#include <fstream>


class Participants
{
private:
    std::vector<Participant> participants;
public:
    std::vector<Participant> get_participants() { return participants; }
    void save_to_file() {
        std::ofstream f{"/home/adelin/OneDirToRuleThemAll/oop/Quiz/participants.txt"};
        if (!f.is_open()) {
            return;
        }
        for (auto p : participants) {
            f << p;
        }
    }
    void load_from_file() {
        std::ifstream f{"/home/adelin/OneDirToRuleThemAll/oop/Quiz/participants.txt"};
        if (!f.is_open()) {
            return;
        }
        Participant p;
        while (f >> p) {
            participants.push_back(p);
        }
        f.close();
    }
    Participants() {
        this->load_from_file();
    }
};

#endif // PARTICIPANTS_H
