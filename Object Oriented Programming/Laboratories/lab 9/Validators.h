#pragma once

#include <iostream>
#include <utility>
#include <cstring>
#include "Domain.h"
#include "Exceptions.h"


class GuardianStatueValidator {

public:
    static void validate(const GuardianStatue& guardianStatue) {
        if (guardianStatue.getPowerWordName().empty()) {
            throw ValidationError("Power Word Name cannot be empty!\n");
        }
        if (guardianStatue.getMaterial().empty()) {
            throw ValidationError("Material cannot be empty!\n");
        }
        if (guardianStatue.getAge() < 0) {
            throw ValidationError("Age cannot be a negative number!\n");
        }
        if (guardianStatue.getCorporealForm().empty()) {
            throw ValidationError("Corporeal Form cannot be empty!\n");
        }
    }
};