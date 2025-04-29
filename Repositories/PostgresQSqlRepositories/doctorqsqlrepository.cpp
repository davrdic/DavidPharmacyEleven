#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "doctorqsqlrepository.h"
#include "stringutils.h"

DoctorQSqlRepository::DoctorQSqlRepository(const QString& dbName, const QString& user, const QString& password) {
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

bool DoctorQSqlRepository::addDoctor(const DoctorDTO& doctor) {
    QSqlQuery query;
    query.prepare("INSERT INTO doctor (name) VALUES (:name)");
    query.bindValue(":name", StringUtils::toQString(doctor.name));

    if (!query.exec()) {
        qDebug() << "Error adding doctor:" << query.lastError();
        return false;
    }
    return true;
}

bool DoctorQSqlRepository::updateDoctor(const DoctorDTO& doctor) {
    QSqlQuery query;
    query.prepare("UPDATE doctor SET name = :name WHERE id = :id");
    query.bindValue(":name", StringUtils::toQString(doctor.name));
    query.bindValue(":id", doctor.id);

    if (!query.exec()) {
        qDebug() << "Error editing doctor:" << query.lastError();
        return false;
    }
    return true;
}

bool DoctorQSqlRepository::deleteDoctor(const DoctorDTO& doctor) {
    QSqlQuery query;
    query.prepare("DELETE FROM doctor WHERE id = :id");
    query.bindValue(":id", doctor.id);

    if (!query.exec()) {
        qDebug() << "Error deleting doctor:" << query.lastError();
        return false;
    }
    return true;
}

std::vector<DoctorDTO> DoctorQSqlRepository::getDoctorList() const {
    std::vector<DoctorDTO> doctors;

    QSqlQuery query("SELECT id, name FROM doctor"); // Fetch both id and name
    while (query.next()) {
        DoctorDTO doctor;
        doctor.id = query.value(0).toInt();  // The id is stored in the first column
        doctor.name = StringUtils::toStdString(query.value(1).toString());  // The name is stored in the second column

        doctors.push_back(doctor);  // Add the DTO to the list
    }
    return doctors;
}
