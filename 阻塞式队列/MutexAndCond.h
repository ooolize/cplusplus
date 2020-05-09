//封装互斥锁和条件变量，以后直接使用即可
#ifndef __RESOURCES_H__
#define __RESOURCES_H__
#include <iostream>
#include <func.h>

using std::cout;
using std::endl;
//int total=10;最好不用全局变量
class MutexLock{
public:
    MutexLock()
    {
        pthread_mutex_init(&_mutex,NULL);
    } 
    ~MutexLock(){
        pthread_mutex_destroy(&_mutex);
    }
    void lock(){
        if(0!=pthread_mutex_lock(&_mutex)){
            perror("lock error\n");
        }
    }
    void unlock(){
        pthread_mutex_unlock(&_mutex);
    }  
    pthread_mutex_t*getMutexInstance(){
        return &_mutex;
    };
    MutexLock(MutexLock&)=delete;
    MutexLock& operator=(MutexLock&)=delete;
private:
    pthread_mutex_t _mutex;
};

class Condition{
public:
    explicit
    Condition(MutexLock&m)
    :_m(m)
    {
        pthread_cond_init(&_cond,NULL);
    }
    ~Condition(){
        pthread_cond_destroy(&_cond);
    }
    void wait(){
        pthread_cond_wait(&_cond,_m.getMutexInstance());
    }
    void notify(){
        pthread_cond_signal(&_cond);
    }
    MutexLock& getMutex(){
        return _m;
    }
    pthread_cond_t* getCond(){
        return &_cond;
    }
    Condition(Condition&)=delete;
    Condition& operator=(Condition&)=delete;
private:
    pthread_cond_t _cond;
    MutexLock &_m;
};
class LockGuard{
public:
    explicit
    LockGuard(MutexLock& mutex)
    :_mutex(mutex)
    {
        _mutex.lock();
    }
    ~LockGuard(){
        _mutex.unlock();
    }
private:
    MutexLock &_mutex;
};
