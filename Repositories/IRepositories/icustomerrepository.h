#ifndef ICUSTOMERREPOSITORY_H
#define ICUSTOMERREPOSITORY_H

#include "customerdto.h"
#include <vector>

class ICustomerRepository {
public:
    virtual ~ICustomerRepository() = default;
    virtual bool addCustomer(const CustomerDTO& customer) = 0;
    virtual bool updateCustomer(const CustomerDTO& customer) = 0;
    virtual bool deleteCustomer(const CustomerDTO& customer) = 0;
    virtual std::vector<CustomerDTO> getCustomerList() const = 0;
};

#endif // ICUSTOMERREPOSITORY_H
