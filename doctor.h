#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>

class Doctor {
public:
    Doctor(const std::string& name);
    std::string getName() const;
    void setName(const std::string& name);

private:
    std::string name;
};

#endif // DOCTOR_H
