#ifndef DOCTORREPOSITORY_H
#define DOCTORREPOSITORY_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "doctordto.h"
#include "IRepositories/idoctorrepository.h"
#include <vector>

class DoctorRepository : public IDoctorRepository {
public:
    DoctorRepository(const QString& dbName, const QString& user, const QString& password);

    bool addDoctor(const DoctorDTO& doctor);
    bool editDoctor(const DoctorDTO& doctor);
    bool deleteDoctor(const DoctorDTO& doctor);
    std::vector<DoctorDTO> getDoctorsList() const;

private:
    QSqlDatabase db;
};

#endif
