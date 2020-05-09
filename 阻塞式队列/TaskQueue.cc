#include "TaskQueue.h"
#include<unistd.h>
void TaskQuery::push(int val){
    LockGuard guard(_mutex);
    while(full())//防止虚假唤醒
        _cond.wait();
    _que.push(val);
    _cond.notify();
}
int TaskQuery::pop(){
    LockGuard guard(_mutex);
    while(empty()){
       _cond.wait(); 
    }
    int tmp=_que.front();
    _que.pop();
    _cond.notify();
    return tmp;
}

//wait函数的上下部
//上部：将cond加入条件队列  解锁  进入睡眠 等待唤醒
//下部：唤醒进程 加锁 操作资源
//当存在多个消费进程时，可能出现多个消费者notify生产者，如果这样使用if(full())的话就会产生虚假唤醒。
