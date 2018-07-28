#ifndef _TIME_VALUE_HH
#define _TIME_VALUE_HH

class TimeVal {
/** copy assign, -=, +=, >=, ==, !=, copy constructor, general constructot TimeVal(struct timeval *)**/
public:
    TimeVal & operator-=(TimeVal &val);
    TimeVal & operator+=(TimeVal &val);
    bool operator>=(TimeVal &val);
    bool operator==(TimeVal &val);
    bool operator!=(TimeVal &val);
    
protected:
    TimeVal(struct timeval *val);
    TimeVal(TimeVal &val);
    TimeVal & operator=(TimeVal &val);
    
};

#endif