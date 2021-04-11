#ifndef LAB14_VALIDATORS_H
#define LAB14_VALIDATORS_H

#include "guardian_statue.h"
#include "exceptions.h"

class Guardian_statue_validator {
public:
    static void validate_statue(Guardian_statue g) {
        std::string errors = "";
        if (g.get_power_word_name().empty()) {
            errors += "<Power word name> invalid!\n";
        }
        if (g.get_material().empty()) {
            errors += "<Material> invalid!\n";
        }
        if (g.get_age() < 0) {
            errors += "<Age> invalid!\n";
        }
        if (g.get_corporeal_form().empty()) {
            errors += "<Corporeal form> invalid!\n";
        }
        if (!errors.empty()) {
            throw Exception(errors);
        }
    }
};


#endif //LAB14_VALIDATORS_H
