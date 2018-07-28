#include "delayqueue.hh"

DelayQueueEntry::DelayQueueEntry(DelayInterval delay)
    : delayDeltaTime(delay)
{
    pNext = pPrev = this;
}


void DelayQueue::synchronizeTime()
{
    struct timeval now;
    DelayInterval syncInterval;
    DelayQueueEntry *next = pNext;

    gettimeofday(&now, NULL);

    if (DelayInterval(&now) < syncTime) {
        syncTime = DelayInterval(&now);
        return;
    }

    syncInterval = DelayInterval(&now) - syncTime;

    while ((next != this) && (syncInterval >= next->delayDeltaTime)) {
        syncInterval -= next->delayDeltaTime;
        next->delayDeltaTime = ZEROINTERVAL;
        next = next->pNext;
    }

    if (next != this) {
        next->delayDeltaTime -= syncInterval;
    }

}


void DelayQueue::addEntry(DelayQueueEntry *newEntry)
{
    DelayInterval syncInterval;
    DelayQueueEntry *next = pNext;

    if (!newEntry) {
        cout << "newEntry is nullptr" << endl;
        return;
    }
   
    synchronizeTime();

    /** add entry **/
    syncInterval = newEntry->delayDeltaTime;
    while ((next != this) && (syncInterval >= next->delayDeltaTime)) {
        syncInterval -= next->delayDeltaTime;
        next = next->pNext;
    }

    if (next != this) {
        next->delayDeltaTime -= syncInterval;
        newEntry->delayDeltaTime = syncInterval;
    } else {
        newEntry->delayDeltaTime = syncInterval;
    }

    next->pPrev->pNext = newEntry;
    newEntry->pPrev = next->pPrev;
    newEntry->pNext = next;
    next->pPrev = newEntry;

    return;
}