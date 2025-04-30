#ifndef DOCTORREPOSITORY_H
#define DOCTORREPOSITORY_H

#include <QString>
#include <QSqlDatabase>
#include <vector>

#include "doctordto.h"
#include "IRepositories/idoctorrepository.h"

/**
 * @brief The DoctorQSqlRepository class provides a concrete implementation of IDoctorRepository
 * using Qt's SQL module with a PostgreSQL backend.
 */
class DoctorQSqlRepository : public IDoctorRepository {
public:
    /**
     * @brief Constructs a DoctorQSqlRepository and initializes the database connection.
     * @param dbName The name of the PostgreSQL database.
     * @param user The username for authentication.
     * @param password The password for authentication.
     */
    DoctorQSqlRepository(const QString& dbName, const QString& user, const QString& password);

    /**
     * @brief Adds a new doctor to the database.
     * @param doctor The doctor data transfer object containing doctor details.
     * @return True if the operation succeeds, false otherwise.
     */
    bool addDoctor(const DoctorDTO& doctor) override;

    /**
     * @brief Updates an existing doctor's information in the database.
     * @param doctor The doctor data transfer object with updated details.
     * @return True if the update is successful, false otherwise.
     */
    bool updateDoctor(const DoctorDTO& doctor) override;

    /**
     * @brief Deletes a doctor from the database.
     * @param doctor The doctor data transfer object identifying the doctor to delete.
     * @return True if the deletion is successful, false otherwise.
     */
    bool deleteDoctor(const DoctorDTO& doctor) override;

    /**
     * @brief Retrieves a list of all doctors from the database.
     * @return A vector of DoctorDTO objects representing the doctors.
     */
    std::vector<DoctorDTO> getDoctorList() const override;

private:
    QSqlDatabase db;  ///< The Qt SQL database connection.
};

#endif // DOCTORREPOSITORY_H
