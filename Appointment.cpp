#include "Appointment.h"
#include <stdexcept>

namespace SCAPMS {

Appointment::Appointment(const std::string& id,
                         const std::string& patientId,
                         const std::string& date,
                         const std::string& time,
                         const std::string& appointmentReason)
    : appointmentID(id),
    patientID(patientId),
    appointmentDate(date),
    appointmentTime(time),
    reason(appointmentReason),
    status("Pending")
{
    if (appointmentID.empty())
        throw std::invalid_argument("Appointment ID cannot be empty.");

    if (patientID.empty())
        throw std::invalid_argument("Patient ID cannot be empty.");

    if (appointmentDate.empty())
        throw std::invalid_argument("Appointment date cannot be empty.");

    if (appointmentTime.empty())
        throw std::invalid_argument("Appointment time cannot be empty.");

    if (reason.empty())
        throw std::invalid_argument("Appointment reason cannot be empty.");
}

std::string Appointment::getAppointmentID() const
{
    return appointmentID;
}

std::string Appointment::getPatientID() const
{
    return patientID;
}

std::string Appointment::getAppointmentDate() const
{
    return appointmentDate;
}

std::string Appointment::getAppointmentTime() const
{
    return appointmentTime;
}

std::string Appointment::getReason() const
{
    return reason;
}

std::string Appointment::getStatus() const
{
    return status;
}

void Appointment::setStatus(const std::string& newStatus)
{
    if (newStatus != "Pending" &&
        newStatus != "Scheduled" &&
        newStatus != "Cancelled" &&
        newStatus != "Completed")
    {
        throw std::invalid_argument("Invalid appointment status.");
    }

    status = newStatus;
}

}