#include <iostream>
#include <vector>
#include <string.h>

using namespace::std;;
class String{
public:
    String()
    :_ptr(new char[5]()+4)
    {
        initRefCount();
    }
    
    explicit
    String(const char* ptr)
    :_ptr(new char[strlen(ptr)+5]()+4)
    {   
        strcpy(_ptr,ptr);
        initRefCount();
    }
    
    String(const String& s)
    :_ptr(s._ptr)
    {
        /* strcpy(_ptr,s._ptr); */
        incrRefCount();
    }

    String(String &&s)
    :_ptr(s._ptr)
    {
        s._ptr=nullptr;///////////
    }

    String& operator=(const String& rhs){
        if(this!=&rhs){
            /* if(_ptr){ */
            /*     delete [] _ptr; */
            /*     _ptr=nullptr; */
            /* } */

            decrRefCount();
            if(getRefCount()==0){
                delete [] (_ptr-4);
                _ptr=nullptr;
            }
            cout<<"String& operator=(const String& rhs) is 浅拷贝"<<endl;
            _ptr=rhs._ptr;
            incrRefCount();
            /* _ptr=new char[strlen(rhs._ptr)+1]();//////////////// */
            /* strcpy(_ptr,rhs._ptr); */
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

    class charProxy{
        public:
            charProxy(String& self,size_t idx)
            :_self(self)
            ,_idx(idx)
        {
            
        }
            char& operator=(char rhs){
                if(_idx<_self.len()){
                    if(_self.getRefCount()>1){
                        cout<<"deep copy"<<endl;
                        char* ptmp=new char[_self.len()+5]+4;
                        strcpy(ptmp,_self._ptr);

                        _self.decrRefCount();

                        /* if(getRefCount()==0){ */
                        /*     delete [] (_ptr-4); */
                        /*     _ptr=nullptr; */
                        /* } */
                        _self._ptr=ptmp;
                        _self.initRefCount();
                    }
                    _self._ptr[_idx]=rhs;
                    return _self._ptr[_idx];
                }
                else{
                    static char nullchar='0';
                    return nullchar;
                }
            }

            operator char(){
                return _self._ptr[_idx];
            }
            friend ostream& operator<<(ostream&os,const charProxy&s);
        private:
            String& _self;
            size_t _idx;
    };
    charProxy operator[](size_t idx){
        return charProxy(*this,idx);
    }


    ~String(){
        decrRefCount();
        if(getRefCount()==0){
            delete [] (_ptr-4);
        }
    }
    void display()const {cout<<_ptr<<endl;}
    char* get()const{return _ptr;}
    size_t len()const{return strlen(_ptr);}

    friend ostream& operator<<(ostream&os,const String& rhs);
private:
    int getRefCount(){
        return *(int*) (_ptr-4);
    }
    void initRefCount(){
       *(int*) (_ptr-4)=1;
    }
    void incrRefCount(){
        ++*(int*)(_ptr-4);
    }
    void decrRefCount(){
        --*(int*)(_ptr-4);
    }
    char * _ptr;
};

#if 1 
ostream& operator<<(ostream&os,const String::charProxy&rhs){
    os<<rhs._self[rhs._idx];
    cout<<"no deep copy"<<endl;
    return os;
}
#endif
void test1()
{
    String s("hello");
    s.display();
    String s1=s;
    String s2;
    s1.display();
    s2=s1;
    s2.display();
}

void test2(){
    String s("world");

    s.display();
    cout<<s[0]<<endl;
    String s1=s;
    s[0]='W';
    s.display();
}
int main(){
    test2();
}

