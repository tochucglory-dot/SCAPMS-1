#include "GeneralPatient.h"

namespace SCAPMS {

GeneralPatient::GeneralPatient(const std::string& id,
                               const std::string& name,
                               int age,
                               const std::string& contact)
    : PatientRecord(id, name, age, contact)
{
}

std::string GeneralPatient::getCategory() const
{
    return "General";
}

std::string GeneralPatient::getDescription() const
{
    return "General clinic patient";
}

std::string GeneralPatient::scheduleAppointment()
{
    return "General patient appointment scheduled.";
}

std::string GeneralPatient::cancelAppointment()
{
    return "General patient appointment cancelled.";
}

}