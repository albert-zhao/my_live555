#include "handlerset.hh"

using namespace std;

/**circle list **/
HandlerDescriptor::HandlerDescriptor(HandlerDescriptor *nextHanderDes)
    :socketNum(-1), conditionset(0), handlerPro(nullptr), data(nullptr)
{
    if (nextHanderDes == this) {
        pNextHanler = pPrevHandler = this;
    } else if (nextHandlerDes == nullptr)
        pNextHandler = pPrevHandler = nullptr;
        cout << "warning: not commended null input parameter" << endl;
    } else {
        this->pNexthandler = nextHandlerDes;
        this->pPrevHandler = nextHandlerDes->pPrevHandler;
        nextHandlerDes->pPrevHandler->pNextHandler = this;
        nextHandlerDes->pPrevHandler = this;
    }
}




MyHandlerSet::MyHandlerSet()
    :HandlerDesHead(&HandlerDesHead)//// pNextHanler = pPrevHandler = this;
{
    cout << "finish MyHandlerSet::MyHandlerSet()" << endl;
}

HandlerDescriptor *MyHandlerSet::lookupHandler(int sockNum)
{
    HandlerDescriptor *tmpHandler;
    MyHandlerIterator iter(*this);

    while ((tmpHandler = iter.next()) != nullptr) {
        if (tmpHandler->socketNum == socknum)
            break;
    }

    return tmpHandler;
}

/** change origin HandlerDescriptor or create new **/
void MyHandlerSet::assignHandler(int num, int set, MyTaskScheduler::SocketHandler *handlerFun, void *data)
{
    HandlerDescriptor *HDes = lookupHandlerDes(num);

    if (HDes == nullptr) {
        Hdesc = new HandlerDescriptor(HandlerDesHead->pNextHandler);
        HDes->socketNum = num;
    }

    HDes->conditionSet = set;
    HDes->handlerPro = handlerFun;
    HDes->data = data;
}

void MyHandlerSet::clearHandler(int num)
{
    HandlerDescriptor *HDes = lookupHandlerDes(num);

    if (HDes == nullptr) {
        cout << "no this HandlerDescriptor that u want to clear" << endl;
        return;
    }

    delete HDes;

}




void MyHandlerIterator::reset()
{
    nextPtr = mySet.HandlerDesHead.pNextHandler;
}

MyHandlerIterator::MyHandlerIterator(MyHandlerSet &set)
    :mySet(set) //// here not copy constructor, because mySet is a reference of MyHandlerSet
{
    reset();
}

HandlerDescriptor *MyHandlerIterator::next()
{
    HandlerDescriptor *result = nextPtr;

    if (result == &mySet.HandlerDesHead)
        result = nullptr;
    else
        nextPtr = nextPtr->pNextHandler;

    return result;
}