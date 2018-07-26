#ifndef _SCHEDULE_HH
#define _SCHEDULE_HH
#include <iostream>

class MyTaskScheduler {
public:
    virtual ~MyTaskScheduler() { std::cout << "deinit MyTaskScheduler finished" << std::endl;}; ////virtual function can be inline ?
    /** main loop **/
    virtual void doEventLoop() = 0;//// temp set parameter void

typedef void SocketHandler(void *data, int mask);
#define SOCKET_READABLE 1 << 0
#define SOCKET_WRITABLE 1 << 1
#define SOCKET_EXCEPTION 1 << 2

    virtual void setSocketHandling(int socknum, int mask, SocketHandler *handlerProc, void *data) = 0;
    virtual void disableSocketHandling(int socknum) { setSocketHandling(socknum, 0, nullptr, nullptr); }

};

#endif