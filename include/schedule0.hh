#include "schedule.hh"
#include "handlerset.hh"
#include "delayqueue.h"

class MyTaskScheduler0: public MyTaskScheduler{
public:
    virtual ~MyTaskScheduler0();

protected:
    MyTaskScheduler0();////stop current class from instantiating it, subclass using it

protected:
    /* using protected avoid declaring friend class, friend function or
     * friend class function and defining class functions to manipulate it
     * , just need subclass to inherit it
     */
    MyHandlerSet *pHandlerSet;////private or protected, neeed to consider
    int lastHandledSocketNum;
};


class AlarmHandler: public DelayQueueEntry {

}