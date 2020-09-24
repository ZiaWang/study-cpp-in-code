#include <iostream>
#include <cstdlib>
using namespace std;

/*  ~~~~~~~~~~~~ 面向对象进阶
 *
 * c++拷贝构造函数：
 *      严格来说，对象的创建包括两个阶段，首先要分配内存空间，然后再进行初始化：
 *          * 分配内存很好理解，就是在堆区、栈区或者全局数据区分配对应字节大小的内存空间。此时该内存中所包含的数据一般是零值或者随机值，
 *            没有实际的意义。
 *          * 初始化就是<首次>对内存赋值，让它的数据有意义。注意是首次赋值，再次赋值不叫初始化。初始化的时候还可以为对象分配其他的资源（
 *            打开文件、连接网络、动态分配内存等），或者提前进行一些计算（根据价格和数量计算出总价、根据长度和宽度计算出矩形的面积等）等。
 *            说白了，初始化就是调用构造函数。
 *
 *      这里说的拷贝，就是指在初始化过程中进行的，用其他对象的数据来初始化新对象的内存。
 *
 *      "拷贝构造函数"，也是一种构造函数，但是这个构造函数是在我们利用其他对象对象的拷贝来完成新对象的初始化的时候，就会自动调用。
 *          * 实际上，"拷贝构造函数"就是一个构造函数，他的定义也是跟构造函数是一样的。
 *          * 通常"拷贝构造函数"的参数是同类型的一个其他对象，然后在函数体中，我们来做一些内存拷贝操作。
 *
 *      举例：
 *          看下面Person类。
 *
 */


void std_string_copy(){
    string name1 = "wangzihao";

    // 这里是将name1内存中的数据拷贝一份，然后用来初始化name2，此时调用的就是string类的"拷贝构造函数"
    string name2 = name1;

    std::cout << name1 << std::endl;        // wangzihao
    std::cout << name2 << std::endl;        // wangzihao

    name1[0] = 'W';

    std::cout << name1 << std::endl;        // Wangzihao
    std::cout << name2 << std::endl;        // wangzihao

    // 我们还可以显式的调用string类的"拷贝构造函数"，用来初始化其他字符串
    string name3 = name1;
    assert(name3 == "Wangzihao");

    name3[0] = 'w';
    assert(name3 == "wangzihao");
    assert(name1 == "Wangzihao");

}


class Person{
public:
    Person();
    Person(char *name, int age);

    /* 拷贝构造函数
     *      1. 参数必须是一个引用，不能是一个对象。如果是一个对象，会导致死循环，并且c++在语法上要求必须传递引用进来
     *      2. 使用const关键字声明形参是一个常量对象之后，调用拷贝构造函数时，传入的实参就可以是const和非const了，
     *         如果传入的是非const，也会转型成const常量对象。但是如果形参没有声明const，那么意味着实参只能传递非const对象，且该对象是可以被修改对的。
     *
     * 默认构造函数
     *      * 如果没有显式地定义拷贝构造函数，那么编译器会自动生成一个默认的拷贝构造函数。这个默认的拷贝构造函数很简单，就是使用“老对象”的成员
     *        变量对“新对象”的成员变量进行一一赋值
     *      * 对于简单的类，默认拷贝构造函数一般是够用的，我们也没有必要再显式地定义一个功能类似的拷贝构造函数。但是当类持有其它资源时，如动态
     *        分配的内存、打开的文件、指向其他数据的指针、网络连接等，默认拷贝构造函数就不能拷贝这些资源，我们必须显式地定义拷贝构造函数，以完
     *        整地拷贝对象的所有数据
     */
    Person(const Person &p);

    void show() const;

    char *m_name;
    int m_age;
};

Person::Person(char *name, int age):m_name(name), m_age(age) {}

Person::Person(const Person &p) {
    this -> m_age = p.m_age;
    this -> m_name = p.m_name;

    std::cout << "copy instructor run..." << std::endl;
}

void Person::show() const {
    std::cout << "name: " << m_name << " ";
    std::cout << "age: " << m_age << std::endl;
}

