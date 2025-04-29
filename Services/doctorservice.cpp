#include "doctorservice.h"

DoctorService::DoctorService(DoctorRepository* doctorService)
    : m_doctorService(doctorService) {}

bool DoctorService::addDoctor(const DoctorDTO& doctor) {
    return m_doctorService->addDoctor(doctor);
}

bool DoctorService::editDoctor(const DoctorDTO& doctor) {
    return m_doctorService->editDoctor(doctor);
}

bool DoctorService::deleteDoctor(const DoctorDTO& doctor) {
    return m_doctorService->deleteDoctor(doctor);
}

QList<DoctorDTO> DoctorService::getDoctorList() const {
    QList<DoctorDTO> doctorList = m_doctorService->getDoctorsList();
    SortingUtils<DoctorDTO>::sortList(doctorList);
    return doctorList;
}
