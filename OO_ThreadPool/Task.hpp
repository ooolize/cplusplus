#ifndef __TASK_H__
#define __TASK_H__

namespace wd{

class Task
{
public:
    virtual 
    void process()=0;
    Task() {}
    ~Task() {}
private:
};

}//end of namespace
#endif
