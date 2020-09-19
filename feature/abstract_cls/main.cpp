#include <iostream>
using namespace std;

/* c++抽象函数：
 *      c++既然支持了面向对象，那么肯定也会支持我们定义抽象类。
 *      抽象类本质上也是一个类，但是这个类里面只声明各种方法和属性，不做具体实现，抽象类无法实例化对象，它将具体的实现交给了对应的子类。
 *      抽象类通常是作为基类，让派生类去实现纯虚函数。派生类必须实现纯虚函数才能被实例化。
 *
 *      c++中实现抽象类借助了 "virtual"关键字来实现抽象类。
 *          纯虚函数：
 *              纯虚函数是指 格式为 "virtual show()=0"这种格式的函数，与虚函数的区别就是在虚函数的后面多了一个"=0"
 *              纯虚函数没有函数体，不是完整的函数，无法调用，也无法为其分配内存空间。
 *
 *          当我们在一个类中，声明一个函数为纯虚函数的时候，c++就会认为这个类是一个抽象类。
 *      只有当一个派生类完全的实现了抽象类中的所有纯虚函数时，这个派生类才能够被实例化。
 *
 * 注意：
 *      1. 一个纯虚函数就可以使类成为抽象基类，但是抽象基类中除了包含纯虚函数外，还可以包含其它的成员函数（虚函数或普通函数）和成员变量。
 *      2. 只有类中的虚函数才能被声明为纯虚函数，普通成员函数和顶层函数均不能声明为纯虚函数
 *
 *
 */


class Line{
public:
    float m_len;

    Line(float len);

    virtual float area() = 0;
    virtual float volume() = 0;
};
Line::Line(float len): m_len(len) {}


class Rec: public Line{
public:
    float m_width;
    Rec(float len, float width);

    // Rec类只实现了area这个方法，没有实现volume方法，因此它仍然是一个抽象类，不能实例化对象。
    float area();

};
Rec::Rec(float len, float width): Line(len), m_width(width){}


float Rec::area() {
    return m_len * m_width;
}


class Cuboid: public Rec{
public:
    float m_high;

    Cuboid(float len, float width, float high);

    // 实现了所有纯虚函数，可以进行实例化了。
    float area();
    float volume();
};
Cuboid::Cuboid(float len, float width, float high):Rec(len, width), m_high(high) {}


float Cuboid::area(){
    return 2 * (m_len * m_high + m_high * m_width + m_len * m_width);
}


float Cuboid::volume() {
    return m_len * m_high * m_width;
}


void std_abstract(){
    // 尝试实例化Rec对象，报错
    // Rec obj_rec(1, 2);      // Variable type 'Rec' is an abstract class

    Cuboid obj_cu(1, 2, 3);

    std::cout << "area = " << obj_cu.area() << std::endl;
    std::cout << "volume = " << obj_cu.volume() << std::endl;
}


int main(){
    std_abstract();
    return 0;
}

