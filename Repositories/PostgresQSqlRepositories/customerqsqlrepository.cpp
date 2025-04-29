#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "customerqsqlrepository.h"
#include "stringutils.h"

CustomerQSqlRepository::CustomerQSqlRepository(const QString& dbName, const QString& user, const QString& password) {
    db = QSqlDatabase::addDatabase("QPSQL");  // Use PostgreSQL
    db.setHostName("localhost");
    db.setDatabaseName(dbName);
    db.setUserName(user);
    db.setPassword(password);

    // Attempt to open the database
    if (!db.open()) {
        // If connection fails, print the error
        qDebug() << "Error: Unable to connect to database!";
        qDebug() << "user: " << user;
        qDebug() << "password: " << password;
        qDebug() << "Database error: " << db.lastError().text();  // Show detailed error
    } else {
        qDebug() << "Successfully connected to the database!";
    }
}

bool CustomerQSqlRepository::addCustomer(const CustomerDTO& customer) {
    QSqlQuery query;
    query.prepare("INSERT INTO customer (name) VALUES (:name)");
    query.bindValue(":name", StringUtils::toQString(customer.name));

    if (!query.exec()) {
        qDebug() << "Error adding customer:" << query.lastError();
        return false;
    }
    return true;
}

bool CustomerQSqlRepository::updateCustomer(const CustomerDTO& customer) {
    QSqlQuery query;
    query.prepare("UPDATE customer SET name = :name, doctor_id = :doctor_id WHERE id = :id");
    query.bindValue(":name", StringUtils::toQString(customer.name));
    query.bindValue(":id", customer.id);
    query.bindValue(":doctor_id", customer.doctor_id);

    if (!query.exec()) {
        qDebug() << "Error editing customer:" << query.lastError();
        return false;
    }
    return true;
}

bool CustomerQSqlRepository::deleteCustomer(const CustomerDTO& customer) {
    QSqlQuery query;
    query.prepare("DELETE FROM customer WHERE id = :id");
    query.bindValue(":id", customer.id);

    if (!query.exec()) {
        qDebug() << "Error deleting customer:" << query.lastError();
        return false;
    }
    return true;
}

std::vector<CustomerDTO> CustomerQSqlRepository::getCustomerList() const {
    std::vector<CustomerDTO> customers;

    QSqlQuery query("SELECT id, name, doctor_id FROM customer"); // Fetch both id and name
    while (query.next()) {
        CustomerDTO customer;
        customer.id = query.value(0).toInt();  // The id is stored in the first column
        customer.name = StringUtils::toStdString(query.value(1).toString());  // The name is stored in the second column
        customer.doctor_id = query.value(2).toInt(); // doctor_id

        customers.push_back(customer);  // Add the DTO to the list
    }
    return customers;
}
