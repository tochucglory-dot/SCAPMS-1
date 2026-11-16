#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include <string>
#include <sstream>
#include <iomanip>

namespace SCAPMS {

class IDGenerator
{
private:
    static int patientCounter;
    static int appointmentCounter;

public:
    static std::string generatePatientID()
    {
        std::ostringstream stream;
        stream << "PAT" << std::setw(4)
               << std::setfill('0') << ++patientCounter;

        return stream.str();
    }

    static std::string generateAppointmentID()
    {
        std::ostringstream stream;
        stream << "APT" << std::setw(4)
               << std::setfill('0') << ++appointmentCounter;

        return stream.str();
    }
};

inline int IDGenerator::patientCounter = 0;
inline int IDGenerator::appointmentCounter = 0;

}

#endif
