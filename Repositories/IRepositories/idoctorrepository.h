#ifndef IDOCTORREPOSITORY_H
#define IDOCTORREPOSITORY_H

#include "doctordto.h"
#include <vector>

class IDoctorRepository {
public:
    virtual ~IDoctorRepository() = default;
    virtual bool addDoctor(const DoctorDTO& doctor) = 0;
    virtual bool updateDoctor(const DoctorDTO& doctor) = 0;
    virtual bool deleteDoctor(const DoctorDTO& doctor) = 0;
    virtual std::vector<DoctorDTO> getDoctorList() const = 0;
};

#endif // IDOCTORREPOSITORY_H
