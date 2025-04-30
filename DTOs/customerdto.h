#pragma once
#include <string>
#include "doctordto.h"

struct CustomerDTO {
    int id = -1;              // Default invalid ID
    std::string name;
    DoctorDTO doctor;
};
