#include <iostream>

using namespace std;


// 基类 Person
class Person{
private:
    int m_id;
    char *m_mob;

protected:
    char *m_addr;

public:
    char *m_name;
    char *m_city;

    Person(char *name, char *city, int id, char *mob, char *addr);

    void set_id(int new_id);
    int get_id() const;
    void set_mob(char *new_mob);
    char *get_mob() const;

    void show();
};

Person::Person(char *name, char *city, int id, char *mob, char *addr): m_mob(mob), m_id(id), m_addr(addr){
    m_name = name;
    m_city = city;
}

void Person::set_id(int new_id) {
    m_id = new_id;
}


int Person::get_id() const {
    return m_id;
}


void Person::set_mob(char *new_mob) {
    m_mob = new_mob;
}


char *Person::get_mob() const {
    return m_mob;
}


void Person::show() {
    std::cout << "id: " << m_id << endl;
    std::cout << "name: " << m_name << endl;
    std::cout << "city: " << m_city << endl;
    std::cout << "mob: " << m_mob << endl;
    std::cout << "addr: " << m_addr << endl;
}


// 派生类 Student
class Student: public Person{
private:
    float m_score;

public:
    int m_std_id;
    char *m_role;

    /*  构造函数
     *      1. Person类的构造函数不能被继承，因为即使继承了，名字也跟Student类的构造函数名称不一样
     *      2. 在设计派生类时，对继承过来的成员变量的初始化工作也要由派生类的构造函数完成，但是大部分基类都有 private 属性的成员变量，
     *         它们在派生类中无法访问，更不能使用派生类的构造函数来初始化。
     *         c++提供的一个解决方法是在派生类的构造函数中调用基类的构造函数。
     *         这里注意，是"调用"基类的构造函数，因此调用的时候我们可以传一些常量或者干脆直接用子类传递过来的参数。
     *      3. 了解了2之后，在声明的时候，我们不能去调用基类构造函数，而是在实现构造函数定义的时候调用。调用的方式类似构造函数的初始化列表。
     *         Student(type1 args1, type2 args2): Person(args1){}
     *         这里，args1是实参，Person(args1)的调用顺序要在Student构造函数执行之前。
     *         如果是多层继承，比如 A继承自B，B又继承自C，那这个时候，构造函数的执行顺序就是 C B A
     *      4. 调用父类构造函数要与初始化列表使用逗号 ","分隔开
     *      5. 调用父类构造函数的时候，必须放在函数头部（也就是参数列表后面）调用，不能在函数体中手动调用。
     *      6. 通过派生类创建对象时必须要调用基类的构造函数。换句话说，定义派生类构造函数时最好指明基类构造函数；
     *         如果不指明，就调用基类的默认构造函数（不带参数的构造函数）；如果没有默认构造函数，那么编译失败。
     *
     */
    Student(char *name, char *city, int id, char *mob, float score, char *addr, int std_id, char *role);

    void show();
    void set_score(float new_store);
    float get_score() const;
};


Student::Student(char *name, char *city, int id, char *mob, float score, char *addr,
                 int std_id, char *role): Person(name, city, id, mob, addr),
                 m_score(score){
    m_std_id = std_id;
    m_role = role;
}


void Student::show() {

    // 访问父类的public成员变量
    std::cout << "name: " << m_name << endl;
    std::cout << "city: " << m_city << endl;

    // 访问父类的private成员变量。（没法直接访问父类的private变量，因为是不可见的，但是可以通过父类预留的get方法来获取）
    std::cout << "id: " << get_id() << endl;
    std::cout << "mob: " << get_mob() << endl;

    // 访问父类中的protected成员变量。（子类可以访问父类的protected对象，但是在外部没法通过实例对象访问该类型的成员变量。）
    std::cout << "addr: " << m_addr << endl;

    // 可以任意访问自己的所有成员变量
    std::cout << "role: " << m_role << endl;
    std::cout << "std_id: " << m_std_id << endl;
    std::cout << "score: " << m_score << endl;
}


void Student::set_score(float new_store) {
    m_score = new_store;
}


float Student::get_score() const{
    return m_score;
}


void std_use_parent_private(){
    Student wzh("wangzihao", "BJ", 1, "+86 1234567890", 59.99, "test addr", 1, "student");
    wzh.show();
}


