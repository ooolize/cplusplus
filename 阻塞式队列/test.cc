#include "Thread.h"
#include "TaskQueue.h"

#include "unistd.h"

#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

class Produce
:public Thread
{
public:
    explicit
    Produce(TaskQuery&t)
    :Thread()
    ,_t(t)
    {
        cout<<"Produce()"<<endl;
    }
    ~Produce(){
        cout<<"~Produce()"<<endl;
    }
    void run(){
        cout<<"is running"<<endl;
        srand(time(nullptr));
        while(1){
            int produceNum=rand();
            _t.push(produceNum);
            cout<<"produceNum = "<<produceNum<<endl;
            sleep(1);
        }
        cout<<"Produce::run()"<<endl;
    }

private:
    TaskQuery& _t;
};
class Consume
:public Thread
{
public:
    Consume(TaskQuery&t)
    :Thread()
    ,_t(t)
    {
        cout<<"Consume(TaskQuery&t)"<<endl;
    }
    ~Consume(){
        cout<<"~Consume(TaskQuery&t)"<<endl;
    }
    void run(){
        while(1){
            int getNum=_t.pop();
            cout<<"getNum = "<<getNum<<endl;
            sleep(2);
        }
    }
private:
    TaskQuery &_t;
};
int main()
{
    TaskQuery t(10);
    unique_ptr<Produce> p(new Produce(t));
    unique_ptr<Consume> c(new Consume(t));
    p->start();
    c->start();
    p->join();
    c->join();
    return 0;
}

