#include "ClinicManager.h"

namespace SCAPMS {

ClinicDatabase& ClinicManager::getDatabase()
{
    return database;
}

bool ClinicManager::registerPatient(
    std::unique_ptr<PatientRecord> patient)
{
    return database.addPatient(std::move(patient));
}

bool ClinicManager::deletePatient(const std::string& patientID)
{
    return database.deletePatient(patientID);
}

PatientRecord* ClinicManager::searchPatientByID(
    const std::string& patientID)
{
    return SearchEngine::linearSearchByID(
        database.getPatients(), patientID);
}
PatientRecord* ClinicManager::binarySearchPatientByID(
    const std::string& patientID)
{
    sortPatientsByID();

    return SearchEngine::binarySearchByID(
        database.getPatients(), patientID);
}

PatientRecord* ClinicManager::searchPatientByName(
    const std::string& name)
{
    return SearchEngine::recursiveSearchByName(
        database.getPatients(), name);
}

bool ClinicManager::scheduleAppointment(
    const Appointment& appointment)
{
    return database.addAppointment(appointment);
}

bool ClinicManager::cancelAppointment(
    const std::string& appointmentID)
{
    return database.cancelAppointment(appointmentID);
}

void ClinicManager::addPatientToQueue(
    const std::string& patientID)
{
    database.addToWaitingQueue(patientID);
}

void ClinicManager::sortPatientsByName()
{
    SortEngine::selectionSortByName(database.getPatients());
}

void ClinicManager::sortPatientsByID()
{
    SortEngine::insertionSortByID(database.getPatients());
}

void ClinicManager::sortPatientsByAge()
{
    SortEngine::mergeSortByAge(database.getPatients());
}

}