void std_copy_constructor(){
    Person p1("wzh", 25);
    p1.show();

    Person p2 = p1;
    p2.show();

    // 不是一块内存
    std::cout << "&p2.name = " << &p2.m_name << std::endl;
    std::cout << "&p1.name = " << &p1.m_name << std::endl;
}



////////////////////////////////////////////////////////////////////////
/* 重载赋值运算符
 *      初始化与赋值的区别：
 *          在定义的同时进行赋值叫做初始化（Initialization），定义完成以后再赋值（不管在定义的时候有没有赋值）就叫做赋值（Assignment）。
 *          初始化只能有一次，赋值可以有多次。
 *          当以拷贝的方式初始化一个对象时，会调用拷贝构造函数
 *              比如：
 *                  int a = 1;
 *                  int b = a;      // 初始化b的时候，会调用拷贝int类型的构造函数
 *          当给一个对象赋值时，会调用重载过的赋值运算符。
 *                  int a = 1;
 *                  int b = 2;
 *
 *                  b = a;          // b已经初始化了，这里只是赋值。
 *
 * 编译器默认重载赋值运算符：
 *      * 即使我们没有显式的重载赋值运算符，编译器也会以默认地方式重载它。默认重载的赋值运算符功能很简单，就是将原有对象的所有成员变量一一赋值
 *        给新对象，这和默认拷贝构造函数的功能类似。
 *      * 默认的赋值运算符一般就够用了，我们也没有必要再显式地重载它。但是当类持有其它资源时，例如动态分配的内存、打开的文件、指向其他数据的指针
 *        、网络连接等，默认的赋值运算符就不能处理了，我们必须显式地重载它，这样才能将原有对象的所有数据都赋值给新对象。
 */

class Array{
public:
    Array(int len);
    Array(const Array &arr);        // 声明"拷贝构造函数"
    ~Array();

    int operator[](int i) const { return m_p[i]; }  // 重载 s[i]取数据运算符
    int &operator[](int i) { return m_p[i]; }       // 写入数据时获取元素

    Array &operator=(const Array &arr);     // 重载赋值运算符
    int length() const { return m_len; }

private:
    int m_len;
    int *m_p;
};

Array::Array(int len):m_len(len) {
    m_p = (int *)calloc(len, sizeof(int));        // 将calloc返回的指针强制转换成int类型的指针
}


Array::Array(const Array &arr) {
    std::cout << "拷贝构造函数运行了" << std::endl;

    // 拷贝构造函数只会在初始化的时候调用
    m_len = arr.m_len;
    m_p = (int *)calloc(m_len, sizeof(int));

    memcpy(m_p, arr.m_p, m_len * sizeof(int));
}


Array::~Array() {
    free(m_p);
}


Array & Array::operator=(const Array &arr) {
    // 重载=运算符函数，会在对象初始化之后，再次被赋值的时候调用

    std::cout << "重载=运算符函数执行了" << std::endl;

    if (this != &arr){      // 不是当前array，则需要创建新内存放新array数据
        m_len = arr.m_len;
        free(m_p);
        m_p = (int *)calloc(m_len, sizeof(int));
        memcpy(this->m_p, arr.m_p, m_len*sizeof(int));
    }
    return *this;
}

void printArray(const Array &arr){
    int len = arr.length();
    for(int i=0; i<len; i++){
        if(i == len-1){
            cout<<arr[i]<<endl;
        }else{
            cout<<arr[i]<<", ";
        }
    }
}

void std_array(){
    Array arr1(10);
    for(int i=0; i<10; i++){
        arr1[i] = i;
    }

    printArray(arr1);

    std::cout << "使用arr1初始化arr2" << std::endl;
    // 调用拷贝构造函数
    Array arr2 = arr1;
    printArray(arr2);

    Array arr3(5);
    for(int i=0; i<5; i++){
        arr1[i] = 5;
    }

    std::cout << "使用arr3对arr2进行赋值" << std::endl;
    arr2 = arr3;
    printArray(arr2);
}



int main() {
    std_array();
    return 0;
}
