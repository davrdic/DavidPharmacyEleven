#include "doctorbusinesslayer.h"

DoctorBusinessLayer::DoctorBusinessLayer(DoctorService* doctorService)
    : m_doctorService(doctorService) {}

bool DoctorBusinessLayer::addDoctor(const DoctorDTO& doctor) {
    // You can add additional validation or business logic here if needed
    return m_doctorService->addDoctor(doctor);
}

bool DoctorBusinessLayer::editDoctor(const DoctorDTO& doctor) {
    // Add validation or business rules if needed
    return m_doctorService->editDoctor(doctor);
}

QList<DoctorDTO> DoctorBusinessLayer::getDoctors() const {
    return m_doctorService->getDoctorsList();
}
