#pragma once

#include <string>
#include "doctordto.h"

/**
 * @brief Data Transfer Object representing a customer.
 */
struct CustomerDTO {
    int id = -1;              ///< Unique identifier (default -1 for invalid)
    std::string name;         ///< Customer's name
    DoctorDTO doctor;         ///< Associated doctor
};
