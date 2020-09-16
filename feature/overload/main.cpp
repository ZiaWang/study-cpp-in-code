#include <iostream>

using namespace std;


void swap(int *a, int *b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}


void swap(char *a, char *b){
    char tmp;
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

}
