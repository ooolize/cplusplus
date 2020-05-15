//用allocator实现vector的动态特性
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
template<typename T>
class Vector
{
public:
    Vector()
    :_start(nullptr)
    ,_finish(nullptr)
    ,_end_of_storage(nullptr)
    {
        cout<<"Vector()"<<endl;
    }
    //负责对对象析构+资源回收
    ~Vector(){
        auto cur=_start;
        while(cur!=_finish){
            _alloc.destroy(cur++);
        }
        _alloc.deallocate(_start,size());
        cout<<"~Vector()"<<endl;
    }

    void push_back(const T &val){
        if(_start==nullptr){
            _start=_alloc.allocate(1);
            _finish=_start+1;
            _end_of_storage=_finish;

            _alloc.construct(_start,val);
        }
        else if(_finish==_end_of_storage){
            reallocate();
            _alloc.construct(_finish++,val);    
        }
        else{
            _alloc.construct(_finish++,val);    
        }
    } 
    void pop_back(){
        //pop_back不会改变capacity,回收内存交给析构函数
        if(size()>=0){
            _alloc.destroy(--_finish);
        }
    }  

    int size(){
        return _finish-_start;
    }
    int capacity(){
        return _end_of_storage-_start;
    }
private:
    void reallocate(){
        size_t newCapa=capacity()*2;
        //分配新空间
        auto _newstart=_alloc.allocate(newCapa);
        auto cur=_start,newcur=_newstart;
        //搬运元素+析构旧位置的对象
        while(cur!=_finish){
            _alloc.construct(newcur++,*cur);
            _alloc.destroy(cur++);
        }
        //回收旧内存
        _alloc.deallocate(_start,capacity());
        _finish=_newstart+size();
        _start=_newstart;
        _end_of_storage=_start+newCapa;

    }//重新分配内存,动态扩容要用的
private:    
     std::allocator<T> _alloc;

    T * _start;      //指向数组中的第一个元素
    T * _finish; //指向最后一个实际元素之后的那个元素
    T * _end_of_storage;        //指向数组本身之后的位置
};

int main()
{
    Vector<int> v;
    for(int i=0;i<10;i++){
        v.push_back(i);
        std::cout<<"size = "<<v.size()<<endl;;
        std::cout<<"capacity = "<<v.capacity()<<endl;;
    }
    cout<<"--------------------------------"<<endl;
    for(int i=0;i<10;i++){
        v.pop_back();
        std::cout<<"size = "<<v.size()<<endl;;
        std::cout<<"capacity = "<<v.capacity()<<endl;;

    }
    return 0;
}

：
