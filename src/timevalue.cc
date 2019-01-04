#include <iostream>
#include "timevalue.hh"




using namespace std;




/** public **/
TimeVal & TimeVal::operator-=(const TimeVal &val)
{
    struct timeval res;

    timersub(&tv, &val.tv, &res);
    tv = res;

    cout << "Timeval -= finished" << endl;

    return *this;
}

TimeVal & TimeVal::operator+=(const TimeVal &val)
{
    struct timeval res;

    timeradd(&tv, &val.tv, &res);
    tv = res;

    cout << "Timeval += finished" << endl;

    return *this;
}

bool TimeVal::operator>=(const TimeVal &val) const
{
    cout << "in TimeVal::operator>=" << endl;
    if ((this->tv.tv_sec > val.tv.tv_sec) || ((this->tv.tv_sec == val.tv.tv_sec) && (this->tv.tv_usec >= val.tv.tv_usec)))
        return true;
    else
        return false;
}

bool TimeVal::operator<=(const TimeVal &val) const
{
    cout << "in TimeVal::operator<=" << endl;

    return !(*this >= val);
}

bool TimeVal::operator==(const TimeVal &val) const
{
    cout << "TimeVal == finished" << endl;

    if ((this->tv.tv_sec == val.tv.tv_sec) && (this->tv.tv_usec == val.tv.tv_usec))
        return true;
    else
        return false;
}

bool TimeVal::operator!=(const TimeVal &val) const
{
    cout << "TimeVal::operator!=" << endl;
    return !(*this == val);
}

bool TimeVal::operator<(const TimeVal &val) const
{
    if ((this->tv.tv_sec < val.tv.tv_sec) || ((this->tv.tv_sec == val.tv.tv_sec) && (this->tv.tv_usec < val.tv.tv_usec)))
        return true;
    else
        return false;
}

TimeVal TimeVal::operator-(const TimeVal &val) const
{
    struct timeval res;

    timersub(&tv, &val.tv, &res);

    cout << "TimeVal operator- finished" << endl;

    return TimeVal(res);
}

void TimeVal::PrintValue()
{
    cout << "tv = " << tv.tv_sec << ", " << tv.tv_usec << endl;
}


/** protected **/
TimeVal::TimeVal(const struct timeval &val)
    :tv(val)
{
    cout << "TimeVal::TimeVal(struct timeval &val) init finished" << endl;
}

/** default copy constructor like this **/
TimeVal::TimeVal(const TimeVal &val)
    :tv(val.tv)
{
    cout << "TimeVal::TimeVal(const TimeVal &val) init finished" << endl;
}

TimeVal::TimeVal(int sec, int usec)
    :tv{sec, usec}
{
    cout << "TimeVal::TimeVal(int sec, int usec) init finished" << endl;
}

TimeVal::TimeVal()
    :tv{0, 0}
{
    cout << "TimeVal::TimeVal() init finished" << endl;
}

TimeVal & TimeVal::operator=(const TimeVal &val)
{
    cout << "TimeVal oprator =" << endl;
    tv = val.tv;
    return *this;
}