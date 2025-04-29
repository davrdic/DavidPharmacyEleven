#ifndef DOCTORREPOSITORY_H
#define DOCTORREPOSITORY_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "doctordto.h"

class DoctorRepository {
public:
    DoctorRepository(const QString& dbName, const QString& user, const QString& password);

    bool addDoctor(const DoctorDTO& doctor);
    bool editDoctor(const DoctorDTO& doctor);
    bool deleteDoctor(const DoctorDTO& doctor);
    QList<DoctorDTO>getDoctorsList() const;

private:
    QSqlDatabase db;
};

#endif
