#pragma once
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;
class Object
{
public:
    Object() {}
    ~Object() {}
    virtual void update()=0;
private:
    
};
class Baby
:public Object
{
public:
    Baby(const string&name)
    :_name(name)
    {

    }
    void update(){
        ::srand(clock());
        int num=rand()%100;
        if(num>30){
            cout<<"Baby is awake!"<<endl;
        }
        else{
            cout<<"baby is sleeping"<<endl;
        }
    }
private:
    string _name;
};

class Nurse
:public Object
{
public:
    Nurse(const string& name)
    :_name(name)
    {

    }
    void update(){
        ::srand(clock());
        int num=rand()%100;
        if(num>70){
            cout<<"Nurse is awake!"<<endl;
        }
        else{
            cout<<"Nurse is sleeping"<<endl;
        }
    }
private:
    string _name;
};

