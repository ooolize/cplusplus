//这个类用来派生不同的线程，start拉起某个具体线程，执行线程处理函数func,func内部执行run函数实现多态
#ifndef __THREAD_H__
#define __THREAD_H__
#include <pthread.h>
/* #include "Resources.h" */
#include <iostream>
using std::cout;
using std::endl;

class Thread{
public:
    Thread()
    :_pthid(0)
    ,_isRunning(false)
    /* ,_ThreadMutex() */
    {
        cout<<"Thread()"<<endl;
    }

    void start();
    void join();
    virtual
    ~Thread(){
        if(_isRunning) {
             pthread_detach(_pthid);
        }
        cout<<"~Thread()"<<endl;
    }
private:
    virtual
    void run()=0;
    static void* func(void*p);
    pthread_t _pthid;
    bool _isRunning;
    /* MutexLock _ThreadMutex; */
};
