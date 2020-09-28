#include <iostream>
/* 类型转换运算符
 *      隐式类型转换是安全的，显式类型转换是有风险的，C语言之所以增加强制类型转换的语法，让我们意识到自己在做什么。
 *      c语言强制类型转换格式：
 *          (type)val;
 *              type就是val要转换的类型。
 *              val就是我们要转换的数据。
 *          比如：
 *              int a = 100;
 *              float b = (float) a;
 *              此时，就是将整数a强制转换成浮点数类型，然后赋值给b；
 *
 *       c++对强制类型的行为进行了分类，我们可以用四个关键字来给指明我们要做的强制转换。
 *          static_cast
 *          const_cast
 *          reinterpret_cast
 *          dynamic_cast
 *
 *       格式：
 *          xxx_cast<type> val;
 *          比如：float b = static_cast<float> a;
 */


/* static_cast转换
 *      static_cast 只能用于良性转换，这样的转换风险较低，一般不会发生什么意外。
 *      比如：
 *          - 原有的自动类型转换，例如 short 转 int、int 转 double、const 转非 const、向上转型等，这种情况下，
 *            我们也可以显式的指明是static_cast，提高可读性。
 *          - void 指针和具体类型指针之间的转换，例如void *转int *、char *转void *等；
 *          - 有转换构造函数或者类型转换函数的类与其它类型之间的转换，例如 double 转 Complex（调用转换构造函数）、Complex 转 double（调用类型转换函数）。
 *      注意：static_cast 不能用于无关类型之间的转换，因为这些转换都是有风险的
 *          比如：
 *              1. 两个具体类型指针之间的转换，例如int *转double *、Student *转int *等。不同类型的数据存储格式不一样，
 *                 长度也不一样，用 A 类型的指针指向 B 类型的数据后，会按照 A 类型的方式来处理数据：
 *                      - 如果是读取操作，可能会得到一堆没有意义的值
 *                      - 如果是写入操作，可能会使 B 类型的数据遭到破坏，当再次以 B 类型的方式读取数据时会得
 *                 到一堆没有意义的值。
 *              2. int 和指针之间的转换。将一个具体的地址赋值给指针变量是非常危险的，因为该地址上的内存可能没有分配，也可能没
 *                 有读写权限，恰好是可用内存反而是小概率事件。
 *
 *       static_cast 是“静态转换”的意思，也就是在编译期间转换，转换失败的话会抛出一个编译错误。
 * explicit关键字：
 *
 */

class Complex{
public:
    // 定义构造函数（默认参数使得他也是一个转换构造函数，如果不想让编译器用下面这个构造函数进行隐式转换，则在声明开头加上explicit关键字）
    explicit Complex(int real, int vir=0):m_real(real), m_virtual(vir){};

    // 加上explicit来避免隐式转换。
    explicit operator int() const{ return m_real; }



private:
    int m_real;
    int m_virtual;
};

void std_static_cast(){
    // 原有类型的自动转换
    auto f = static_cast<float>(1);

    int num_int = 1;
    auto *s = static_cast<void *>(&num_int);

    // 有转换构造函数的转换
    Complex c1 = static_cast<Complex>(1);

    // 有类型转换函数的转换
    int a = static_cast<int>(c1);

    // 声明了explicit之后，隐式转换会报错。
    // int b = c1;     // No viable conversion from 'Complex' to 'int'
}


/* const_cast转换
 *       static_cast 也不能用来去掉表达式的 const 修饰和 volatile 修饰。即不能将 const/volatile 类型转换为非 const/volatile 类型。
 *       c++给我们提供了const_cast来用来去掉表达式的 const 修饰或 volatile 修饰。
 *          - const_cast 就是用来将 const/volatile 类型转换为非 const/volatile 类型。
 *
 *
 *
 *
 */


void std_const_cast(){
    const int a = 1;

    int *b = const_cast<int*>(&a);
    *b = 2;

    std::cout << "a = " << a << std::endl;      // 编译阶段已经处理成了 std::cout << "a = " << 1 << std::endl;
    assert(a == 1);                 // 编译阶段已经处理成了 assert(1 == 1);

}


/* reinterpret_cast转换
 *      reinterpret即"重新解释"，指该转换仅仅是对二进制位的重新解释，不会借助已有的转换规则对数据进行调整。
 *      比如：
 *          char name[] = "abcdef";
 *          int *name_int = reinterpret_cast<int*>(&name);
 *
 *          这里意味着告诉编译器，使用解释整型的逻辑来处理name对应的内存数据。
 *
 */


void std_reinterpret_cast(){
    char name[] = "abcdef";

    int *name_int = reinterpret_cast<int*>(&name);

    std::cout << name_int << std::endl;

    name_int += 1;
    std::cout << name_int << std::endl;
}


// TODO 后面用到dynamic_cast的时候再研究，这个估计是用不到了。它是用来在继承中对对象进行向上和向下转型时使用的。


int main() {
    std_reinterpret_cast();
    return 0;
}
