#include "doctorservice.h"
#include "sortingutils.h"

DoctorService::DoctorService(std::shared_ptr<IDoctorRepository> iDoctorRepository)
    : iDoctorRepository(iDoctorRepository) {}

bool DoctorService::addDoctor(const DoctorDTO& doctor) {
    return iDoctorRepository->addDoctor(doctor);
}

bool DoctorService::editDoctor(const DoctorDTO& doctor) {
    return iDoctorRepository->editDoctor(doctor);
}

bool DoctorService::deleteDoctor(const DoctorDTO& doctor) {
    return iDoctorRepository->deleteDoctor(doctor);
}

std::vector<DoctorDTO> DoctorService::getDoctorList() const {
    std::vector<DoctorDTO> doctorList = iDoctorRepository->getDoctorsList();
    SortingUtils<DoctorDTO>::sortVectorByDTOName(doctorList);
    return doctorList;
}
