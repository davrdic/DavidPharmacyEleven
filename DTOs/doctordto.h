#pragma once

#include <string>

/**
 * @brief Data Transfer Object representing a doctor.
 */
struct DoctorDTO {
    int id = -1;              ///< Unique identifier (default -1 for invalid)
    std::string name;         ///< Doctor's name
};
