#include "delayqueue.hh"

#define ZEROINTERVAl




DelayQueueEntry::DelayQueueEntry(DelayTimeVal delay)
    : delayDeltaTime(delay)
{
    pNext = pPrev = this;
}

void DelayQueueEntry::handleTimeOut()
{
    delete this;//// ? delete what?
}




void DelayQueue::synchronizeTime()
{
    struct timeval now;
    DelayTimeVal syncInterval;
    DelayQueueEntry *next = head();

    gettimeofday(&now, NULL);//// ? need to deal return value

    if (DelayTimeVal(&now) < lastSyncTime) {
        lastSyncTime = DelayTimeVal(&now);
        return;
    }

    syncInterval = DelayTimeVal(&now) - lastSyncTime;
    lastSyncTime = DelayTimeVal(&now);

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
    DelayQueueEntry *next = head();

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

 void DelayQueue::handleAlarm() //// process one event every time
{
    if (head()->delayDeltaTime != ZEROINTERVAL) {
        synchronizeTime();
    }

    if (head()->delayDeltaTime == ZEROINTERVAl) {
        DelayQueueEntry *toRemove = head();
        removeEntry(toRemove);
        toRemove->handleTimeOut();
    }
}