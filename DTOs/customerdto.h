#pragma once
#include <string>

struct CustomerDTO {
    int id = -1;              // Default invalid ID
    std::string name;
    int doctor_id = -1;
};
