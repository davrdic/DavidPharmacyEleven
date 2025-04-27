#include "doctorservice.h"

DoctorService::DoctorService(const QString& dbName, const QString& user, const QString& password) {
    db = QSqlDatabase::addDatabase("QPSQL");  // Use PostgreSQL
    db.setHostName("localhost");
    db.setDatabaseName(dbName);
    db.setUserName(user);
    db.setPassword(password);

    if (!db.open()) {
        qDebug() << "Error: Unable to connect to database!";
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
