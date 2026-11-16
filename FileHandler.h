#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include "../controller/ClinicDatabase.h"

namespace SCAPMS {

class FileHandler
{
public:
    static bool savePatients(
        const ClinicDatabase& database,
        const std::string& filename);

    static bool saveAppointments(
        const ClinicDatabase& database,
        const std::string& filename);

    static bool loadPatients(
        ClinicDatabase& database,
        const std::string& filename);

};

}

#endif
