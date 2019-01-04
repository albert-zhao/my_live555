#include <iostream>
#include <unistd.h>
#include "delayqueue.hh"




using namespace std;




class Handler: public DelayQueueEntry {
public:
    Handler(DelayTimeVal &delay) : DelayQueueEntry(delay) {
        cout << "handler init finished" << endl;
    }
    ~Handler() {
        cout << "deinit Handler" << endl;
    };
    virtual void handleTimeOut();
};

void Handler::handleTimeOut()
{
    DelayQueueEntry::handleTimeOut();
}

/** 全局类变量的初始化发生在主函数之前 **/
int main()
{
#if 1
    cout << "enter main" << endl;

    int cnt = 0;
    DelayQueue queue;
    cout << "\n\n...\n\n" << endl;

    DelayTimeVal val(8, 0);
    val.PrintValue();
    cout << "\n\n....\n\n" << endl;

    Handler *entry = new Handler(val);
    cout << "\n\n...\n\n" << endl;

    queue.addEntry(entry);
    cout << "\n\n...\n\n" << endl;

    while (1) {
        sleep(1);

        queue.handleAlarm();

        cout << "handlerAlarm finished, cnt = " << ++cnt << "\n\n\n\n" << endl;
    }
#endif
    cout << "main function" << endl;
}