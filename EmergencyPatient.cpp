#include "EmergencyPatient.h"

namespace SCAPMS {

EmergencyPatient::EmergencyPatient(const std::string& id,
                                   const std::string& name,
                                   int age,
                                   const std::string& contact)
    : PatientRecord(id, name, age, contact)
{
}

std::string EmergencyPatient::getCategory() const
{
    return "Emergency";
}

std::string EmergencyPatient::getDescription() const
{
    return "Emergency clinic patient";
}

std::string EmergencyPatient::scheduleAppointment()
{
    return "Emergency patient appointment scheduled.";
}

std::string EmergencyPatient::cancelAppointment()
{
    return "Emergency patient appointment cancelled.";
}

}