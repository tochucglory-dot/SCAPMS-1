#ifndef SORTENGINE_H
#define SORTENGINE_H

#include <vector>
#include <memory>
#include <string>

#include "../model/PatientRecord.h"

namespace SCAPMS {

class SortEngine
{
public:
    // Selection Sort by patient name
    static void selectionSortByName(
        std::vector<std::unique_ptr<PatientRecord>>& patients);

    // Insertion Sort by patient ID
    static void insertionSortByID(
        std::vector<std::unique_ptr<PatientRecord>>& patients);

    // Merge Sort by patient age
    static void mergeSortByAge(
        std::vector<std::unique_ptr<PatientRecord>>& patients);
};

}

#endif