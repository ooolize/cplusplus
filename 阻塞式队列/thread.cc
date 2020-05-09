#include "Thread.h"
#include "unistd.h"
#include <pthread.h>
#include <iostream>

using std::cout;
using std::endl;

void Thread::start(){
    pthread_create(&_pthid,nullptr,func,this);
    /* LockGuard ThGuard(_ThreadMutex); */
    /* sleep(1); */
    //不知道为什么 非得加上sleep才能正常
    _isRunning=true;
    /* cout<<"start"<<endl; */
}
void Thread::join(){
    pthread_join(_pthid,nullptr);
    /* LockGuard ThGuard(_ThreadMutex); */
    _isRunning=false;
}
void* Thread::func(void*p){
    Thread*pThread=static_cast<Thread*>(p);
    /* cout<<"isRunning is"<<pThread->_isRunning<<endl; */
    /* LockGuard ThGuard(pThread->_ThreadMutex); */
    if(pThread->_isRunning==false){
        pThread->run();
    }
}
