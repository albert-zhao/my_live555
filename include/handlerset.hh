#ifndef _HANDLER_SET_HH
#define _HANDLER_SET_HH

#include "schedule.hh"

class HandlerDescriptor {
    friend class MyHandlerSet;
    friend class MyHandlerIterator;

private:
    HandlerDescriptor(HandlerDescriptor *nextHanderDes);
    virtual ~HandlerDescriptor();
private:
    int socketNum;
    int conditionSet;
    void *data;
    MyTaskScheduler::SocketHandler *handlerPro;
    HandlerDescriptor *pNextHandler;
    HandlerDescriptor *pPrevHandler;
};




class MyHandlerSet {
    friend class MyHandlerIterator;

public:
    MyHandlerSet();
    virtual ~MyHandlerSet();
    void assignHandler(int num, int set, MyTaskScheduler::SocketHandler *handler, void *data);
    void clearHandler(int num);

private:
    HandlerDescriptor *lookupHandler(int sockNum);

private:
    HandlerDescriptor HandlerDesHead;

};




class MyHandlerIterator {
public:
    MyHandlerIterator(MyHandlerSet &set);//temp
    virtual ~MyHandlerIterator();
    HandlerDescriptor *next();

private:
    void reset();
private:
    MyHandlerSet &mySet;
    HandlerDescriptor *nextPtr;
};
#endif