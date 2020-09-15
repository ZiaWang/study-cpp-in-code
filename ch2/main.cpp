#include <iostream>
using namespace std;

class Person{
    // 根据C++软件设计规范，实际项目开发中的成员变量以及只在类内部使用的成员函数（只被成员函数调用的成员函数）
    // 都建议声明为 private，而只将允许通过对象调用的成员函数声明为 public。
private:
    int m_age;
    const char *m_mob;

    // const变量只能通过初始化列表的方式来初始化
//    const char m_country;

public:
    const char *m_name;
    const char *m_city;
    const char *m_hobby;

    // 静态变量：
    //      1. 一个类中可以有一个或多个静态成员变量，所有的对象都共享这些静态成员变量，都可以引用它。
    //      2. static 成员变量和普通 static 变量一样，都在内存分区中的全局数据区分配内存，到程序结束时才释放。
    //         这就意味着，static 成员变量不随对象的创建而分配内存，也不随对象的销毁而释放内存。而普通成员变量在对象创建时分配内存，在对象销毁时释放内存。
    //      3. 静态成员变量必须初始化，而且只能在类体外进行
    //      4. 静态成员变量既可以通过对象名访问，也可以通过类名访问，但要遵循 private、protected 和 public 关键字的访问权限限制。
    //         当通过对象名访问时，对于不同的对象，访问的是同一份内存。
    // 静态变量在多个对象之间是共享的，也就是说，即使实例化n多个对象，也只会使用一份内存来存储m_count，所有对象都是使用这份内存中的数据。
    // 这里使用m_count来记录实例化了多少个对象了。
    static int m_count;

    // 构造函数，不能有返回值，支持重载。
    Person(const char *name, const char *city, int age, const char *mob);

    // 析构函数，没有参数，不能有返回值，也不能被重载，一个类只能有一个析构函数
    ~Person();

    // 类体内定义的函数，会自动变成inline的内联函数，实际开发中，对于比较复杂的函数，都会放到类的外面去定义，只在类中声明即可。
    void hello();
    void set_age(int age);
    void set_mob(const char *mob);
    void add_hobby(const char *hobby);
};

// static修饰的静态变量在初始化的时候才会分配内存，因此必须在类声明的外部进行初始化之后，才能使用static静态变量。
// 初始化时可以赋初值，也可以不赋值。如果不赋值，那么会被默认初始化为 0。
int Person::m_count = 0;


//  构造函数的调用是强制性的，一旦在类中定义了构造函数，那么创建对象时就一定要调用，不调用是错误的。
//  如果有多个重载的构造函数，那么创建对象时提供的实参必须和其中的一个构造函数匹配；反过来说，创建对象时只有一个构造函数会被调用。
Person::Person(const char *name, const char *city, int age, const char *mob): m_mob(mob), m_name(name), m_city(city){

    m_hobby = new char[10];

    // 可以自己选择是否使用初始化列表来给private属性赋值
    m_age = age;

    m_count += 1;
}

Person::~Person() {
    delete [] m_hobby;
}

void Person::add_hobby(const char *hobby) {}

void Person::hello() {
    std::cout << "name = " << m_name << endl;
    std::cout << "mob = " << *m_mob << endl;
    std::cout << "age = " << m_age << endl;
    std::cout << "city = " << m_city << endl;
}


void Person::set_age(int age) {
    m_age = age;
}


void Person::set_mob(const char *mob) {
//    m_mob = mob;
//    还可以直接使用this来给当前对象赋值，this实际上是一个const指针，使用this的一个好处是，函数参数和对象属性都可以用mob了。
//    注意：
//        1. const指针意味着this指针的值是不能修改的
//        2. this只能在成员方法内部使用（成员方法值得就是对象调用的method）
//        3. 只有当对象被创建之后，this才有意义。因此不能在static方法中使用this
//     其他介绍:
//        1. this 实际上是成员函数的一个形参，在调用成员函数时将对象的地址作为实参传递给 this。
//           不过 this 这个形参是隐式的，它并不出现在代码中，而是在编译阶段由编译器默默地将它添加到参数列表中。
//        2. this 作为隐式形参，本质上是成员函数的局部变量，所以只能用在成员函数的内部，并且只有在通过对象调用成员函数时才给 this 赋值。
//        3. 成员函数最终被编译成与对象无关的普通函数，除了成员变量，会丢失所有信息，所以编译时要在成员函数中添加一个额外的参数，
//           把当前对象的首地址传入，以此来关联成员函数和成员变量。这个额外的参数，实际上就是 this，它是成员函数和成员变量关联的桥梁。
    this -> m_mob = mob;
}


void std_instance(){
    // 实例化对象有多种方式，一种是在栈内存上创建，该内存会自动回收，另一种是在堆上创建，该内存需要我们自己调用delete来回收
    // 成员变量的初始化顺序与初始化列表中列出的变量的顺序无关，它只与成员变量在类中声明的顺序有关

    // C/C++中，字符串本质上就是一个字符数组
    // 在栈上创建对象
    Person wangzihao("wangzihao", "BeiJing", 25, "1234567890");

    wangzihao.hello();

    // 在堆上创建对象
    Person *wzh = new Person("wzh", "BeiJing", 25, "1234567890");

    wzh -> hello();

    delete wzh;
}


void std_private(){
    // 私有属性只能在类内部访问，通过实例对象只能访问public属性
    Person wangzihao("wangzihao", "BeiJing", 25, "1234567890");

//    std::cout << wangzihao.m_mob << endl();     // error: 'm_mob' is a private member of 'Person'
}


void std_initialize(){


}


void std_static(){
    Person wangzihao("wangzihao", "BeiJing", 25, "1234567890");
    Person *wzh = new Person("wzh", "BeiJing", 25, "1234567890");

    std::cout << "wangzihao.m_count = " << wangzihao.m_count << endl;
    std::cout << "wzh.m_count = " << wzh -> m_count << endl;
    std::cout << "Person.m_count = " << Person::m_count << endl;

    // 修改m_count静态变量
    wzh -> m_count = 10;

    std::cout << "wangzihao.m_count = " << wangzihao.m_count << endl;
    std::cout << "wzh.m_count = " << wzh -> m_count << endl;
    std::cout << "Person.m_count = " << Person::m_count << endl;

    delete  wzh;
}

// 析构函数在对象被销毁时调用，而对象的销毁时机与它所在的内存区域有关。
//      位于全局的对象，在程序执行结束的时候会调用这些对象的析构函数。
//      栈中的对象，在函数执行结束的时候会调用对象的析构函数。
//      堆中的对象，在调用delete的时候才会调用析构函数，如果没有delete，析构函数就不会执行。
// 举例:
class Demo{
private:
    string m_s;

public:
    Demo(string s);
    ~Demo();
};


Demo::Demo(string s):m_s(s) {}


Demo::~Demo() {
    std::cout << "do: " << m_s << endl;
}


void init_demo(){
    Demo obj1("test local");
}


Demo obj2("test global");


int main(){
/*  实例化的两种方式
    std_instance();
 */

/* 析构函数执行时间
    Demo obj3("test main");

    Demo *obj4 = new Demo("test global new");

    init_demo();
    std::cout << "main" << endl;

    delete obj4;

 */

/*  static变量

 */

    std_static();

    return 0;
}





