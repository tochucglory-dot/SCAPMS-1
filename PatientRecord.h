
#ifndef PATIENTRECORD_H
#define PATIENTRECORD_H

#include <string>

namespace SCAPMS {

class PatientRecord
{
protected:
    std::string patientID;
    std::string name;
    int age;
    std::string contact;

public:
    // Constructor
    PatientRecord(const std::string& id,
                  const std::string& patientName,
                  int patientAge,
                  const std::string& patientContact);

    // Virtual destructor
    virtual ~PatientRecord() = default;

    // Getters
    std::string getPatientID() const;
    std::string getName() const;
    int getAge() const;
    std::string getContact() const;

    // Setters
    void setName(const std::string& newName);
    void setAge(int newAge);
    void setContact(const std::string& newContact);

    // Pure virtual functions
    virtual std::string getCategory() const = 0;
    virtual std::string getDescription() const = 0;
};

}

#endif

