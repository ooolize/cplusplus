/* 静态工厂模式---生产一种系列 */
/* 抽象工厂模式---生产多种系列 */
/* 下面的代码是静态工厂模式，只有figure一种产品型号，可以再加一种figure1.就是抽象工厂模式了 */

/* 满足单一职责原则，开闭原则 */
/* 目的：定义一个创建对象的接口而无需关心具体的类，让子类决定实例化哪一个类，将类的实例化延迟到子类 */
/* 注意：只有批量产生对象时才需要工厂模式，对于简单对象的创建无须使用工厂模式。或者考虑扩展性。 */

#include <iostream>
#include <memory>

using std::unique_ptr;

const double pi=3.1415926;
class Figure{
public:
    virtual double area()=0;
};

class Circle
:public Figure
{
public:
    Circle(double r1)
    :r(r1)
    {

    }
    double area(){return pi*r*r;} 
private:
    double r;
};

class Rectangle
:public Figure
{
public:
    Rectangle(int a1,int b1)
    :a(a1)
    ,b(b1)
    {

    }
    double area(){return a*b;}
private:
    double a;
    double b;
};

class FigureFactory{
public:
    virtual Figure* create()=0;
};

class RectangleFactory
:public FigureFactory
{
public:
    Figure* create(){
        return new Rectangle(10,10);
    }
};
class CircleFactory
:public FigureFactory
{
public:
    Figure* create(){
        return new Circle(10);
    }
};

void display(Figure*f){
    std::cout<<"area = "<<f->area()<<std::endl;
}
void test1(){
    unique_ptr<RectangleFactory> Rfactory(new RectangleFactory());
    unique_ptr<Figure> Rectangle1(Rfactory->create());
    
    
    unique_ptr<CircleFactory> Cfactory(new CircleFactory());
    unique_ptr<Figure> Circle1(Cfactory->create());

    display(Rectangle1.get());
    display(Circle1.get());
}
int main()
{
    test1();
    return 0;
}

