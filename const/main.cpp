#include <iostream>
#include <cstring>
#define USER "wangzihao"

using namespace std;

int get_num(){
    return 1;
}

void std_define_const(){
    /*  使用define定义常量
     *      #define name value
     *
     *  define与const创建常量的区别：
     *      1. define不会做类型的安全检查，const由于声明时需要指定常量类型，会做类型检查
     *      2. define声明的常量，可以再undef取消掉，但是const声明的变量时不能再取消的
     *      3. define声明的常量，不管#define是在何处，都会在全局生效；而const声明的常量则与命名空间有关系。
     *      4. TODO: 未完待补充
     */

    std::cout << "USER = " << USER << endl;

    {
        #define NAME "wzh"
    }
    std::cout << "NAME = " << NAME << endl;

    {
        const int age = 1;
    }

    // std::cout << "age = " << age << endl;       // error: Use of undeclared identifier 'age'

}


void std_const_var_base(){
    /* const常量的基本特性:
     *    1. 不可变性。常量是不可以被修改的。
    */
    // const int A = 1;
    // A = 2;       // error: cannot assign to variable 'A' with const-qualified type 'const int'

    /* 其他:
     *    1. 常量定义有两种方式
    */
    const int A = 1;    // 建议使用此方式，可读性好，更明确
    int const B = 1;

    /* 注意:
     *    1. 常量必须在声明的时候就初始化。
     *    2. 常量的初始化方式任意，这也影响了执行常量初始化的时间。
    */
    // const int M;    // error: default initialization of an object of const type 'const int'

    const int NUM1 = get_num();      // 运行程序时才初始化
    const int NUM2 = 1;              // 编译时初始化

    int num3 = 1;
    const int NUM3 = num3;           // 运行程序时才初始化


}


void std_const_ptr(){
    /*  const还可以用来声明指针，声明指针时，根据位置的不同会产生不同的效果：
     *      1. 指针指向的值为常量，不能修改。
     *           const char *name;      //建议使用此方式
     *           char const *name;
     *      2. 指针的值为常量，不能修改。
     *          char * const name;
    */

    const char *name1 = "wangzihao";     // *name1的值不能修改，后面只能是"wangzihao"
    char const *name2 = "wangzihao";     // *name2的值不能修改，后面只能是"wangzihao"
    char * const name3 = "wangzihao";    // &name3的值不能修改

    const char * const name4 = "wangzihao";    // &name4的值和*name4的值都不能修改

}


int std_const_params(char ch, const char *name){
    // 查找name中，某个字符ch出现的次数

    int name_len = std::strlen(name);
    int counter = 0;

    for (int i=0; i<name_len; i++){
        char name_chr = name[i];

        if (name_chr == ch){
            counter += 1;
        }
    }

    return counter;
}


void f(const char *name){
    // do nothing..
}


void std_nonconst_to_const(){
    /*  const常量与非const常量之间的转换
     *      1. 不能将const常量的数据（const char *name）赋值给非const常量（char *name）
     *              const char *name指向的数据只有读的权限，而后者则具有读和写的权限
     *      2. 可以将非const常量（char *name）赋值给const常量的数据（const char *name），即可以降低数据访问权限
     *      3. C语言标准库中很多函数的参数都被 const 限制了，但我们在以前的编码过程中并没有注意这个问题，
     *         经常将非 const 类型的数据传递给 const 类型的形参，这样做从未引发任何副作用，原因就是上面讲到的，
     *         将非 const 类型转换为 const 类型是允许的。
     */
    char *name = "wangzihao";
    f(name);

    // const char *name2 = "asdasd";
    // name = name2;       // error: assigning to 'char *' from incompatible type 'const char *'
}


int main() {
/* 基本特性
     std_const_var_base();
 */

/* const作为函数参数
    char ch = 'a';
    const char *name = "wangzihao";
    int counter = std_const_params(ch, name);

    std::cout << counter << endl;
 */

/*  将非const数据赋值给const常量
    std_nonconst_to_const
 */

/*  define与const创建常量
 *
 */
    std_define_const();

    return 0;
}
