#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <vector>
#include <memory>
#include <string>

#include "../model/PatientRecord.h"

namespace SCAPMS {

class SearchEngine
{
public:
    // Linear search using patient ID
    static PatientRecord* linearSearchByID(
        const std::vector<std::unique_ptr<PatientRecord>>& patients,
        const std::string& patientID);

    // Binary search using patient ID
    static PatientRecord* binarySearchByID(
        const std::vector<std::unique_ptr<PatientRecord>>& patients,
        const std::string& patientID);

    // Recursive search using patient name
    static PatientRecord* recursiveSearchByName(
        const std::vector<std::unique_ptr<PatientRecord>>& patients,
        const std::string& name);
};

}

#endif