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
 
using namespace::wd;

class Producer 
{
public:
	Producer()
	{}
	void producer(TaskQueue& _taskque)
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

};

class Consumer 
{
public:
	Consumer()
	{}

	~Consumer() {	cout << "~Consumer()" <<endl;	}
	void consumer(TaskQueue & _taskque)
	{
		while(1) {
			int data = _taskque.pop();
			
			cout << ">>> consumer " << pthread_self()  
				 << " get a number: " << data << endl;
			sleep(2);
		}
	}
	
};

void test()
{
	wd::TaskQueue taskque;
	unique_ptr<wd::Thread> producer
        (new Thread(std::bind(&Producer::producer,Producer(),std::ref(taskque))));
	unique_ptr<wd::Thread> consumer
        (new Thread(std::bind(&Consumer::consumer,Consumer(),std::ref(taskque))));

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
