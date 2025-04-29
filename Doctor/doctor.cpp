#include "doctor.h"

Doctor::Doctor(const std::string& name) : name(name) {}

std::string Doctor::getName() const {
    return name;
}

void Doctor::setName(const std::string& name) {
    this->name = name;
}
