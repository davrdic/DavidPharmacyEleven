#include "doctorservice.h"
#include "sortingutils.h"

DoctorService::DoctorService(std::shared_ptr<IDoctorRepository> iDoctorRepository)
    : iDoctorRepository(std::move(iDoctorRepository)) {}

bool DoctorService::addDoctor(const DoctorDTO& doctor) {
    return iDoctorRepository->addDoctor(doctor);
}

bool DoctorService::updateDoctor(const DoctorDTO& doctor) {
    return iDoctorRepository->updateDoctor(doctor);
}

bool DoctorService::deleteDoctor(const DoctorDTO& doctor) {
    return iDoctorRepository->deleteDoctor(doctor);
}

std::vector<DoctorDTO> DoctorService::getDoctorList() const {
    std::vector<DoctorDTO> doctorList = iDoctorRepository->getDoctorList();
    SortingUtils<DoctorDTO>::sortVectorByDTOName(doctorList);
    return doctorList;
}
