#ifndef DOCTORSERVICE_H
#define DOCTORSERVICE_H

#include "doctorrepository.h"
#include "sortingutils.h"

class DoctorService {
public:
    DoctorService(DoctorRepository* doctorService);

    bool addDoctor(const DoctorDTO& doctor);
    bool editDoctor(const DoctorDTO& doctor);
    bool deleteDoctor(const DoctorDTO& doctor);
    QList<DoctorDTO> getDoctorList() const;

private:
    DoctorRepository* m_doctorService;
};

#endif
