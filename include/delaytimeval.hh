#ifndef _DELAY_TIMEVAL_HH
#define _DELAY_TIMEVAL_HH
#include "timevalue.hh"




using namespace std;




class DelayTimeVal: public TimeVal {
public:
    DelayTimeVal(const struct timeval &t)
        :TimeVal(t)
    {
        cout << "DelayTimeVal(struct timeval &t) init" << endl;
    }

    DelayTimeVal(int sec, int usec)
        :TimeVal(sec, usec)
    {
        cout << "DelayTimeVal(int sec, int usec) init\n" << endl;
    }

    DelayTimeVal() : TimeVal()
    {
        cout << "DelayTimeVal() init finished\n" << endl;
    }

    DelayTimeVal(const DelayTimeVal &val): TimeVal(val)
    {
        cout << "DelayTimeVal(const DelayTimeVal &val) init\n" << endl;
    }

    DelayTimeVal operator-(const DelayTimeVal & val)
    {
        //cout << "DelayTimeVal operator-(const DelayTimeVal & val) 0" << endl;
        TimeVal &a = *this;
        ////TimeVal result = (*this) - val; error, will recursive call itself
        TimeVal result = a - val;
        //cout << "DelayTimeVal operator-(const DelayTimeVal & val)" << endl;
        return DelayTimeVal(result.getValue());
    }
    /** =, - , == != need to deal **/
    // bool operator==(const DelayTimeVal &val) {
    //     TimeVal &tv = *this;
    //     return tv == val;
    // }

    // bool operator!=(const DelayTimeVal &val) {
    //     return !(*this == val);
    // }

    /* = use default copy assignemt function */
    // DelayTimeVal & operator=(const DelayTimeVal &delaytv);

};

#endif