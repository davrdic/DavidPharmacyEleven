#ifndef DOCTORBUSINESSLAYER_H
#define DOCTORBUSINESSLAYER_H

#include "doctorservice.h"

class DoctorBusinessLayer {
public:
    DoctorBusinessLayer(DoctorService* doctorService);

    bool addDoctor(const DoctorDTO& doctor);
    bool editDoctor(const DoctorDTO& doctor);
    QList<DoctorDTO> getDoctors() const;

private:
    DoctorService* m_doctorService;
};

#endif // DOCTORBUSINESSLAYER_H
