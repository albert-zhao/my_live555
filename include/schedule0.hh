#include "schedule.hh"
class MyTaskScheduler0: public MyTaskScheduler{
public:
    MyTaskScheduler0();
    virtual ~MyTaskScheduler0();

private:
    class MyHandlerSet *pHandlerSet;////private or protected, neeed to consider
};