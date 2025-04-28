#include "doctorbusinesslayer.h"

DoctorBusinessLayer::DoctorBusinessLayer(DoctorService* doctorService)
    : m_doctorService(doctorService) {}

bool DoctorBusinessLayer::addDoctor(const DoctorDTO& doctor) {
    return m_doctorService->addDoctor(doctor);
}

bool DoctorBusinessLayer::editDoctor(const DoctorDTO& doctor) {
    return m_doctorService->editDoctor(doctor);
}

bool DoctorBusinessLayer::deleteDoctor(const DoctorDTO& doctor) {
    return m_doctorService->deleteDoctor(doctor);
}

QList<DoctorDTO> DoctorBusinessLayer::getDoctorList() const {
    QList<DoctorDTO> doctorList = m_doctorService->getDoctorsList();
    SortingUtils<DoctorDTO>::sortList(doctorList);
    return doctorList;
}
