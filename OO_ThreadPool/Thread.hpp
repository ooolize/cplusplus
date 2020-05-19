///
/// @file    Thread.h
/// @author  lemon(haohb13@gmail.com)
/// @date    2020-05-05 16:24:33
///

#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__

#include <pthread.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd
{

class Thread
{
public:
	Thread()
	: _pthid(0)
	, _isRunning(false)
	{	cout << "Thread()" << endl;	}

	virtual ~Thread();

	void start(); //开启线程 ==> pthread_create
	void join();  //回收线程

private:
	virtual void run()=0;//线程的工作就是执行任务，但这个任务是什么，不确定
	static void * threadFunc(void * arg);//线程函数执行体

private:
	pthread_t _pthid;// 线程id
	bool _isRunning;
};

}//end of namespace wd
#endif
