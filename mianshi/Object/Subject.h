#pragma once
#include"Object.h"

#include<list>
#include<algorithm>


using std::list;

class Subject
{
public:
    Subject() {}
    ~Subject() {}
    virtual void attach(Object*)=0;
    virtual void detach(Object*)=0;
    virtual void notify()=0;
protected:
    list<Object*> _objs;
};
class Ring
:public Subject
{
public:
    Ring()
    :Subject()
    ,_isRinging(false)
    {

    }
    void attach(Object* obj);
    void detach(Object* obj);
    void notify();
    void press();
private:
    bool _isRinging;
};

