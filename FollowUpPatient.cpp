#include "FollowUpPatient.h"

namespace SCAPMS {

FollowUpPatient::FollowUpPatient(const std::string& id,
                                 const std::string& name,
                                 int age,
                                 const std::string& contact)
    : PatientRecord(id, name, age, contact)
{
}

std::string FollowUpPatient::getCategory() const
{
    return "Follow-Up";
}

std::string FollowUpPatient::getDescription() const
{
    return "Patient returning for a follow-up visit";
}

std::string FollowUpPatient::scheduleAppointment()
{
    return "Follow-up appointment scheduled.";
}

std::string FollowUpPatient::cancelAppointment()
{
    return "Follow-up appointment cancelled.";
}

}