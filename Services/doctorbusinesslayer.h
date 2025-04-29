#ifndef DOCTORBUSINESSLAYER_H
#define DOCTORBUSINESSLAYER_H

#include "doctorrepository.h"
#include "sortingutils.h"

class DoctorBusinessLayer {
public:
    DoctorBusinessLayer(DoctorRepository* doctorService);

    bool addDoctor(const DoctorDTO& doctor);
    bool editDoctor(const DoctorDTO& doctor);
    bool deleteDoctor(const DoctorDTO& doctor);
    QList<DoctorDTO> getDoctorList() const;

private:
    DoctorRepository* m_doctorService;
};

#endif // DOCTORBUSINESSLAYER_H
