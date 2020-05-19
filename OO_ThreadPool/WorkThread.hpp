#ifndef __WORKTHREAD_H__
#define __WORKTHREAD_H__
#include "Thread.hpp"
#include "ThreadPool.hpp"

namespace wd{

class WorkThread
: public Thread
{
public:
    WorkThread(ThreadPool& ThreadPool)
    :_threadPool(ThreadPool)
    {
        
    }
    void run(){
        _threadPool._threadFunc();   
    }
    ~WorkThread() {}

private:
    ThreadPool& _threadPool;
};

}//end of namespace
#endif

