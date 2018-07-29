#ifndef _TIME_VALUE_HH
#define _TIME_VALUE_HH
#include <sys/time.h>

class TimeVal {
/** copy assign, -=, +=, >=, ==, !=, copy constructor, general constructot TimeVal(struct timeval *)**/
public:
    TimeVal & operator-=(const TimeVal &val);
    TimeVal & operator+=(const TimeVal &val);
    bool operator>=(const TimeVal &val) const;
    bool operator==(const TimeVal &val) const;
    bool operator!=(const TimeVal &val) const;

protected:
    TimeVal(const struct timeval *val);
    TimeVal(const TimeVal &val);
    TimeVal & operator=(const TimeVal &val);

private:
    struct timeval tv;
};

#endif