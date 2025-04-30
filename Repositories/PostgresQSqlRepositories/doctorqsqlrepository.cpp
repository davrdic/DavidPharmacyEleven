#include "doctorqsqlrepository.h"
#include "stringutils.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DoctorQSqlRepository::DoctorQSqlRepository(const QString& dbName, const QString& user, const QString& password) {
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
        qDebug() << "Error updating doctor:" << query.lastError();
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

    QSqlQuery query("SELECT id, name FROM doctor");
    while (query.next()) {
        DoctorDTO doctor;
        doctor.id = query.value(0).toInt();
        doctor.name = StringUtils::toStdString(query.value(1).toString());
        doctors.push_back(doctor);
    }

    return doctors;
}
