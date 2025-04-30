#pragma once

#include "doctordto.h"
#include <vector>

/**
 * @brief Interface for Doctor repository operations.
 */
class IDoctorRepository {
public:
    virtual ~IDoctorRepository() = default;

    /**
     * @brief Add a new doctor to the repository.
     * @param doctor The doctor data to add.
     * @return True if successful, false otherwise.
     */
    virtual bool addDoctor(const DoctorDTO& doctor) = 0;

    /**
     * @brief Update an existing doctor in the repository.
     * @param doctor The updated doctor data.
     * @return True if successful, false otherwise.
     */
    virtual bool updateDoctor(const DoctorDTO& doctor) = 0;

    /**
     * @brief Delete a doctor from the repository.
     * @param doctor The doctor to delete.
     * @return True if successful, false otherwise.
     */
    virtual bool deleteDoctor(const DoctorDTO& doctor) = 0;

    /**
     * @brief Retrieve a list of all doctors.
     * @return A vector of DoctorDTO objects.
     */
    virtual std::vector<DoctorDTO> getDoctorList() const = 0;
};
