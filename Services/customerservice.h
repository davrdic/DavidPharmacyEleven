#ifndef CUSTOMERSERVICE_H
#define CUSTOMERSERVICE_H

#include <memory>

#include "IRepositories/icustomerrepository.h"
#include "customerdto.h"
#include <vector>

class CustomerService {
public:
    // Constructor, accept shared pointer to repository
    CustomerService(std::shared_ptr<ICustomerRepository> iCustomerRepository);
    bool addCustomer(const CustomerDTO& customer);
    bool updateCustomer(const CustomerDTO& customer);
    bool deleteCustomer(const CustomerDTO& customer);
    std::vector<CustomerDTO> getAllCustomersData() const;

private:
    // Store a shared pointer to the repository interface
    std::shared_ptr<ICustomerRepository> iCustomerRepository;
};

#endif
