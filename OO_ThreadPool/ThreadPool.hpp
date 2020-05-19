#ifndef __WD__THREADPOOL_H__
#define __WD__THREADPOOL_H__
#include "Thread.hpp"
#include "TaskQueue.hpp"
#include<memory>
#include<vector>
using std::vector;
using std::unique_ptr;
namespace wd{

class ThreadPool
{
    friend class WorkThread;
public:
    ThreadPool(size_t threadNums,size_t taskNums)
    :_threadNums(threadNums)
    ,_taskqueue(taskNums)
    ,_taskNums(taskNums)
    ,_exitFlags(false)
    {
        _threads.reserve(threadNums);
        cout<<"ThreadPool()"<<endl;
    }
    void addTask(Task*);
    Task* getTask();
    void start();
    void stop();
    ~ThreadPool() {
        if(!_exitFlags){
            stop();
        }
        cout<<"~ThreadPool()"<<endl;
    }
private:
    void _threadFunc();
private:
    vector<unique_ptr<Thread>>_threads;
    size_t _threadNums;
    TaskQueue _taskqueue;
    size_t _taskNums;
    bool _exitFlags;
};


}//end of namespace wd
#endif
