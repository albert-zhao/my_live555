#include <iostream>
#include "delayqueue.hh"




#define INT_MAX	0x7FFFFFFF
#define MILLION 1000000
using namespace std;




const DelayTimeVal ETERNITY(INT_MAX, MILLION);
const DelayTimeVal ZEROINTERVAL(0, 0);




DelayTimeVal TimeNow()
{
    struct timeval val;
    int ret = -1;

    ret = gettimeofday(&val, NULL);
    if (ret < 0) { //// maybe not correct
        val.tv_sec = 0;
        val.tv_usec = 0;
    }

    return DelayTimeVal(val);
}




/** DelayQueueEntry **/
DelayQueueEntry::DelayQueueEntry(const DelayTimeVal &delay)
    : delayDeltaTime(delay)
{
    pNext = pPrev = this;
}

DelayQueueEntry::~DelayQueueEntry()
{
    /** how to deal with  DelayTimeVal delayDeltaTime **/
    cout << "deinit DelayQueueEntry" << endl;
}

void DelayQueueEntry::handleTimeOut()
{
    cout << "DelayQueueEntry::handleTimeOut()" << endl;
    delete this;//// ? delete what? virtual function, call subclass deconstructor
}




/** DelayQueue **/
DelayQueue::DelayQueue(): DelayQueueEntry(ETERNITY) //// lastSyncTime default constructor
{
    cout << "DelayQueue() init\n\n" << endl;
    lastSyncTime = TimeNow();
}

void DelayQueue::synchronizeTime()
{
    struct timeval now;
    DelayTimeVal syncInterval;
    DelayQueueEntry *next = head();

    gettimeofday(&now, NULL);//// ? need to deal return value

    if (DelayTimeVal(now) < lastSyncTime) {
        lastSyncTime = DelayTimeVal(now);
        return;
    }

    cout << "after DelayTimeVal(now) < lastSyncTime\n" << endl;

    cout << "lastSyncTime: ";
    lastSyncTime.PrintValue();

    DelayTimeVal nowTimeVal(now);
    cout << "timenow: ";
    nowTimeVal.PrintValue();

    syncInterval = (nowTimeVal - lastSyncTime);
    lastSyncTime = nowTimeVal;

    cout << "next == this " << (next == this) << endl;
    ////cout << "next = " << next << ", this = " << this << endl;

    cout << "syncInterval ->";
    syncInterval.PrintValue();

    cout << "lastSyncTime: ";
    lastSyncTime.PrintValue();

    cout << "next->delayDeltaTime ->";
    next->delayDeltaTime.PrintValue();

    while ((next != this) && (syncInterval >= next->delayDeltaTime)) {
        cout << "in while ((next != this) && (syncInterval >= next->delayDeltaTime))" << endl;
        syncInterval -= next->delayDeltaTime;
        next->delayDeltaTime = ZEROINTERVAL;
        next = next->pNext;
    }

    cout << "after while ((next != this) && (syncInterval >= next->delayDeltaTime)) finished" << endl;

    if (next != this) {
        cout << "next != this" << endl;
        next->delayDeltaTime -= syncInterval;
    } else {
        cout << "next == this\n" << endl;
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
   
    cout << "before synchronizeTime\n" << endl;
    synchronizeTime();// cause newEnrty's delayDeltatime value is calculated from now

    /** add entry **/
    syncInterval = newEntry->delayDeltaTime;
    syncInterval.PrintValue();
    cout << "before while ((next != this) && (syncInterval >= next->delayDeltaTime))" << endl;
    while ((next != this) && (syncInterval >= next->delayDeltaTime)) {
        syncInterval -= next->delayDeltaTime;
        next = next->pNext;
    }

    cout << "here in addEntry" << endl;

    if (next != this) {
        next->delayDeltaTime -= syncInterval;
        newEntry->delayDeltaTime = syncInterval;
    } else {
        newEntry->delayDeltaTime = syncInterval;
        cout << "next == this" << endl;
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

    ////synchronizeTime(); // dont't need synchronizeTime, cause all entries are all based on one lastSyncTime

#if 0
    if (newEntry == this)
        return;
#else // the following method is better
    DelayQueueEntry *entry = this;
    if (newEntry == entry) //// entry is delayQueue entry header
        return;
#endif

    /** need to check newEntry is in DelayQueue **/
    entry = entry->pNext;
    while (entry != this) {
        if (entry == newEntry)
            break;
        entry = entry->pNext;
    }
    if (entry == this) //// newEntry not in delayQueue
        return;

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
        cout << "in if (head()->delayDeltaTime != ZEROINTERVAL)" << endl;
        synchronizeTime();
    }

    if (head()->delayDeltaTime == ZEROINTERVAL) {
        DelayQueueEntry *toRemove = head();
        removeEntry(toRemove);
        toRemove->handleTimeOut();
    }
}