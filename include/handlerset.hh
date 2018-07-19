#ifndef _HANDLER_SET_HH
#define _HANDLER_SET_HH

class MyHandlerSet {
public:
    void assignHandler(int num, int set, MyTaskScheduler::SocketHandler *handler, void *data);
    void clearHandler(int num);

private:
    int socketNum;
    int conditionSet;
    void *data;
    MyTaskScheduler::SocketHandler *handlerPro;
};

#endif