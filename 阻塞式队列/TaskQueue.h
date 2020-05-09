//队列是临界资源，需要用锁，数据结构用STL的queue，
#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__
#include "MutexAndCond.h"
#include <queue>

using std::cout;
using std::endl;
using std::queue;

class TaskQuery{
public:
    TaskQuery(int size)
    :_size(size)
    ,_mutex()
    ,_cond(_mutex)
    {
        cout<<"TaskQueue"<<endl;    
    }
    bool empty(){return _que.size()==0;}
    bool full(){return _que.size()==_size;}
    void push(int);
    int pop();

private: 
    size_t _size;
    queue<int> _que;
    MutexLock _mutex;
    Condition _cond;
};
#endif

