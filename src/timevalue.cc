#include "timevalue.hh"

TimeVal & TimeVal::operator-=(const TimeVal &val)
{
    if (!(*this >= val)) {
        this->tv.tv_sec = 0;
        this->tv.tv_usec = 0;
        reurn *this;
    }

    /** need to deal this >= val **/

}

TimeVal & TimeVal::operator+=(const TimeVal &val)
{
    this->tv.tv_sec += val.tv.tv_sec;
    this->tv.tv_usec += val.tv.tv_sec;
    this->tv.tv_sec += (this->tv.tv_usec / 1000000);
    this->tv.tv_usec += (this->tv.tv_usec % 1000000);
    return *this;
}

bool TimeVal::operator>=(const TimeVal &val) const
{
    if ((this->tv.tv_sec > val.tv.tv_sec) || ((this->tv.tv_sec == val.tv.tv_sec) && (this->tv.tv_usec >= val.tv.tv_usec)))
        return true;
    else
        return false;
}

bool TimeVal::operator==(const TimeVal &val) const
{
    if ((this->tv.tv_sec == val.tv.tv_sec) && (this->tv.tv_usec >= val.tv.tv_usec))
        return true;
    else
        return false;
}

bool TimeVal::operator!=(const TimeVal &val) const
{
    return !(*this == val);
}

TimeVal::TimeVal(struct timeval *val)
    :tv(*val)
{
    cout << "TimeVal::TimeVal(struct timeval *val) init" << endl;
}

TimeVal::TimeVal(const TimeVal &val)
    :tv(val.tv)
{
    cout << "TimeVal::TimeVal(const TimeVal &val)" << endl;
}

TimeVal & TimeVal::operator=(const TimeVal &val)
{
    tv = val.tv;
    return *this;
}