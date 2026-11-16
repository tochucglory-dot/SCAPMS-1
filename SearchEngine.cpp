#include "SearchEngine.h"

namespace SCAPMS {

// Linear Search: searches patients one by one using ID
PatientRecord* SearchEngine::linearSearchByID(
    const std::vector<std::unique_ptr<PatientRecord>>& patients,
    const std::string& patientID)
{
    for (const auto& patient : patients)
    {
        if (patient->getPatientID() == patientID)
            return patient.get();
    }

    return nullptr;
}

// Binary Search: requires patients to be sorted by ID
PatientRecord* SearchEngine::binarySearchByID(
    const std::vector<std::unique_ptr<PatientRecord>>& patients,
    const std::string& patientID)
{
    int left = 0;
    int right = static_cast<int>(patients.size()) - 1;

    while (left <= right)
    {
        int middle = left + (right - left) / 2;

        std::string currentID = patients[middle]->getPatientID();

        if (currentID == patientID)
            return patients[middle].get();

        if (currentID < patientID)
            left = middle + 1;
        else
            right = middle - 1;
    }

    return nullptr;
}

// Recursive Search: searches patients by name
PatientRecord* SearchEngine::recursiveSearchByName(
    const std::vector<std::unique_ptr<PatientRecord>>& patients,
    const std::string& name)
{
    // Helper function performs the recursive search
    auto search = [&](auto&& self, int index) -> PatientRecord*
    {
        if (index >= static_cast<int>(patients.size()))
            return nullptr;

        if (patients[index]->getName() == name)
            return patients[index].get();

        return self(self, index + 1);
    };

    return search(search, 0);
}

}