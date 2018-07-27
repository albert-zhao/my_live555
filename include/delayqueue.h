#ifndef _DELAY_QUEUE_H
#define _DELAY_QUEUE_H
/** abstract class, so constructor is protected for subclass invoking it **/
class DelayQueueEntry {
public:
    virtual void handleTimeOut();

protected:
    DelayQueueEntry(DelayInterval delay);

protected:
    DelayQueueEntry *pNext;
    DelayQueueEntry *pPrev;
    DelayInterval delayDeltaTime;
};

class DelayQueue: public DelayQueueEntry {
public:
    void addEntry(DelayQueueEntry *newEntry);
    void removeEntry(DelayQueueEntry *newEntry);
};
#endif