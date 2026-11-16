#ifndef CLINICDATABASE_H
#define CLINICDATABASE_H

#include <vector>
#include <queue>
#include <stack>
#include <array>
#include <memory>
#include <string>

#include "../model/PatientRecord.h"
#include "../model/Appointment.h"

namespace SCAPMS {

class ClinicDatabase
{
private:
    // Stores all registered patients
    std::vector<std::unique_ptr<PatientRecord>> patients;

    // Stores all appointments
    std::vector<Appointment> appointments;

    // Stores patients waiting for attention
    std::queue<std::string> waitingQueue;

    // Stores previous administrative operations for undo
    std::stack<std::string> undoStack;

    // Stores previous patient details before editing
    struct PatientSnapshot
    {
        std::string patientID;
        std::string name;
        int age;
        std::string contact;
    };

    std::stack<PatientSnapshot> editedPatients;

    std::stack<std::unique_ptr<PatientRecord>> deletedPatients;

    // Cache for 10 frequently accessed patients
    std::array<PatientRecord*, 10> patientCache{};

public:
    ClinicDatabase();

    bool addPatient(std::unique_ptr<PatientRecord> patient);
    bool deletePatient(const std::string& patientID);

    PatientRecord* findPatientByID(const std::string& patientID);
    const std::vector<std::unique_ptr<PatientRecord>>& getPatients() const;
    std::vector<std::unique_ptr<PatientRecord>>& getPatients();

    bool addAppointment(const Appointment& appointment);
    bool cancelAppointment(const std::string& appointmentID);

    const std::vector<Appointment>& getAppointments() const;

    void addToWaitingQueue(const std::string& patientID);
    std::string getNextWaitingPatient();
    int getWaitingCount() const;
    std::vector<std::string> getWaitingPatients() const;

    void recordUndoOperation(const std::string& operation);
    void recordPatientEdit(const PatientRecord& patient);
    bool undoLastOperation();

    void updatePatientCache(PatientRecord* patient);
};

}

#endif