#ifndef CUSTOMERQSQLREPOSITORY_H
#define CUSTOMERQSQLREPOSITORY_H

#include <QString>
#include <QSqlDatabase>
#include "customerdto.h"
#include "IRepositories/icustomerrepository.h"
#include <vector>

class CustomerQSqlRepository : public ICustomerRepository {
public:
    CustomerQSqlRepository(const QString& dbName, const QString& user, const QString& password);

    bool addCustomer(const CustomerDTO& customer);
    bool updateCustomer(const CustomerDTO& customer);
    bool deleteCustomer(const CustomerDTO& customer);
    std::vector<CustomerDTO> getCustomerList() const;

private:
    QSqlDatabase db;
};

#endif // CUSTOMERQSQLREPOSITORY_H
