#include "PatientRecord.h"
#include <stdexcept>

namespace SCAPMS {

PatientRecord::PatientRecord(const std::string& id,
                             const std::string& patientName,
                             int patientAge,
                             const std::string& patientContact)
    : patientID(id),
    name(patientName),
    age(patientAge),
    contact(patientContact)
{
    if (patientID.empty())
        throw std::invalid_argument("Patient ID cannot be empty.");

    if (name.empty())
        throw std::invalid_argument("Patient name cannot be empty.");

    if (age < 0 || age > 120)
        throw std::invalid_argument("Invalid patient age.");

    if (contact.empty())
        throw std::invalid_argument("Contact cannot be empty.");
}

std::string PatientRecord::getPatientID() const
{
    return patientID;
}

std::string PatientRecord::getName() const
{
    return name;
}

int PatientRecord::getAge() const
{
    return age;
}

std::string PatientRecord::getContact() const
{
    return contact;
}

void PatientRecord::setName(const std::string& newName)
{
    if (newName.empty())
        throw std::invalid_argument("Name cannot be empty.");

    name = newName;
}

void PatientRecord::setAge(int newAge)
{
    if (newAge < 0 || newAge > 120)
        throw std::invalid_argument("Invalid patient age.");

    age = newAge;
}

void PatientRecord::setContact(const std::string& newContact)
{
    if (newContact.empty())
        throw std::invalid_argument("Contact cannot be empty.");

    contact = newContact;
}

}