//基于对象的思想，亦可以实现多态的效果，同一个函数对不同的对象有不同的结果。
//具体实现是使用方法
//1.Figure中的函数适配器function绑定其他类的成员函数，
//2.display中调用Figure的接口Handle。而这个接口函数在实现的时候也仅仅是调用了function,
//3.绑定时使用bind,注意传参和引用。
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
using std::vector;
using std::cout;
using std::endl;
using std::less;
using std::ostream_iterator;
using std::placeholders::_1;
using std::bind;
using std::function;

class Figure{
public:
    using AreaCallBack=function<double()>;
    using ShowCallBack=function<void()>;
    Figure(AreaCallBack&&area,ShowCallBack&&show)
    :_area(std::move(area))
    ,_show(std::move(show))
    {

    }
    void SetAreaCallBack(AreaCallBack&& area){
            _area=std::move(area);
    }
    void SetShowCallBack(ShowCallBack&& show){
            _show=std::move(show);
        } 
    double HandleAreaCallBack(){
        if(_area){
           return  _area();
        }
        return -1;
        
    }
    void HandleShowCallBack(){
        if(_show){
            _show();
        }
    }
private:
    AreaCallBack _area;
    ShowCallBack _show;
};
class Circle{
public:
    Circle()=default;
    Circle(int r)
    :_r(r)
    {

    }
    double getArea(){
        return _r*_r*3.14;
    }
    void display(){
        cout<<"Radius = "<<_r<<endl
            <<"Area = "<<getArea()<<endl;
    }
    void showArea(){
        cout<<"Circle area = "<<getArea()<<endl;
    }
private:
    int _r;
};
class Rectangele{
public:
    Rectangele()=default;
    Rectangele(int x,int y)
    :_x(x)
    ,_y(y)
    {

    }
    double getRectangleArea(){
        return _x*_y;
    }
    void showRectangleArea(){
        cout<<"Rectangle area = "<<getRectangleArea()<<endl;
    }
private:
    int _x;
    int _y;
};

void display(Figure*f){
    cout<<"area is = "<<f->HandleAreaCallBack()<<endl;
    f->HandleShowCallBack();
}
int main()
{
    Rectangele rec(10,20);
    Circle c(10);
    Figure f(bind(&Circle::getArea,&c),
             bind(&Circle::showArea,&c));
    display(&f);

    f.SetAreaCallBack(bind(&Rectangele::getRectangleArea,&rec));
    f.SetShowCallBack(bind(&Rectangele::showRectangleArea,&rec));
    display(&f);

    return 0;
}

