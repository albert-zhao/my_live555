#include "delayqueue.hh"

DelayQueueEntry::DelayQueueEntry(DelayInterval delay)
    : delayDeltaTime(delay)
{
    pNext = pPrev = this;
}



void DelayQueue::addEntry(DelayQueueEntry *newEntry)
{
    synchronizeTime();

    /** add entry **/
}