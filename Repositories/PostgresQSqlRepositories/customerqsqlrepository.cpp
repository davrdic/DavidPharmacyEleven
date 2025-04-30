#include "customerqsqlrepository.h"
#include "stringutils.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

CustomerQSqlRepository::CustomerQSqlRepository(const QString& dbName, const QString& user, const QString& password) {
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName(dbName);
    db.setUserName(user);
    db.setPassword(password);

    if (!db.open()) {
        qDebug() << "Error: Unable to connect to database!";
        qDebug() << "user:" << user;
        qDebug() << "password:" << password;
        qDebug() << "Database error:" << db.lastError().text();
    } else {
        qDebug() << "Successfully connected to the database!";
    }
}

bool CustomerQSqlRepository::addCustomer(const CustomerDTO& customer) {
    QSqlQuery query;
    query.prepare("INSERT INTO customer (name, doctor_id) VALUES (:name, :doctor_id)");
    query.bindValue(":name", StringUtils::toQString(customer.name));
    query.bindValue(":doctor_id", customer.doctor.id);

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
    query.bindValue(":doctor_id", customer.doctor.id);
    query.bindValue(":id", customer.id);

    if (!query.exec()) {
        qDebug() << "Error updating customer:" << query.lastError();
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

std::vector<CustomerDTO> CustomerQSqlRepository::getAllCustomersData() const {
    std::vector<CustomerDTO> customers;

    QSqlQuery query(R"(
        SELECT customer.id, customer.name, customer.doctor_id, doctor.name AS doctor_name
        FROM customer
        LEFT JOIN doctor ON customer.doctor_id = doctor.id
    )");

    while (query.next()) {
        CustomerDTO customer;
        customer.id = query.value("id").toInt();
        customer.name = StringUtils::toStdString(query.value("name").toString());
        customer.doctor.id = query.value("doctor_id").toInt();
        customer.doctor.name = StringUtils::toStdString(query.value("doctor_name").toString());

        customers.push_back(customer);
    }

    return customers;
}
