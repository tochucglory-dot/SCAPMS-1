#include "SortEngine.h"
#include <algorithm>

namespace SCAPMS {

// SELECTION SORT: Arrange patients alphabetically by name
void SortEngine::selectionSortByName(
    std::vector<std::unique_ptr<PatientRecord>>& patients)
{
    int n = static_cast<int>(patients.size());

    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < n; j++)
        {
            if (patients[j]->getName() <
                patients[minIndex]->getName())
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
            std::swap(patients[i], patients[minIndex]);
    }
}

// INSERTION SORT: Arrange patients by ID
void SortEngine::insertionSortByID(
    std::vector<std::unique_ptr<PatientRecord>>& patients)
{
    int n = static_cast<int>(patients.size());

    for (int i = 1; i < n; i++)
    {
        int j = i;

        while (j > 0 &&
               patients[j]->getPatientID() <
                   patients[j - 1]->getPatientID())
        {
            std::swap(patients[j], patients[j - 1]);
            j--;
        }
    }
}

// MERGE SORT: Arrange patients by age
void SortEngine::mergeSortByAge(
    std::vector<std::unique_ptr<PatientRecord>>& patients)
{
    if (patients.size() <= 1)
        return;

    auto merge = [&](auto&& self, int left, int middle, int right) -> void
    {
        std::vector<std::unique_ptr<PatientRecord>> temp;

        int i = left;
        int j = middle + 1;

        while (i <= middle && j <= right)
        {
            if (patients[i]->getAge() <= patients[j]->getAge())
                temp.push_back(std::move(patients[i++]));
            else
                temp.push_back(std::move(patients[j++]));
        }

        while (i <= middle)
            temp.push_back(std::move(patients[i++]));

        while (j <= right)
            temp.push_back(std::move(patients[j++]));

        for (int k = 0; k < static_cast<int>(temp.size()); k++)
            patients[left + k] = std::move(temp[k]);
    };

    auto sort = [&](auto&& self, int left, int right) -> void
    {
        if (left >= right)
            return;

        int middle = left + (right - left) / 2;

        self(self, left, middle);
        self(self, middle + 1, right);

        merge(merge, left, middle, right);
    };

    sort(sort, 0, static_cast<int>(patients.size()) - 1);
}

}