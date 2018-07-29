#ifndef _DELAY_QUEUE_HH
#define _DELAY_QUEUE_HH
#include "timevalue.hh"
using namespace std;

class DelayTimeVal: public TimeVal {
public:
    DelayTimeVal(struct timeval *t)
        :TimeVal(t)
    { 
        cout << "DelayTimeVal(struct timeval *t) init" << endl;
    }

    /** =, - need to deal **/
    DelayTimeVal & operator=(const DelayTimeVal &delaytv);

};

/** abstract class, so constructor is protected for subclass invoking it **/
class DelayQueueEntry {
    friend class Delayqueue; 
public:
    virtual ~DelayQueueEntry();//// must be virtual, so u can use baseclass deconstructor to call subclass deconstructor
    virtual void handleTimeOut();

protected:
    DelayQueueEntry(DelayTimeVal delay);

private://// if defined protected, may only can access the Delayqueueentry of the Delayqueue, then others can not access
    DelayQueueEntry *pNext;
    DelayQueueEntry *pPrev;
    DelayTimeVal delayDeltaTime;
};

class DelayQueue: public DelayQueueEntry {
public:
    void addEntry(DelayQueueEntry *newEntry);
    void removeEntry(DelayQueueEntry *newEntry);
    void handleAlarm();

private:
    void synchronizeTime();
    DelayQueueEntry * head() { return pNext; }

private:
    DelayTimeVal lastSyncTime;

};
#endif