#include "ClinicDatabase.h"
#include <algorithm>
#include <stdexcept>

namespace SCAPMS {

ClinicDatabase::ClinicDatabase()
{
    patientCache.fill(nullptr);
}

bool ClinicDatabase::addPatient(std::unique_ptr<PatientRecord> patient)
{
    if (!patient)
        throw std::invalid_argument("Invalid patient record.");

    if (findPatientByID(patient->getPatientID()) != nullptr)
        throw std::invalid_argument("Duplicate patient ID.");

    std::string id = patient->getPatientID();

    patients.push_back(std::move(patient));

    recordUndoOperation("ADD:" + id);

    return true;
}

bool ClinicDatabase::deletePatient(const std::string& patientID)
{
    auto it = std::find_if(
        patients.begin(),
        patients.end(),
        [&patientID](const std::unique_ptr<PatientRecord>& patient)
        {
            return patient->getPatientID() == patientID;
        });

    if (it == patients.end())
        return false;

    deletedPatients.push(std::move(*it));
    patients.erase(it);

    recordUndoOperation("DELETE:" + patientID);

    return true;
}

PatientRecord* ClinicDatabase::findPatientByID(const std::string& patientID)
{
    for (const auto& patient : patients)
    {
        if (patient->getPatientID() == patientID)
        {
            updatePatientCache(patient.get());
            return patient.get();
        }
    }

    return nullptr;
}

const std::vector<std::unique_ptr<PatientRecord>>&
ClinicDatabase::getPatients() const
{
    return patients;
}
std::vector<std::unique_ptr<PatientRecord>>&
ClinicDatabase::getPatients()
{
    return patients;
}

bool ClinicDatabase::addAppointment(const Appointment& appointment)
{
    if (findPatientByID(appointment.getPatientID()) == nullptr)
        throw std::invalid_argument("Patient does not exist.");

    for (const auto& existing : appointments)
    {
        if (existing.getAppointmentID() == appointment.getAppointmentID())
            throw std::invalid_argument("Duplicate appointment ID.");
    }

    appointments.push_back(appointment);

    recordUndoOperation("ADD_APPOINTMENT:" +
                        appointment.getAppointmentID());

    return true;
}

bool ClinicDatabase::cancelAppointment(const std::string& appointmentID)
{
    for (auto& appointment : appointments)
    {
        if (appointment.getAppointmentID() == appointmentID)
        {
            appointment.setStatus("Cancelled");
            recordUndoOperation("CANCEL_APPOINTMENT:" + appointmentID);
            return true;
        }
    }

    return false;
}

const std::vector<Appointment>& ClinicDatabase::getAppointments() const
{
    return appointments;
}

void ClinicDatabase::addToWaitingQueue(const std::string& patientID)
{
    if (findPatientByID(patientID) == nullptr)
        throw std::invalid_argument("Patient does not exist.");

    waitingQueue.push(patientID);
}

std::string ClinicDatabase::getNextWaitingPatient()
{
    if (waitingQueue.empty())
        return "";

    std::string patientID = waitingQueue.front();
    waitingQueue.pop();

    return patientID;
}

int ClinicDatabase::getWaitingCount() const
{
    return static_cast<int>(waitingQueue.size());
}

void ClinicDatabase::recordUndoOperation(const std::string& operation)
{
    undoStack.push(operation);
}

void ClinicDatabase::recordPatientEdit(const PatientRecord& patient)
{
    PatientSnapshot snapshot;

    snapshot.patientID = patient.getPatientID();
    snapshot.name = patient.getName();
    snapshot.age = patient.getAge();
    snapshot.contact = patient.getContact();

    editedPatients.push(snapshot);
    recordUndoOperation("EDIT:" + snapshot.patientID);
}

bool ClinicDatabase::undoLastOperation()
{
    if (undoStack.empty())
        return false;

    std::string operation = undoStack.top();

    // Undo patient registration
    if (operation.find("ADD:") == 0)
    {
        std::string patientID = operation.substr(4);

        auto it = std::find_if(
            patients.begin(),
            patients.end(),
            [&patientID](const std::unique_ptr<PatientRecord>& patient)
            {
                return patient->getPatientID() == patientID;
            });

        if (it == patients.end())
            return false;

        patients.erase(it);
        undoStack.pop();

        return true;
    }

    // Undo patient deletion
    if (operation.find("DELETE:") == 0)
    {
        if (deletedPatients.empty())
            return false;

        std::string patientID = operation.substr(7);

        if (deletedPatients.top()->getPatientID() != patientID)
            return false;

        patients.push_back(std::move(deletedPatients.top()));
        deletedPatients.pop();

        undoStack.pop();

        return true;
    }

    // Undo patient editing
    if (operation.find("EDIT:") == 0)
    {
        if (editedPatients.empty())
            return false;

        PatientSnapshot snapshot = editedPatients.top();

        PatientRecord* patient =
            findPatientByID(snapshot.patientID);

        if (patient == nullptr)
            return false;

        patient->setName(snapshot.name);
        patient->setAge(snapshot.age);
        patient->setContact(snapshot.contact);

        editedPatients.pop();
        undoStack.pop();

        return true;
    }

    return false;
}

void ClinicDatabase::updatePatientCache(PatientRecord* patient)
{
    for (int i = 9; i > 0; --i)
        patientCache[i] = patientCache[i - 1];

    patientCache[0] = patient;
}
std::vector<std::string> ClinicDatabase::getWaitingPatients() const
{
    std::vector<std::string> waitingPatients;

    std::queue<std::string> temporaryQueue = waitingQueue;

    while (!temporaryQueue.empty()) {
        waitingPatients.push_back(temporaryQueue.front());
        temporaryQueue.pop();
    }

    return waitingPatients;
}

}