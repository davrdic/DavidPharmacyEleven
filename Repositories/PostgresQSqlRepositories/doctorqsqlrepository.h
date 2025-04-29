#ifndef DOCTORREPOSITORY_H
#define DOCTORREPOSITORY_H

#include <QString>
#include <QSqlDatabase>
#include "doctordto.h"
#include "IRepositories/idoctorrepository.h"
#include <vector>

class DoctorQSqlRepository : public IDoctorRepository {
public:
    DoctorQSqlRepository(const QString& dbName, const QString& user, const QString& password);

    bool addDoctor(const DoctorDTO& doctor);
    bool updateDoctor(const DoctorDTO& doctor);
    bool deleteDoctor(const DoctorDTO& doctor);
    std::vector<DoctorDTO> getDoctorList() const;

private:
    QSqlDatabase db;
};

#endif
