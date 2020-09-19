#include <iostream>
using namespace std;

/*  运算符重载：
 *      重载，就是赋予新的含义。函数重载（Function Overloading）可以让一个函数名有多种功能，在不同情况下进行不同的操作。
 *      运算符重载（Operator Overloading）也是一个道理，同一个运算符可以有不同的功能。
 *
 *      运算符重载其实就是定义一个函数，在函数体内实现想要的功能，当用到该运算符时，编译器会自动调用这个函数。
 *      也就是说，运算符重载是通过函数实现的，它本质上是函数重载。
 *
 *      运算符重载函数除了函数名有特定的格式，其它地方和普通函数并没有区别。我们完全可以使用函数或者方法来代替运算符（见下面的例子）
 */


class Counter{
public:
    int m_x;
    int m_y;

    Counter();
    Counter(int x, int y);
    Counter operator+(const Counter &c) const;
};
Counter::Counter() { m_x = 0; m_y = 0; }
Counter::Counter(int x, int y):m_x(x), m_y(y) {}

Counter Counter::operator+(const Counter &c) const {

    // 返回一个匿名对象即可
    return Counter(this->m_x + c.m_x, this->m_y + c.m_y);
}


// 通过全局函数的方式来重载<<运算符
ostream &operator<<(ostream &_cout, Counter &c){
    _cout << "Counter(m_x=" << c.m_x << ", m_y=" << c.m_y << ")" << std::endl;
    return _cout;
}


Counter operator+(Counter &m, Counter &n){
    /* 让运算符重载在全局范围内生效。
     *      运算符重载函数不仅可以作为类的成员函数，还可以作为全局函数。
     *      当类型为Counter类的两个对象m、n相加的时候，编译器检测到+号两边都是Counter对象，就会转换成对应的函数调用：
     *          operator+(m, n)
     * 注意：
     *      如果operator+函数在实现的过程中，使用到了Counter中的private、protected变量，就需要在Counter类中将operator+函数声明为友元函数
     *
     */

    Counter tmp;
    tmp.m_x = m.m_x + n.m_x;
    tmp.m_y = m.m_y + n.m_y;

    return tmp;
}


void std_operator_add(){
     Counter a(1, 2);
     Counter b(2, 2);

     Counter c;

     c = a + b;

     std::cout << "c.m_x: " << c.m_x << std::endl;      // 3
     std::cout << "c.m_y: " << c.m_y << std::endl;      // 4

     // 运算符重载后，使用运算符的时候，本质上还是调用对应的函数
     Counter d = a.operator+(b);
    std::cout << "d.m_x: " << d.m_x << std::endl;      // 3
    std::cout << "d.m_y: " << d.m_y << std::endl;      // 4
}


void std_operator_global_add(){
    Counter a(1, 2);
    Counter b(2, 2);

    Counter c;
    c = a + b;

    std::cout << "c.m_x: " << c.m_x << std::endl;      // 3
    std::cout << "c.m_y: " << c.m_y << std::endl;      // 4

    Counter d;
    d = operator+(a, b);
    std::cout << "d.m_x: " << d.m_x << std::endl;      // 3
    std::cout << "d.m_y: " << d.m_y << std::endl;      // 4
}


void std_operator_out(){
    Counter a(1, 2);

    std::cout << a << std::endl;
}


int main() {
    return 0;
}
