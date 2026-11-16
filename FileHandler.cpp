#include "FileHandler.h"
#include "../model/GeneralPatient.h"
#include "../model/EmergencyPatient.h"
#include "../model/FollowUpPatient.h"

#include <fstream>
#include <stdexcept>

namespace SCAPMS {

bool FileHandler::savePatients(
    const ClinicDatabase& database,
    const std::string& filename)
{
    std::ofstream file(filename);

    if (!file.is_open())
        throw std::runtime_error("Unable to save patient records.");

    for (const auto& patient : database.getPatients())
    {
        file << patient->getCategory() << "|"
             << patient->getPatientID() << "|"
             << patient->getName() << "|"
             << patient->getAge() << "|"
             << patient->getContact() << "\n";
    }

    return true;
}

bool FileHandler::saveAppointments(
    const ClinicDatabase& database,
    const std::string& filename)
{
    std::ofstream file(filename);

    if (!file.is_open())
        throw std::runtime_error("Unable to save appointments.");

    for (const auto& appointment : database.getAppointments())
    {
        file << appointment.getAppointmentID() << "|"
             << appointment.getPatientID() << "|"
             << appointment.getAppointmentDate() << "|"
             << appointment.getAppointmentTime() << "|"
             << appointment.getReason() << "|"
             << appointment.getStatus() << "\n";
    }

    return true;
}

bool FileHandler::loadPatients(
    ClinicDatabase& database,
    const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
        throw std::runtime_error("Unable to load patient records.");

    std::string category, id, name, contact;
    int age;

    while (std::getline(file, category, '|'))
    {
        std::getline(file, id, '|');
        std::getline(file, name, '|');
        file >> age;
        file.ignore(1);
        std::getline(file, contact);

        if (category == "General")
        {
            database.addPatient(
                std::make_unique<GeneralPatient>(
                    id, name, age, contact));
        }
        else if (category == "Emergency")
        {
            database.addPatient(
                std::make_unique<EmergencyPatient>(
                    id, name, age, contact));
        }
        else if (category == "Follow-Up")
        {
            database.addPatient(
                std::make_unique<FollowUpPatient>(
                    id, name, age, contact));
        }
        else
        {
            throw std::runtime_error("Unknown patient category.");
        }
    }

    return true;
}

}