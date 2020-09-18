#include <iostream>

using namespace std;


/* 目前存在的一个问题：
 *      1. 在继承中，Par是基类，Sub是子类，如果他俩都实现了一个方法show，假设我们实例化了p对象和s对象分别对应父类和子类，
 *         那么当s赋值给p的时候，p是没法调用Son类中的方法的，因为c++在调用方法的时候，是根据对象类型来查找方法的，即使通过指针、引用也都不行。
 *
 *         此问题导致我们没法去实现多态。
 *
 * 虚函数：
 *      为了解决上面尴尬的问题，c++引入了"虚函数"的概念
 *      使用：
 *          在函数声明时，前面使用virtual关键字声明即可。
 *          virtual show();
 *      只需要在父类的show方法声明前，加上virtual即可，子类会在编译时自动也成为虚函数，当然，我们也可以直接指定。
 *
 * 虚函数使用注意:
 *      1. 为了方便，可以只将基类中的函数声明为虚函数，这样所有派生类中具有遮蔽关系的同名函数都将自动成为虚函数
 *          遮蔽关系要求两个函数的类型必须是完全一样的。
 *      2. 只需要在虚函数的声明处加上 virtual 关键字，函数定义处可以加也可以不加。
 *      3. 当在基类中定义了虚函数时，如果派生类没有定义新的函数来遮蔽此函数，那么将使用基类的虚函数。
 *      4. 只有派生类的虚函数覆盖基类的虚函数（函数原型相同）才能构成多态（通过基类指针访问派生类函数）。
 *              例如基类虚函数的原型为virtual void func();，派生类虚函数的原型为virtual void func(int);，
 *              那么当基类指针 p 指向派生类对象时，语句p -> func(100);将会出错，而语句p -> func();将调用基类的函数。
 *      5. 构造函数不能是虚函数。对于基类的构造函数，它仅仅是在派生类构造函数中被调用，这种机制不同于继承。
 *         也就是说，派生类不继承基类的构造函数，将构造函数声明为虚函数没有什么意义。
 *      6. 析构函数可以声明为虚函数，而且有时候必须要声明为虚函数
 *          TODO: 研究下虚析构函数
 * c++多态：
 *      C++提供多态的目的是：可以通过基类指针对所有派生类（包括直接派生和间接派生）的成员变量和成员函数进行“全方位”的访问，尤其是成员函数。
 *      如果没有多态，我们只能访问成员变量。
 *
 * 多态生效条件：
 *      1. 必须存在继承关系
 *      2. 继承关系中必须有同名的虚函数，并且它们是覆盖关系（函数原型相同）
 *      3. 存在基类的指针，通过该指针调用虚函数
 */


class Par{
private:
    int m_p;

public:
    Par(int p): m_p(p){};

    int get_p () const{ return m_p; }

    virtual void show() const;
};

void Par::show() const {
    std::cout << "Par::show " << std::endl;
    std::cout << "m_p =  " << m_p << std::endl;
    std::cout << "Par::show  end  " << std::endl;
}


class Sub: public Par{
private:
    int m_s;

public:
    Sub(int p, int s): Par(p), m_s(s){};

    /*
     *
     */
    void show() const;
};

void Sub::show() const {
    std::cout << "Sub::show " << std::endl;
    std::cout << "m_p =  " << get_p() << std::endl;
    std::cout << "m_s =  " << m_s << std::endl;
    std::cout << "Sub::show  end  " << std::endl;
}

void std_virtual_with_obj(){
    Par p(1);
    Sub s(10, 20);

    p = s;

    // 调用的仍然是Par::show
    p.show();

}



void std_virtual_with_reference(){
    Par p(1);
    Sub s(10, 20);

    Par &p_ref = p;
    Sub &s_ref = s;

    p_ref = s_ref;

    // 调用的仍然是par::show
    p_ref.show();
}



void std_virtual_with_ptr(){
    Par *p = new Par(1);
    Sub *s = new Sub(10, 20);

    p = s;

    // 调用的是sub::show
    p -> show();

}


int main() {
    std_virtual_with_reference();

    return 0;
}
