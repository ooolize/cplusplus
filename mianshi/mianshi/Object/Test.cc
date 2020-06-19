/* 本质上是一个事件来临，通知关注这一事件的所有观察者。 */
/* 物品有一个链表保存观察者， */
/* 物品基类定义了添加，删除，唤醒观察者的动作，观察者基类定义唤醒后的动作。 */
/* 物品可以有很多 观察者也可以有很多 */


#include "Subject.h"
#include <memory>

using std::unique_ptr;
class Guest{
public:
    Guest(const string&name)
    :_name(name)
    {

    }
    void knock(Ring&r){
        r.press();
    }
private:
    string _name;
};
int main()
{
    unique_ptr<Object> baby1(new Baby("xiaoming"));
    unique_ptr<Object> baby2(new Baby("dapang"));
    unique_ptr<Object> nurse1(new Nurse("nurse1"));
    unique_ptr<Object> nurse2(new Nurse("nurse2"));
    
    
    Ring r;

    r.attach(baby1.get());
    r.attach(baby2.get());
    r.attach(nurse1.get());
    r.attach(nurse2.get());
    unique_ptr<Guest> guest(new Guest("guest1"));
    
    guest->knock(r);
    return 0;
}

