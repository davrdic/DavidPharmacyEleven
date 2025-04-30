#ifndef DOCTORSERVICE_H
#define DOCTORSERVICE_H

#include <memory>
#include <vector>
#include "IRepositories/idoctorrepository.h"
#include "doctordto.h"

/**
 * @brief The DoctorService class provides business logic operations for managing doctors.
 * It acts as an intermediary between the UI and the data repository.
 */
class DoctorService {
public:
    /**
     * @brief Constructs a DoctorService with a given doctor repository.
     * @param iDoctorRepository A shared pointer to an implementation of IDoctorRepository.
     */
    explicit DoctorService(std::shared_ptr<IDoctorRepository> iDoctorRepository);

    /**
     * @brief Adds a new doctor to the system.
     * @param doctor The DoctorDTO object containing the doctor's data.
     * @return True if the operation was successful, false otherwise.
     */
    bool addDoctor(const DoctorDTO& doctor);

    /**
     * @brief Updates an existing doctor's information.
     * @param doctor The DoctorDTO object with updated data.
     * @return True if the update was successful, false otherwise.
     */
    bool updateDoctor(const DoctorDTO& doctor);

    /**
     * @brief Deletes a doctor from the system.
     * @param doctor The DoctorDTO object representing the doctor to delete.
     * @return True if the deletion was successful, false otherwise.
     */
    bool deleteDoctor(const DoctorDTO& doctor);

    /**
     * @brief Retrieves a list of all doctors, sorted alphabetically by name.
     * @return A sorted vector of DoctorDTO objects.
     */
    std::vector<DoctorDTO> getDoctorList() const;

private:
    std::shared_ptr<IDoctorRepository> iDoctorRepository; ///< Interface for doctor-related database operations.
};

#endif // DOCTORSERVICE_H
