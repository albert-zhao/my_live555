#include <iostream>
#include "timevalue.hh"
#include "delaytimeval.hh"




using namespace std;




class EventTime: public TimeVal {
public:
    EventTime(int sec = 0, int usec = 0): TimeVal(sec, usec) {
        cout << "EventTime init finished" << endl;
    }
    bool operator==(const EventTime &val) const { // this can
        cout << "EventTime == " << endl; 
        const ::TimeVal &tv = *this;// 注意 tv = *this 会错误, 注意作用域
        const ::TimeVal &tv1 = val;
        return tv == tv1;
    }
    // bool operator==(const TimeVal &val) { // error
    //     cout << "Eventtime another way == " << endl;
    //     return  TimeVal == val;
    // }

    // EventTime & operator=(const EventTime &delaytv) //// error
    // {
    //     const TimeVal &tmp = delaytv;
    //     ::TimeVal &val = *this;
    //     val = tmp; //// error, val is in ::, TimeVal& TimeVal::operator=(const TimeVal&)’ is protected
    //     return *this;
    // }

};


int main()
{
    EventTime et(3, 8);
    EventTime et1(2, 5);

    ////EventTime et2 = (et -= et1); // this can't cause (et -= et1) return TimeVal &, baseclass object can not be subclass object
    ////TimeVal tv = (et -= et1); this can if copy constructor is not protected
    et -= et1; //// correct
    et.PrintValue();

    EventTime et3(1, 3);
    cout << "et3 == et, " << (et3 == et) << endl; // use TimeVal== or use EventTime==
    EventTime et4(et3);

    et4 = et1;

    et4.PrintValue();

    et4 += et;

    et4.PrintValue();

    cout << "begin dalaytimeval test" << endl;

    DelayTimeVal dt(8, 9);
    DelayTimeVal dt1(4, 3);

    dt -= dt1;
    dt.PrintValue();

    DelayTimeVal dt3(1, 3);
    cout << "dt3 == dt, " << (dt3 == dt) << endl;

    DelayTimeVal dt4(dt3);
    dt4.PrintValue();

    dt4 = dt1;
    dt4.PrintValue();

    dt4 += dt;
    dt4.PrintValue();

}