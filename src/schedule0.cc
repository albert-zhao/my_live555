#include "schedule0.hh"




using namespace std;



/** MyTaskScheduler0 **/
MyTaskScheduler0::MyTaskScheduler0()
{
    pHandlerSet = new MyHandlerSet();
    cout << "initial MyTaskScheduler0 finished" << endl;
}

MyTaskScheduler0::~MyTaskScheduler0()
{
    cout << "deinit MyTaskScheduler0 finished" << endl;
    delete pHandlerSet;
}




/**  AlarmHandler **/
AlarmHandler::~AlarmHandler()
{
    cout << "deinit AlarmHandler" << endl;
}

void AlarmHandler::handleTimeOut()
{
    /** TO DO **/
    DelayQueueEntry::handleTimeOut();
}