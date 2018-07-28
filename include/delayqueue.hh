#ifndef _DELAY_QUEUE_HH
#define _DELAY_QUEUE_HH

class DelayTimeVal: public TimeVal {

};

/** abstract class, so constructor is protected for subclass invoking it **/
class DelayQueueEntry {
    friend class Delayqueue; 
public:
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

private:
    DelayTimeVal syncTime;
    void synchronizeTime();

};
#endif