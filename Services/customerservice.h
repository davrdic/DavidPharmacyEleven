#ifndef CUSTOMERSERVICE_H
#define CUSTOMERSERVICE_H

#include <memory>
#include <vector>

#include "IRepositories/icustomerrepository.h"
#include "customerdto.h"

/**
 * @brief The CustomerService class handles business logic for managing customer data.
 * It serves as a layer between the UI/application logic and the data repository.
 */
class CustomerService {
public:
    /**
     * @brief Constructs a CustomerService with a given customer repository.
     * @param iCustomerRepository A shared pointer to an implementation of ICustomerRepository.
     */
    explicit CustomerService(std::shared_ptr<ICustomerRepository> iCustomerRepository);

    /**
     * @brief Adds a new customer to the system.
     * @param customer The CustomerDTO containing customer information.
     * @return True if the customer was successfully added, false otherwise.
     */
    bool addCustomer(const CustomerDTO& customer);

    /**
     * @brief Updates an existing customer's information.
     * @param customer The CustomerDTO with updated customer data.
     * @return True if the update was successful, false otherwise.
     */
    bool updateCustomer(const CustomerDTO& customer);

    /**
     * @brief Deletes a customer from the system.
     * @param customer The CustomerDTO representing the customer to delete.
     * @return True if the deletion was successful, false otherwise.
     */
    bool deleteCustomer(const CustomerDTO& customer);

    /**
     * @brief Retrieves all customer records from the system, sorted by name.
     * @return A sorted vector of CustomerDTO objects.
     */
    std::vector<CustomerDTO> getAllCustomersData() const;

private:
    std::shared_ptr<ICustomerRepository> iCustomerRepository; ///< Interface for customer-related database operations.
};

#endif // CUSTOMERSERVICE_H
