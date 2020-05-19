#include "ThreadPool.hpp"
#include "Task.hpp"
#include <unistd.h>
#include <pthread.h>
using namespace::wd;
class MyTask
:public Task
{
public:
    void process(){
        ::srand(::time(nullptr));
        int number=::rand()%100;
        cout<<"Thread is "<<pthread_self()
            <<": numbers is "<<number<<endl;
        ::sleep(1);
    }
};
int test0()
{
    unique_ptr<Task> upTask(new MyTask());
    ThreadPool threadPool(4,10);
    threadPool.start();

    for(int i=0;i<20;i++){
        threadPool.addTask(upTask.get());        
    }
    /* sleep(5); */
    threadPool.stop();
    return 0;
};

int main(){
    test0();
    return 0;
}
