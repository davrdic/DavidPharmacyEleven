#pragma once

#include "customerdto.h"
#include <vector>

/**
 * @brief Interface for Customer repository operations.
 */
class ICustomerRepository {
public:
    virtual ~ICustomerRepository() = default;

    /**
     * @brief Add a new customer to the repository.
     * @param customer The customer data to add.
     * @return True if successful, false otherwise.
     */
    virtual bool addCustomer(const CustomerDTO& customer) = 0;

    /**
     * @brief Update an existing customer in the repository.
     * @param customer The updated customer data.
     * @return True if successful, false otherwise.
     */
    virtual bool updateCustomer(const CustomerDTO& customer) = 0;

    /**
     * @brief Delete a customer from the repository.
     * @param customer The customer to delete.
     * @return True if successful, false otherwise.
     */
    virtual bool deleteCustomer(const CustomerDTO& customer) = 0;

    /**
     * @brief Retrieve a list of all customers and their associated doctors.
     * @return A vector of CustomerDTO objects.
     */
    virtual std::vector<CustomerDTO> getAllCustomersData() const = 0;
};
