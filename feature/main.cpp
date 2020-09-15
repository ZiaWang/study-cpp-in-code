#include <iostream>
#include <cassert>
using namespace std;

// namespace只能在全局或者其他namespace中定义
namespace n1{
    int a = 1;
}


namespace n2{
    int a = 2;
}


void std_namespace(){
    using namespace n1;
    std::cout << "n1::a = " << a << std::endl;

    using n2::a;
    std::cout << "n2::a = " << a << std::endl;
    std::cout << "n1::a = " << n1::a << std::endl;
}


void std_new_delete(){
    // new 和 delete 创建和删除内存的位置是在堆内存，没有在栈中。对于我们自己声明的变量，这些变量的内存是在栈中维护的。

    // 在堆内存中存在
    int *p_int = new int;
    std::cout << "p_int = " << p_int << endl;
    std::cout << "&p_int = " << &p_int  << endl;
    std::cout << "*p_int = " << *p_int << endl;
    *p_int = 2;
    std::cout << *p_int << endl;

    // 在栈内存中存在
    int j = 10;
    std::cout << "&j = " << &j << endl;

    std::cout << "delete p_int" << endl;
    delete p_int;
    std::cout << "p_int = " << p_int << endl;
    std::cout << "&p_int = " << &p_int  << endl;
    std::cout << "*p_int = " << *p_int << endl;
    std::cout << "delete end" << endl;

    p_int = &j;
    std::cout << "p_int = " << p_int << endl;
    std::cout << "&p_int = " << &p_int  << endl;
    std::cout << "*p_int = " << *p_int << endl;


    delete p_int;
    std::cout << "j = " << j << endl;
    std::cout << "&j = " << &j << endl;
    delete &j;
}


inline void int_swap(int *a, int *b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}


void std_inline(){
    // 内联函数
    // 1. 函数是一个可以重复使用的代码块，CPU 会一条一条地挨着执行其中的代码。CPU 在执行主调函数代码时如果遇到了被调函数，
    //    主调函数就会暂停，CPU 转而执行被调函数的代码；被调函数执行完毕后再返回到主调函数，主调函数根据刚才的状态继续往下执行。
    // 2. 函数调用是有时间和空间开销的。程序在执行一个函数之前需要做一些准备工作，要将实参、局部变量、返回地址以及若干寄存器都压入栈中，
    //    然后才能执行函数体中的代码；函数体中的代码执行完毕后还要清理现场，将之前压入栈中的数据都出栈，才能接着执行函数调用位置以后的代码。
    //    如果函数体代码比较多，需要较长的执行时间，那么函数调用机制占用的时间可以忽略；如果函数只有一两条语句，那么大部分的时间都会花费在函
    //    数调用机制上，这种时间开销就就不容忽视。
    // 3. 内联函数适用于"函数较短小"的函数，它是直接"用内联函数的代码替换掉调用处的函数调用"，即"将函数调用这一行代码使用函数体替换掉"

    int a = 1;
    int b = 2;
    int_swap(&a, &b);
    std::cout << "a = " << a << endl;
    std::cout << "b = " << b << endl;
}


void int_swap_no_point(int a, int b){
    // 参数不是指针的时候，调用函数时实际上传进来的是一个值的copy，而原值的引用
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}


void swap(int *a, int *b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}


void swap(string *a, string *b){
    string tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}


void std_func_overload(){
    // c++的函数在定义的时候，必须指定参数的类型，有时候我们想用一个函数来对多种类型的参数进行处理，这个时候就需要用重载。
    // 比如这里想要交换两个变量的值，而我们想交换的不止是整数，还可以是字符串、浮点数、甚至是一些类的实例对象。

    int a = 1, b = 2;
    swap(&a, &b);

    assert(a == 2);
    assert(b == 1);
}


int main() {
/*  名称空间
    int a = 3;
    std_namespace();
    //局部命名空间中调用using namespace xxx 或者using xxx::var，只会在该局部环境中生效，并且会覆盖掉上层命名空间中的内容。
    std::cout << "global::a = " << a << std::endl;
*/

/*  函数重载
    // 函数是传值的拷贝
    int m = 1, n = 2;
    int_swap_no_point(m, n);
    std::cout << "m = " << m << endl;
    std::cout << "n = " << n << endl;

    // 重载
    std_func_overload();
*/

/*  内联函数
    std_inline()
 */

/*  new与delete运算符
    std_new_delete()
 */
}
