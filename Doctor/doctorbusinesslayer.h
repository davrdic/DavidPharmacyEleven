#ifndef DOCTORBUSINESSLAYER_H
#define DOCTORBUSINESSLAYER_H

#include "doctorservice.h"
#include "sortingutils.h"

class DoctorBusinessLayer {
public:
    DoctorBusinessLayer(DoctorService* doctorService);

    bool addDoctor(const DoctorDTO& doctor);
    bool editDoctor(const DoctorDTO& doctor);
    bool deleteDoctor(const DoctorDTO& doctor);
    QList<DoctorDTO> getDoctorList() const;

private:
    DoctorService* m_doctorService;
};

#endif // DOCTORBUSINESSLAYER_H
