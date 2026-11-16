#ifndef CLINICMANAGER_H
#define CLINICMANAGER_H

#include "ClinicDatabase.h"
#include "SearchEngine.h"
#include "SortEngine.h"

namespace SCAPMS {

class ClinicManager
{
private:
    ClinicDatabase database;

public:
    ClinicDatabase& getDatabase();

    bool registerPatient(std::unique_ptr<PatientRecord> patient);
    bool deletePatient(const std::string& patientID);

    PatientRecord* searchPatientByID(const std::string& patientID);
    PatientRecord* binarySearchPatientByID(const std::string& patientID);
    PatientRecord* searchPatientByName(const std::string& name);

    bool scheduleAppointment(const Appointment& appointment);
    bool cancelAppointment(const std::string& appointmentID);

    void addPatientToQueue(const std::string& patientID);

    void sortPatientsByName();
    void sortPatientsByID();
    void sortPatientsByAge();
};

}

#endif