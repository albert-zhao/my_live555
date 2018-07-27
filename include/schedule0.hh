#include "schedule.hh"
#include "handlerset.hh"
class MyTaskScheduler0: public MyTaskScheduler{
public:
    virtual ~MyTaskScheduler0();

protected:
    MyTaskScheduler0();////stop current class from instantiating it, subclass using it

private:
    MyHandlerSet *pHandlerSet;////private or protected, neeed to consider
};
