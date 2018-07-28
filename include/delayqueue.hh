#ifndef _DELAY_QUEUE_HH
#define _DELAY_QUEUE_HH

class DelayInterval
{
/** copy assign -= >= constructor **/
};

/** abstract class, so constructor is protected for subclass invoking it **/
class DelayQueueEntry {
    friend class Delayqueue; 
public:
    virtual void handleTimeOut();

protected:
    DelayQueueEntry(DelayInterval delay);

private://// if defined protected, may only can access the Delayqueueentry of the Delayqueue, then others can not access
    DelayQueueEntry *pNext;
    DelayQueueEntry *pPrev;
    DelayInterval delayDeltaTime;
};

class DelayQueue: public DelayQueueEntry {
public:
    void addEntry(DelayQueueEntry *newEntry);
    void removeEntry(DelayQueueEntry *newEntry);

private:
    DelayInterval syncTime;
    void synchronizeTime();

};
#endif