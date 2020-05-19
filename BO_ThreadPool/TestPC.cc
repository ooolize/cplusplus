///
/// @file    TestThread.cc
/// @author  lemon(haohb13@gmail.com)
/// @date    2020-05-05 16:27:16
///


#include "ThreadPool.hpp"
#include <unistd.h>
#include <stdlib.h>

#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

using namespace::wd;

struct MyTask 
{
    void mytask()
    {
        ::srand(::time(nullptr));
        int data = ::rand() % 100;
        cout << ">> producer " << pthread_self()
            << " produce a number: " << data << endl;
        sleep(1);
    }

};

void test()
{
    ThreadPool myPool(4,10);
    MyTask task1;
    myPool.start();
    for(int i=0;i<20;++i){
        myPool.addTask(std::bind(&MyTask::mytask,&task1));
    }
    myPool.stop();
}
int main(void)
{
    test();
    return 0;
}
