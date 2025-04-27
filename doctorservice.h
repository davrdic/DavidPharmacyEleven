#ifndef DOCTORSERVICE_H
#define DOCTORSERVICE_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class DoctorService {
public:
    DoctorService(const QString& dbName, const QString& user, const QString& password);

    bool addDoctor(const QString& doctorName);
    bool editDoctor(const QString& oldName, const QString& newName);
    bool deleteDoctor(const QString& doctorName);
    QList<QString> getDoctorsList() const;

private:
    QSqlDatabase db;
};

#endif // DOCTORSERVICE_H
