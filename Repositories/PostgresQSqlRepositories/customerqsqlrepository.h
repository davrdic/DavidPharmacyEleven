#ifndef CUSTOMERQSQLREPOSITORY_H
#define CUSTOMERQSQLREPOSITORY_H

#include <QString>
#include <QSqlDatabase>
#include <vector>

#include "customerdto.h"
#include "IRepositories/icustomerrepository.h"

/**
 * @brief The CustomerQSqlRepository class implements ICustomerRepository using Qt's PostgreSQL driver.
 */
class CustomerQSqlRepository : public ICustomerRepository {
public:
    /**
     * @brief Constructs a CustomerQSqlRepository with the given database credentials.
     * @param dbName The name of the PostgreSQL database.
     * @param user The username for the database connection.
     * @param password The password for the database connection.
     */
    CustomerQSqlRepository(const QString& dbName, const QString& user, const QString& password);

    /**
     * @brief Adds a new customer to the database.
     * @param customer The customer DTO containing name and associated doctor.
     * @return True if the insertion is successful; false otherwise.
     */
    bool addCustomer(const CustomerDTO& customer) override;

    /**
     * @brief Updates an existing customer's data.
     * @param customer The updated customer DTO.
     * @return True if the update is successful; false otherwise.
     */
    bool updateCustomer(const CustomerDTO& customer) override;

    /**
     * @brief Deletes a customer from the database.
     * @param customer The customer DTO identifying the customer by ID.
     * @return True if the deletion is successful; false otherwise.
     */
    bool deleteCustomer(const CustomerDTO& customer) override;

    /**
     * @brief Retrieves all customers and their associated doctor data.
     * @return A vector of CustomerDTO containing customer and related doctor info.
     */
    std::vector<CustomerDTO> getAllCustomersData() const override;

private:
    QSqlDatabase db;  ///< The database connection instance.
};

#endif // CUSTOMERQSQLREPOSITORY_H
