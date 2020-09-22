#include <iostream>


/*
 * ～～～～～ 模版函数
 *
 * 模版用来解决什么问题？
 *      一般情况下，我们定义函数的时候，都会给函数的参数和返回值来指定类型，如果多个函数存在大量的因为不同参数类型导致的逻辑重复
 *      （比如swap函数可以交换多种类型的数据，但是每种类型我们都得定义一个函数），那这个时候我们就可以使用模版了。
 *      使用了template之后，数据的类型也可以通过参数来传递，在函数定义时可以不指明具体的数据类型，当发生函数调用时，编译器可以
 *      根据传入的实参自动推断数据类型。这就是类型的参数化。
 *
 *  详细介绍：
 *      1. 所谓函数模板，实际上是建立一个通用函数，它所用到的数据的类型（包括返回值类型、形参类型、局部变量类型）可以不具体指定，而是用一个
 *         虚拟的类型来代替（实际上是用一个标识符来占位），等发生函数调用时再根据传入的实参来逆推出真正的类型。这个通用函数就称为函数模板（Function Template）。
 *      2. 一但定义了函数模板，就可以将类型参数用于函数定义和函数声明了。说得直白一点，原来使用 int、float、char 等内置类型的地方，
 *         都可以用类型参数来代替。
 *  声明命名一个模版函数格式：
 *      template<typename T1, typename T2, ..., typename Tn> Tx func();
 *        template关键字告诉编译器，接下来是要创建一个模版函数
 *        <>用于存放传递进去的类型名称，类型名称可以有多个，每个类型名称前面都要使用typename来声明（typename可以使用class代替，class是旧版本的语法格式）
 *        Tx是函数的返回值，同样可以动态指定（但是必须是前面T1~Tn中的一个）。
 */

template<typename T> void swap(T *a, T *b){
    // 参数列表中的指针换成引用，使用起来更方便。
    T tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}


template<typename T> T max(T &a, T &b, T &c){
    T _max = a;

    if (b > _max){
        _max = b;
    }

    if (c > _max){
        _max = c;
    }

    return _max;
}


template<typename T1, typename T2> T1 func(T1 &m, T2 &n){
    std::cout << "T1 m = " << m << std::endl;
    std::cout << "T1 n = " << n << std::endl;

    n[0] = 's';

    T1 ret;
    ret = m;
    return ret;
}


void std_template(){
    int _max;
    int a = 1;
    int b = 2;
    int c = 3;

    _max = max(a, b, c);

    std::cout << "_max = " << _max << std::endl;

    std::cout << std::endl;
    std::cout << std::endl;

    int m = 1;
    char n[4] = "asd";
    func(m, n);
    std::cout << "T1 n = " << n << std::endl;
}



////////////////////////////////////////////////////////////////////////////////////
/*  模版类
 *      1. 函数模板中定义的类型参数可以用在函数声明和函数定义中，类模板中定义的类型参数可以用在类声明和类实现中。
 *         类模板的目的同样是将数据的类型参数化。
 *      2. 一但声明了类模板，就可以将类型参数用于类的成员函数和成员变量了。换句话说，原来使用 int、float、char
 *         等内置类型的地方，都可以用类型参数来代替。
 *      3. 类模板在实例化时必须显式地指明数据类型，编译器不能根据给定的数据推演出数据类型。
 *              比如，必须这样实例化对象：Point<int, int> p(1, 2)
 *              不能：Point p(1, 2)，这种方式，编译器是没办法通过我们传递的1、2参数来推演出数据类型的。
 *         除了上面的方式外，可以使用对象指针的方式来实例化。但是等号两侧Point后面尖括号中的类型必须是前后一致的。
 *          比如： Point<int, char*> p = new Point<int, char*>(1， "东经100")，
 *          不能：
 *              Point<int, char*> p = new Point<int, int>(1， "东经100")
 *              Point<int, char*> p = new Point(1， "东经100")
 */


// 现在创建一个坐标系类，可以用多种方式来表示坐标
template<typename T_X, typename T_Y>        // 模版类的开头，需要使用template声明模版类中要用到的类型
class Point{
public:
    Point(T_X x, T_Y y);

    // 成员函数声明时，也是直接使用上面声明好了的类型来指代返回值类型以及参数列表中参数的类型
    T_X get_x() const;
    void set_x(T_X x);

    T_Y get_y() const;
    void set_y(T_Y y);

    void show(){
        std::cout << "Point(x=" << m_x << ", y=" << m_y  << ")" << std::endl;
    }

private:
    T_X m_x;
    T_Y m_y;

};

// 每个函数在定义之前，都需要指定 template<typename T_X, typename T_Y>  Point<T_X, T_Y>
template<typename T_X, typename T_Y>
Point<T_X, T_Y>::Point(T_X x, T_Y y):m_x(x), m_y(y){}


template<typename T_X, typename T_Y>
T_X Point<T_X, T_Y>::get_x() const {
    return m_x;
}


template<typename T_X, typename T_Y>
void Point<T_X, T_Y>::set_x(T_X x) {
    m_x = x;
}


template<typename T_X, typename T_Y>
T_Y Point<T_X, T_Y>::get_y() const {
    return m_y;
}


template<typename T_X, typename T_Y>
void Point<T_X, T_Y>::set_y(T_Y y) {
    m_y = y;
}


void std_template_cls(){
    // 实例化对象的时候，必须在<>中指定模版类的T_X,T_Y真实类型
    Point<int, int> p1(1, 2);
    p1.show();

    Point<char*, char*> p2("东经10", "北纬20");
    p2.show();

    Point<int, char*> p3(100, "北纬20");
    p3.show();

    p3.set_x(101);
    p3.show();

    p3.set_y("北纬100");
    p3.show();

}


int main() {
    std_template_cls();

    return 0;
}