void std_invoke_parent_var_and_func(){

    Student wzh("wangzihao", "BJ", 1, "+86 1234567890", 59.99, "test addr", 1, "student");

    wzh.Person::show();
    std::cout << wzh.Person::m_city;
}


void std_use_parent_protected(){
    /* 调用父类中的protected成员变量：
     *      1. 子类代码中是可以访问父类protected成员变量的，但是在子类和父类的实例对象中，是不能访问protected成员变量的
     *          也就是说，protected声明的成员变量，也是一种私有变量，该变量不能在类外部被访问，但是可以在类内部以及在子类的内部被访问。
     *          而private声明的成员变量更严格一些，父类中声明的private成员变量，只能在父类中使用。
     */

    // 父类实例对象不能访问父类protected成员变量
    Person wangzihao("wangzihao", "BJ", 1, "+86 1234567890", "test addr");
    // wangzihao.m_addr;   // error: 'm_addr' is a protected member of 'Person'

    // 子类实例对象不能访问父类protected成员变量
    Student wzh("wangzihao", "BJ", 1, "+86 1234567890", 59.99, "test addr", 1, "student");
    // wzh.m_addr;     // error: 'm_addr' is a protected member of 'Person'
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 验证子类会调用父类默认构造函数
class Par{
private:
    int m_s;
public:
    int m_a;

    Par();
    Par(int a, int s);
    int get_s();
};
Par::Par() {m_a = 888;}
Par::Par(int a, int s) {m_a = a; m_s = s;}
int Par::get_s(){return m_s;}


class Son: public Par{
public:
    Son();
    Son(int a, int s);
};

Son::Son() {m_a = 999;}
Son::Son(int a, int s):Par(a, s) {m_a = a;}


void std_init(){
    // 通过派生类创建对象时必须要调用基类的构造函数。换句话说，定义派生类构造函数时最好指明基类构造函数；
    // 如果不指明，就调用基类的默认构造函数（不带参数的构造函数）；如果没有默认构造函数，那么编译失败。

    Son son1(1, 2);

    // 如果删掉Par中声明和定义的默认构造函数 Par();此处编译会报错，因为找不到默认的父类构造函数了。
    Son son2;   // error: Constructor for 'Son' must explicitly initialize the base class 'Par' which does not have a default constructor

    std::cout << son1.m_a << endl;      // 1
    std::cout << son1.get_s() << endl;      // 2
    std::cout << son2.m_a << endl;      // 999
    std::cout << son2.get_s() << endl;      // 0
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 验证子类覆盖父类中方法（遮蔽），不等于重载。

class P{
public:
    void f(){};
    void f(int a){};
};


class S: public P{
public:
    void f(float a){};
    void f(char *a){};
};


void std_method_cover(){
    S obj_s;
    obj_s.f(1);
    obj_s.f(1.1);
    obj_s.f("aaa");

    // obj_s.f();      // error: No matching member function for call to 'f'
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 研究c++继承时的"向上转型"

/* 基类与子类之间的向上转型
 *      1. 在 C/C++ 中经常会发生数据类型的转换，例如将 int 类型的数据赋值给 float 类型的变量时，编译器会先把 int 类型
 *         的数据转换为 float 类型再赋值；反过来，float 类型的数据在经过类型转换后也可以赋值给 int 类型的变量。
 *
 *         数据类型转换的前提：编译器知道如何对数据进行取舍
 *
 *         类其实也是一种数据类型，也可以发生数据类型转换，不过这种转换只有在基类和派生类之间才有意义，并且只能将派生类赋值给基类，
 *         包括将派生类对象赋值给基类对象、将派生类指针赋值给基类指针、将派生类引用赋值给基类引用，这在 C++ 中称为向上转型（Upcasting），
 *         向上转型非常安全，可以由编译器自动完成
 *      2. 赋值的本质是将现有的数据写入已分配好的内存中，对象的内存只包含了成员变量，所以对象之间的赋值是成员变量的赋值，
 *         成员函数不存在赋值问题（调用函数时，还是根据对象的类型，调用相应类的方法）。
 *
 */

class Par2{
private:
    int m_pri_a;

public:
    int m_pub_b;

    Par2(int a, int b);
    void show() const;
    int get_a() const { return m_pri_a; };
    int get_b() const { return m_pub_b; };
    static void f(){ std::cout << "Par2::f run" << endl; };
};

Par2::Par2(int a, int b): m_pri_a(a), m_pub_b(b) { std::cout<< "Par2::Par2 run " << endl; }
void Par2::show() const{
    std::cout << "Par2::show" << endl;
    std::cout << "m_pri_a = " << m_pri_a << endl;
    std::cout << "m_pub_b = " << m_pub_b << endl;
    std::cout << "Par2::show  end ......." << endl;
}

class Son2: public Par2{
private:
    int m_pri_m;

public:
    int m_pub_n;

    Son2(int a, int b, int m, int n);
    void show() const;
    static void g(){ std::cout << "Son2::g run" << endl; };
};

Son2::Son2(int a, int b, int m, int n): Par2(a, b), m_pri_m(m), m_pub_n(n) { std::cout<< "Son2::Son2 run " << endl; }
void Son2::show() const{
    std::cout << "Son2::show" << endl;
    std::cout << "get_a() = " << get_a() << endl;
    std::cout << "get_b() = " << get_b() << endl;
    std::cout << "m = " << m_pri_m << endl;
    std::cout << "n = " << m_pub_n << endl;
    std::cout << "Son2::show  end ......." << endl;
}


void std_up_change_by_obj(){
    // 通过对象向上赋值

    Par2 p(1, 2);
    Son2 s(10, 20, 30, 40);

    p.show();
    s.show();

    /* 将Son2子类的实例对象赋值给Par2基类的实例对象，c++会做下面的操作：
     *      1. 将子类与基类共有的成员变量（a、b），从子类对象拷贝到父类对象，也就是说在保证父类对象p的内存布局不变的情况下，修改里面存放的值。
     *      2. 对于基类中没有的成员变量，将舍弃。
     *      3. 父类实例对象的类型肯定不会变化。其实本质上就是一个赋值操作（或者说就是一次内存拷贝）
     *
     */
    p = s;      // 10, 20

    // 调用的是父类的show方法
    p.show();   // Par2::show       m_pri_a = 10    m_pub_b = 20

    // 调用的是父类的f方法
    p.f();      // Par2::f run
}


void std_up_change_by_ptr(){
    // 通过指针向上赋值

    Par2 *p = new Par2(1, 2);
    Son2 *s = new Son2(10, 20, 30, 40);

    std::cout << "p = " << p << endl;       // 0x7f94cfc02610
    std::cout << "s = " << s << endl;       // 0x7f94cfc02620

    /* 将子类指针赋值给父类指针
     *      1. 此时没有出现对象赋值时对的拷贝操作，只是简单的将子类对象的指针赋值给了父类对象。
     *      2. 虽然赋值之后，父类对象持有的是子类对象内存的指针，但是类型仍然没变，调用方法的时候，仍然是调用Par2类的方法，
     *         也就是说将派生类指针赋值给基类指针时，通过基类指针只能使用派生类的成员变量，但不能使用派生类的成员函数。
     *         原因：
     *              编译器虽然通过指针的指向来访问成员变量，但是却不通过指针的指向来访问成员函数：编译器通过指针的类型来访问成员函数
     *  概括起来说就是：
     *      编译器通过指针来访问成员变量，指针指向哪个对象就使用哪个对象的数据
     *      编译器通过指针的类型来访问成员函数，指针属于哪个类的类型就使用哪个类的函数。
     */
    p -> show();
    s -> show();

    p = s;
    std::cout << "p = " << p << endl;       // 0x7f94cfc02620
    std::cout << "s = " << s << endl;       // 0x7f94cfc02620

    p -> show();

    p -> f();

    // p -> g();       // error : No member named 'g' in 'Par2'
}


void std_up_change_by_reference(){
    /* 使用引用向上赋值
     *      引用和指针并没有本质上的区别，引用仅仅是对指针进行了简单封装，所以表现跟向上赋值指针是一样的逻辑。
     */

    Par2 p(1, 2);
    Par2 &p_ref = p;

    Son2 s(10, 20, 30, 40);
    Son2 &s_ref = s;

    p_ref.show();
    s_ref.show();

    p_ref = s_ref;

    p_ref.show();
    p_ref.f();
    // p_ref.g();      // No member named 'g' in 'Par2'
}


int main() {
    /* 验证子类会调用父类默认构造函数
     * std_init();
     */

    /*
     *
     *
     *
     */

    /* 向上转型
     *      std_up_change_by_obj();
     *      std_up_change_by_ptr();
     *      std_up_change_by_reference();
     */
    return 0;
}
