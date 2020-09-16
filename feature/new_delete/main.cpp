#include <iostream>
using namespace std;


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


int main() {
/*  new与delete运算符
    std_new_delete()
 */
}
