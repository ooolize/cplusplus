/* 一个问题： */
/* 如果结束时不加wakeup就会卡主，原因是线程在处理完自己的工作后， */
/* 由于结束标志还未更新，它会继续调用pop方法领取任务，而此时没有队列是空的， */
/* 就会阻塞在cond的wait上， */
/* 修改方法 */
/* 增加wakeup,用来在改变结束标志后唤醒所有wait的 让他们准备join */
/* 还需在TaskQueue中增加标志位，如果是要唤醒所有，那么就需要更新flags跳出pop的while循环 */


/* OO线程池 */
/* 线程如何工作呢？ */
/* 线程池创建时就放入的是线程派生类的指针,创建后调用派生类的start方法 */
/* --->拉起线程处理函数func--->run方法--->线程池线程处理函数(取出任务调用process方法) */
/* Queue中存的是什么么？ */
/* 是派生的任务类，在main 线程中创建，并加入到队列中 */


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
