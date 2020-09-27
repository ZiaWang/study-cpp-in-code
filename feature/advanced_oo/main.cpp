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


////////////////////////////////////////////////////////////////////////
/* ~~~~~~~~~~~~~~~~~~~~ c++ 转换构造函数
 *
 * 自动类型转换与强制类型转换：
 *      不同的数据类型之间可以相互转换。无需用户指明如何转换的称为自动类型转换（隐式类型转换），需要用户显式地指明如何转换的称为强制类型转换。
 *
 *      自动类型转换：我们不需要告诉编译器类型的转换规则，编译器会使用内置的一套规则完成数据类型的转换。
 *          比如：
 *              int a = 7;
 *              a = 1.1 + a;
 *              在这种情况下，c++编译器会先执行等式右边的逻辑，也就是说，将a变成float类型，然后再跟1.1相加，得到了8.1，再赋值给a，
 *              由于a的变量类型是int，所以还会将8.1转换成8，再赋值。
 *
 *      强制类型转换：我们需要通过语法来告诉编译器，要将某个类型的数据强制转换成我们指定的类型。
 *          比如：
 *              int a = 1;
 *              int *b = &a;
 *
 *              float *c = (float*) b;
 *              在这种情况下，如果我们不指定"(float*)"，直接将int类型的指针b赋值给float类型的指针c，编译器是会报错的。
 *              b指针指向的内存是存储了整数的内存，而c指针的类型是浮点型，如果将c的指针指向b对应的整型内存空间，在对c进行操作的时候，
 *              会把c当作浮点数来处理，但是从内存中取出来的是整数。由于计算机中整型和浮点型存储的方式不一样，使用浮点数的方式去操作整数，
 *              会导致内存中数据出问题，引发奇怪的错误。因此c++默认不允许这种类型转换，但是我们如果非要转换的话，就得使用强制类型转换。
 * 转换构造函数
 *      实际上，就算有时候我们使用强制类型转换，也不一定能转换成功，因为编译器需要知道如何将现有数据转换成对应的数据，否则的话，只会转换失败。
 *      c++给我们预留了"转换构造函数"这个接口来实现将其他类型的数据转换成当前类型的数据，我们只需要给当前类型的数据创建一个"转换构造函数"就行了
 *
 *      转换构造函数也是一种构造函数，它遵循构造函数的一般规则。转换构造函数*只有一个参数*，这个参数就是编译器尝试进行自动转换时，传入的value。
 *      比如：
 *          int a = 1.111;
 *          那么1.111就是"转换构造函数"传递进去的值。
 *
 * c++中的构造函数：
 *      默认构造函数
 *          class_name();
 *          c++默认会调用的构造函数
 *      普通构造函数
 *          class_name(typename1 var1, typename2 var2, ...)
 *          用户自定义对的构造函数
 *      拷贝构造函数
 *          class_name(const class_name &obj)
 *      转换构造函数
 *          class_name(typename var)
 *
 *      因此，以下面的Complex类为例，如果普通构造函数中包含了默认参数，那么就可以让"转换构造函数"直接复用普通构造函数的逻辑
 *          Complex(int real_v, int virtual_v=0):m_real(real_v), m_virtual(virtual_v) {}
 *
 * 类型转换函数：
 *      上面实际上是将其他类型的数据转换成当前类型的数据，但是有时候我们需要将当前类型数据转换成其他类型数据。这个时候，我们就需要定义"类型转换函数
 *      格式：
 *          operator typename(){ return data; }
 *              operator是关键字。
 *              typename是我们的目的类型。
 *              data是typename对应类型的一个值。
 *      具体举例见下面complex，我们实现一个将complex转换成int数据的类型转换函数。
 *
 *
 */

class Complex{
public:
    Complex(int real_v, int virtual_v):m_real(real_v), m_virtual(virtual_v) {}

    // 定义转换构造函数
    Complex(float val):m_real(static_cast<int>(val)), m_virtual(0){};

    // 重载 << 运算符
    friend ostream & operator<<(ostream &out, Complex &c);

    // 定义类型转换函数，将complex转换成int
    operator int()const{ return m_real; }

private:
    int m_real;
    int m_virtual;
};

ostream & operator<<(ostream &out, Complex &c){
    out << c.m_real <<" + "<< c.m_virtual <<"i";
    return out;
}


void std_customize_type_change(){
    Complex c(1, 1);

    std::cout << c << std::endl;        // 1 + 1i

    c = 1.1;

    std::cout << c << std::endl;        // 1 + 0i
}


void std_default_type_change(){
    int a;

    a = 1.99999;
    std::cout << "a = " << a << std::endl;
}


void std_force_type_change(){
    int a = 1;
    int *b = &a;

    // float *c = b;   // Cannot initialize a variable of type 'float *' with an lvalue of type 'int *'
    auto *d = reinterpret_cast<float*>(b);      // 强制转换，也可以 auto *d = (float*)(b)

}


void std_convert_type_func() {
    Complex c(1, 2);

    int a = c;
    assert(a == 1);
}


int main() {
    std_customize_type_change();
    return 0;
}
