#ifndef APPOINTABLE_H
#define APPOINTABLE_H

#include <string>

namespace SCAPMS {

class Appointable
{
public:
    virtual ~Appointable() = default;

    virtual std::string scheduleAppointment() = 0;
    virtual std::string cancelAppointment() = 0;
};

}

#endif
