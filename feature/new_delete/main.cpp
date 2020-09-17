#include <iostream>
using namespace std;


void std_new_delete(){
    /* new 和 delete：
     *      1. 创建和删除内存的位置是在堆内存，没有在栈中。对于我们自己声明的变量，这些变量的内存是在栈中维护的。
     *      2. 使用new创建的对象，在堆内存中创建完数据之后，会返回该内存的指针。所以我们需要使用一个指针对象来接收。
     *
     * 关于指针：
     *      1. 声明一个指针变量 type *name;
     *             此时，变量"name"就是一个指针了，打印name的时候，打印出来的就是指针指向的数据的内存地址
     *      2. *name实际上是指针指向的值，也就是说 "*name" 代表 "内存中指针指向的值"
     *      3. &name，是指针的内存地址，因为name是一个指针，指针的值也是需要有地方存储的，获取该指针值内存地址的方法就是用 &
     *      4. &*name，实际上就是name的值，因为*name是内存中name指针指向的值，那么&*name实际上就是获取该值的内存地址，就等于name。
     *
     *  扩展：
     *      1. 如果声明一个普通变量，比如 char s = 's';
     *          此时，变量s实际上代表的就是内存中的数据
     *      2. &s，就是内存中数据的地址，即一个指针
     *      3. *&s，就是s，因为&s是一个指针，指向的是's'，所以 *&s就是去取&s这个指针的值，也就是's'
     *      4. 不能对s使用*s操作，因为s不是一个指针。
     */
    // std point
    char s = 's';
    std::cout << "s = " << s << endl;
    std::cout << "&s = " << &s << endl;
    std::cout << "*&s = " << *&s << endl;
    // std::cout << "*s = " << *s << endl;     // error: Indirection requires pointer operand ('int' invalid)

    // 在堆内存中存在
    int *p_int = new int;
    std::cout << "p_int = " << p_int << endl;
    std::cout << "&p_int = " << &p_int  << endl;
    std::cout << "*p_int = " << *p_int << endl;
    std::cout << "&*p_int = " << &*p_int << endl;
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

    std_new_delete();
}
