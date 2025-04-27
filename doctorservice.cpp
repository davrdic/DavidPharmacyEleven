#include "doctorservice.h"

DoctorService::DoctorService(const QString& dbName, const QString& user, const QString& password) {
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

bool DoctorService::addDoctor(const QString& doctorName) {
    QSqlQuery query;
    query.prepare("INSERT INTO doctor (name) VALUES (:name)");
    query.bindValue(":name", doctorName);

    if (!query.exec()) {
        qDebug() << "Error adding doctor:" << query.lastError();
        return false;
    }
    return true;
}

bool DoctorService::editDoctor(const QString& oldName, const QString& newName) {
    QSqlQuery query;
    query.prepare("UPDATE doctor SET name = :newName WHERE name = :oldName");
    query.bindValue(":newName", newName);
    query.bindValue(":oldName", oldName);

    if (!query.exec()) {
        qDebug() << "Error updating doctor:" << query.lastError();
        return false;
    }
    return true;
}

bool DoctorService::deleteDoctor(const QString& doctorName) {
    QSqlQuery query;
    query.prepare("DELETE FROM doctor WHERE name = :name");
    query.bindValue(":name", doctorName);

    if (!query.exec()) {
        qDebug() << "Error deleting doctor:" << query.lastError();
        return false;
    }
    return true;
}

QList<QString> DoctorService::getDoctorsList() const {
    QList<QString> doctors;

    QSqlQuery query("SELECT name FROM doctor");
    while (query.next()) {
        doctors.append(query.value(0).toString());
    }
    return doctors;
}
