 ///
 /// @file    TaskQueue.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-05-06 11:57:13
 ///
 
#ifndef __WD_TASKQUEUE_H__
#define __WD_TASKQUEUE_H__

#include "MutexLock.hpp"
#include "Condition.hpp"

#include <iostream>
#include <queue>
using std::cout;
using std::endl;
using std::queue;

namespace wd
{

class TaskQueue
{
public:
	TaskQueue(size_t size = 10)
	: _queSize(size)
	, _mutex()
	, _cond(_mutex)
	{}

	bool empty();
	bool full();
	void push(int data);
	int pop();

private:
	queue<int> _que;
	size_t _queSize;
	MutexLock _mutex;
	Condition _cond;
};

}//end of namespace wd
 

#endif
