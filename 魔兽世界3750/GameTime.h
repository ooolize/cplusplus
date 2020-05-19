#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>

using namespace::std;
namespace warcraft{

class GameTime
{
public:
    static GameTime*getInstance();
    
    static void init();
    
    static void destory(){
        if(_instance){
            delete _instance;
        }
    }
    size_t getHour(){return _hours;}
    void reset(){_mins=0;_hours=0;}
    void updata();
    void showTime();    
private:
    GameTime(size_t mins=0,size_t hours=0)
    :_mins(mins)
    ,_hours(hours)
    {
        cout<<"GameTime()"<<endl;
    }
    ~GameTime() {cout<<"~GameTime()"<<endl;}
    static GameTime* _instance;
    static pthread_once_t _once;
    size_t _mins;
    size_t _hours;
};

}
