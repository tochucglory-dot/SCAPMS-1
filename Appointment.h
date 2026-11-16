#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>

namespace SCAPMS {

class Appointment
{
private:
    std::string appointmentID;
    std::string patientID;
    std::string appointmentDate;
    std::string appointmentTime;
    std::string reason;
    std::string status;

public:
    Appointment(const std::string& id,
                const std::string& patientId,
                const std::string& date,
                const std::string& time,
                const std::string& appointmentReason);

    std::string getAppointmentID() const;
    std::string getPatientID() const;
    std::string getAppointmentDate() const;
    std::string getAppointmentTime() const;
    std::string getReason() const;
    std::string getStatus() const;

    void setStatus(const std::string& newStatus);
};

}

#endif
