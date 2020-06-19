#include <iostream>
#include <vector>
#include <string.h>

using namespace::std;;
class String{
public:
    String()
    :_ptr(new char[1]())
    {

    }
    
    explicit
    String(const char* ptr)
    :_ptr(new char[strlen(ptr)+1]())
    {   
        strcpy(_ptr,ptr);
    }
    
    String(const String& s)
    :_ptr(new char[strlen(s._ptr)+1]())
    {
        strcpy(_ptr,s._ptr);
    }

    String(String &&s)
    :_ptr(s._ptr)
    {
        s._ptr=nullptr;///////////
    }

    String& operator=(const String& rhs){
        if(this!=&rhs){
            if(_ptr){
                delete [] _ptr;
                _ptr=nullptr;
            }
            _ptr=new char[strlen(rhs._ptr)+1]();////////////////
            strcpy(_ptr,rhs._ptr);
        }
        return *this;
    }
#if 0
    String& operator=(String&& rhs){
        if(this!=&rhs){
            if(_ptr){
                delete [] _ptr;/////////////////
                _ptr=nullptr;
            }
            _ptr=rhs._ptr;
            rhs._ptr=nullptr;
        }
        return *this;
    }
#endif
    /* char operator[](size_t idx){ */
    /*     if(idx<len()){ */
    /*         return _ptr[idx]; */
    /*     } */
    /*     return 0; */
    /* } */

    ~String(){
        if(_ptr){
            delete [] _ptr;
            _ptr=nullptr;
        }
    }
    void display()const {cout<<_ptr<<endl;}
    char* get()const{return _ptr;}
    size_t len()const{return strlen(_ptr);}
private:
    char * _ptr;
};



int main()
{
    String s("hello");
    s.display();
    String s1=s;
    String s2;
    s1.display();
    s2=s1;
    s2.display();

    
    return 0;
}

