#ifndef EMERGENCYPATIENT_H
#define EMERGENCYPATIENT_H

#include "PatientRecord.h"
#include "Appointable.h"

namespace SCAPMS {

class EmergencyPatient : public PatientRecord, public Appointable
{
public:
    EmergencyPatient(const std::string& id,
                     const std::string& name,
                     int age,
                     const std::string& contact);

    std::string getCategory() const override;
    std::string getDescription() const override;

    std::string scheduleAppointment() override;
    std::string cancelAppointment() override;
};

}

#endif
