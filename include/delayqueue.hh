#ifndef _DELAY_QUEUE_HH
#define _DELAY_QUEUE_HH
#include "delaytimeval.hh"




extern const DelayTimeVal ZEROINTERVAl;
extern const DelayTimeVal ETERNITY;
class DelayQueue;




/** abstract class, so constructor is protected for subclass invoking it **/
class DelayQueueEntry {
friend class DelayQueue;
public:
    virtual ~DelayQueueEntry();//// must be virtual, so u can use baseclass deconstructor to call subclass deconstructor
    virtual void handleTimeOut();

protected:
    DelayQueueEntry(const DelayTimeVal &delay);

private://// if defined protected, may only can access the Delayqueueentry of the Delayqueue, then others can not access
    DelayQueueEntry *pNext;
    DelayQueueEntry *pPrev;
    DelayTimeVal delayDeltaTime; //// when DelayqueueEntry in DelayQueue, delatDeltaTime = ETERNITY, can not be changed
};

#if 1
class DelayQueue: public DelayQueueEntry {
public:
    DelayQueue();
    void addEntry(DelayQueueEntry *newEntry);
    void removeEntry(DelayQueueEntry *newEntry);
    void handleAlarm();
    DelayTimeVal const& timeToNextAlarm();

private:
    void synchronizeTime();
    DelayQueueEntry * head() const { return pNext; }

private:
    DelayTimeVal lastSyncTime;

};
#else
class DelayQueue {
public:
    DelayQueue();
    void addEntry(DelayQueueEntry *newEntry);
    void removeEntry(DelayQueueEntry *newEntry);
    void handleAlarm();
    DelayTimeVal const& timeToNextAlarm();

private:
    void synchronizeTime();
    DelayQueueEntry * head() { return &entry; }

private:
    DelayTimeVal lastSyncTime;
    DelayQueueEntry entry;

};
#endif
#endif