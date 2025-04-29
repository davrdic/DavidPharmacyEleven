#ifndef DOCTORSERVICE_H
#define DOCTORSERVICE_H

#include <memory>

#include "IRepositories/idoctorrepository.h"
#include "doctordto.h"
#include <vector>

class DoctorService {
public:
    // Constructor, accept shared pointer to repository
    DoctorService(std::shared_ptr<IDoctorRepository> iDoctorRepository);
    bool addDoctor(const DoctorDTO& doctor);
    bool editDoctor(const DoctorDTO& doctor);
    bool deleteDoctor(const DoctorDTO& doctor);
    std::vector<DoctorDTO> getDoctorList() const;

private:
    // Store a shared pointer to the repository interface
    std::shared_ptr<IDoctorRepository> iDoctorRepository;
};

#endif
