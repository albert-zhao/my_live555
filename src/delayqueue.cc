#include "delayqueue.hh"

DelayQueueEntry::DelayQueueEntry(DelayTimeVal delay)
    : delayDeltaTime(delay)
{
    pNext = pPrev = this;
}


void DelayQueue::synchronizeTime()
{
    struct timeval now;
    DelayTimeVal syncInterval;
    DelayQueueEntry *next = pNext;

    gettimeofday(&now, NULL);

    if (DelayTimeVal(&now) < syncTime) {
        syncTime = DelayTimeVal(&now);
        return;
    }

    syncInterval = DelayTimeVal(&now) - syncTime;

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
    DelayTimeVal syncInterval;
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

void DelayQueue::removeEntry(DelayQueueEntry *newEntry)
{
    if (!newEntry)
        return;

    ////synchronizeTime();

    /** need to check newEntry is in DelayQueue **/

    if (newEntry->pNext != this) {
        newEntry->pNext->delayDeltaTime += newEntry->delayDeltaTime;
    }

    newEntry->pPrev->pNext = newEntry->pNext;
    newEntry->pNext->pPrev = newEntry->pPrev;
    newEntry->pPrev = newEntry;
    newEntry->pNext = newEntry;

    return;
}