#include "customerservice.h"
#include "sortingutils.h"

CustomerService::CustomerService(std::shared_ptr<ICustomerRepository> iCustomerRepository)
    : iCustomerRepository(std::move(iCustomerRepository)) {}

bool CustomerService::addCustomer(const CustomerDTO& customer) {
    return iCustomerRepository->addCustomer(customer);
}

bool CustomerService::updateCustomer(const CustomerDTO& customer) {
    return iCustomerRepository->updateCustomer(customer);
}

bool CustomerService::deleteCustomer(const CustomerDTO& customer) {
    return iCustomerRepository->deleteCustomer(customer);
}

std::vector<CustomerDTO> CustomerService::getAllCustomersData() const {
    std::vector<CustomerDTO> customerList = iCustomerRepository->getAllCustomersData();
    SortingUtils<CustomerDTO>::sortBy(customerList, [](const CustomerDTO& customer){return customer.name.empty() ? std::string("~") : customer.name; });
    return customerList;
}
