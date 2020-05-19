 ///
 /// @file    TestThread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-05-05 16:27:16
 ///
 

#include "Thread.hpp"
#include "TaskQueue.hpp"

#include <unistd.h>
#include <stdlib.h>

#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;
 

class Producer 
: public wd::Thread
{
public:
	Producer(wd::TaskQueue & taskque)
	: _taskque(taskque)
	{}

private:
	void run()
	{
		::srand(::time(nullptr));
		while(1) {
			int data = ::rand() % 100;
			_taskque.push(data);
			cout << ">> producer " << pthread_self()
				 << " produce a number: " << data << endl;
			sleep(1);
		}
	}

	wd::TaskQueue & _taskque;
};

class Consumer 
: public wd::Thread
{
public:
	Consumer(wd::TaskQueue & taskque)
	: _taskque(taskque)
	{}

	~Consumer() {	cout << "~Consumer()" <<endl;	}
private:
	void run()
	{
		while(1) {
			int data = _taskque.pop();
			
			cout << ">>> consumer " << pthread_self()  
				 << " get a number: " << data << endl;
			sleep(2);
		}
	}
	
	wd::TaskQueue & _taskque;
};

void test()
{
	wd::TaskQueue taskque;
	unique_ptr<wd::Thread> producer(new Producer(taskque));
	unique_ptr<wd::Thread> consumer(new Consumer(taskque));

	producer->start();//开启线程
	consumer->start();
	producer->join();
	consumer->join();
}

int main(void)
{
	test();
	return 0;
}
