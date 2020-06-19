#include <iostream>
#include <memory>

using std::allocator;
using std::cout;
using std::endl;

template<class T>
class Vector{
public:
    Vector()
    :_start(nullptr)
    ,_finish(nullptr)
    ,_end_of_start(nullptr)
    {
        cout<<"Vector()"<<endl;
    }
    ~Vector(){
        auto cur=_finish;
        while(cur!=_start){
            _alloc.destroy(--cur);
        }
        _alloc.deallocate(_start,capacity());
    }
    
    void push_back(T val){
        if(_finish==_end_of_start){
            reallocate();
            _alloc.construct(_finish++,val);
        }
        else{
            _alloc.construct(_finish++,val);
        }
    }
    T pop_back(){
        if(size()>=0){
            int ans=*(--_finish);
            _alloc.destroy(_finish);
            return ans;    
        }
    }
    size_t insert(size_t pos,T val){
        if(pos>size()){
            return -1;
        }
        else{
            if(_finish==_end_of_start){
                reallocate();
                /* auto newFinish=std::uninitialized_copy(pos,_finish,pos+1); */
                _alloc.construct(_finish,*(_finish-1));
                auto _cur=_finish-1;
                while(_cur>pos+_start){
                    *(_cur+1)=*(_cur);
                    --_cur;
                }
                *_cur=val;
                return _cur-_start;
            }
            else{
                _alloc.construct(_finish,*(_finish-1));
                auto _cur=_finish++-1;
                while(_cur>=pos+_start){
                    *(_cur+1)=*(_cur);
                    --_cur;
                }
                /* *_cur=val; */
                return _cur-_start;            
            }
        }
    }
    size_t capacity(){return _end_of_start-_start;}
    size_t size(){return _finish-_start;}
    void display(){
        for(auto begin=_start;begin!=_finish;++begin){
            cout<<*begin<<" ";
        }
        cout<<endl;
    }

private:
    void reallocate(){
        auto newCap=capacity()==0?1:2*capacity();
        auto newStart=_alloc.allocate(newCap);

        auto newFinish=std::uninitialized_copy(_start,_finish,newStart);
        while(_finish!=_start)_alloc.destroy(--_finish);
        _alloc.deallocate(_start,capacity());

        _start=newStart;
        _finish=newFinish;
        _end_of_start=_start+newCap;
    }

    allocator<T> _alloc;

    T* _start;
    T* _finish;
    T* _end_of_start;
};
int main()
{
    Vector<int> v;
    /* v.push_back(1); */    
    /* cout<<"size = "<<v.size()<<endl; */  
    /*     cout<<"capacity = "<<v.capacity()<<endl; */  
    for(int i=0;i<10;i++){
        v.push_back(i);
        cout<<"size = "<<v.size()<<endl;  
        cout<<"capacity = "<<v.capacity()<<endl;  
    }
    v.display();
    v.insert(4,4);
    v.display();
    /* for(int i=10;i>0;i--){ */
    /*     v.pop_back(); */
    /*     cout<<"size = "<<v.size()<<endl; */  
    /*     cout<<"capacity = "<<v.capacity()<<endl; */  
    /* } */
    return 0;
}

