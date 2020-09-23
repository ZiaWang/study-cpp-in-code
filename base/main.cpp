#include <iostream>
#include "mybase.h"


using namespace std;


/* include
 *      1. include表示要从其他地方导入包，他后面有两种格式 "#include <iostream>" 和 'include "iostream"  '。两者的区别在于包搜索顺序的不同。
 *          前者使用<>，表示先从系统目录中找iostream.h头文件
 *          后者使用""，表示先从当前目录寻找iostraem.h头文件。
 *      2. c++中 include导入的规则：
 *          1. 对于C语言的包，比如stdio.h，都去掉后缀，并在头文件名前面加上"c"，即 "#include <cstdio>"
 *          2. 对于旧版的C++的包，去掉后面的".h"后缀，即"#include <iostream>"
 */


/* .h文件与.cpp文件
 *      前者又叫头文件，里面存放的都是我们的声明
 *      后者用来存放定义，是头文件中声明的具体实现。
 *      注意：
 *          1. 要想在当前cpp文件中使用其他模块的函数，就需要使用include导入对应模块的头文件
 *          2. 当我们需要定义类里的成员函数，或者我们需要使用这个类时，我们在 cpp 中需要 include 这个头文件。
 */


// 实现头文件中声明的函数
void std_declare_func_in_head_file(char *s){
    // 头文件中声明（但是没有初始化）的变量，可以在其他cpp文件重复声明。
    // int std_declare_var_in_head_file1;

    // 头文件中已经声明并初始化的变量，在其他cpp文件中声明和初始化会覆盖该变量的了。
    int std_declare_var_in_head_file2;

    // 给头文件中声明的变量初始化赋值
    std_declare_var_in_head_file1 = 10;
    std::cout << std_declare_var_in_head_file1 << endl;

    // 调用头文件中已经声明并初始化好的变量
    std::cout << std_declare_var_in_head_file2 << endl;     // 0

    std::cout << s << endl;
}


void std_cin_cout(){
    // cout后面跟多个 "<<"，会将这些字符串拼接起来输出到控制台
    std::cout << "hello" << " " << "world" << std::endl;

    /*  endl与\n都可以用来换行
     *      1. \n仅仅是出书一个换行符
     *      2. std::endl会输出一个换行符并立即刷新缓冲区
     *          相当于 std::cout << "\n" << std::flush
     */

    // 输入
    int input_num;
    float input_float;

    std::cout << "input a float:" << std::endl;
    std::cin >> input_float;
    std::cout << "input_float = " << input_float << std::endl;

    // 如果传入的是一个小数，那么剩余的整数部分和小数部分会传给后面的input（0、0.111）
    std::cout << "input a number:" << std::endl;
    std::cin >> input_num;
    std::cout << "input_num = " << input_num << std::endl;

    // cin同时输入多个
    std::cout << "input a number and a float:" << std::endl;
    std::cin >> input_num >> input_float;
    std::cout << "input_num = " << input_num << std::endl;
    std::cout << "input_float = " << input_float << std::endl;
}


void std_define_var(){
    /*  变量：
     *      1. 变量实际上可以看作是一块内存区域的名称，我们对变量的操作实际上是对内存的操作。
     *      2. 不同类型的变量，决定了内存块的大小和布局。
     *  其他：
     *      1. extern
     *          在声明变量/函数的时候使用，用于告诉编译器，遇到此变量/函数的时候，去其他模块中寻找该变量的定义（要求该）。
     *          用于避免全局变量名重复声明，建议使用namespace
     *  注意：
     *      1. 变量声明不像C语言一样，严格要求在函数起始处声明，C++中只要在初始化变量之前声明即可。这个好处是可以让我们在for循环等代码块中声明变量了
     */
    std::cout << "不在函数起始位置声明变量" << std::endl;
    int num1, num2 = 2;
    num1 = num2 + 1;
    std::cout << "num1 = " << num1 << endl;

    for (int i=1; i<=3; i++){
        std::cout << "i = " << i << endl;
    }

    // 在for循环外部，i变量的值就无法获得的，这里编译main.cpp文件的时候会抛出异常
    // std::cout << "try get i = " << i << endl;       // error: use of undeclared identifier 'i'
}


// 全局变量（在整个程序的生命周期中有效）
int flag = 1;
void std_var_scope(){
    /*  变量的作用域
     *      1. 全局变量：在所有函数外部声明的变量
     *          全局变量在程序的整个生命周期都是有效的，他会在程序运行结束时释放掉。
     *      2. 局部变量：在函数体内部或者代码块内部声明的变量
     *          局部变量只会在函数内部/代码块内部生效，随着代码块的执行，然后才会在内存中创建存储变量的空间，当代码块执行结束之后，会释放掉。
     */
    std::cout << "global flag = "  << flag << endl;         // 1
    int flag = 2;

    if (1){
        int flag = 3;
        std::cout << "inner2 flag = "  << flag << endl;     // 3
    }
    std::cout << "inner1 flag = "  << flag << endl;         // 2
}


void std_datatype_size(){
    cout << "type: \t\t" << "************size**************"<< endl;

    cout << "bool: \t\t" << "所占字节数：" << sizeof(bool);
    cout << "\t最大值：" << (numeric_limits<bool>::max)();
    cout << "\t\t最小值：" << (numeric_limits<bool>::min)() << endl;

    cout << "char: \t\t" << "所占字节数：" << sizeof(char);
    cout << "\t最大值：" << (numeric_limits<char>::max)();
    cout << "\t\t最小值：" << (numeric_limits<char>::min)() << endl;

    cout << "int: \t\t" << "所占字节数：" << sizeof(int);
    cout << "\t最大值：" << (numeric_limits<int>::max)();
    cout << "\t最小值：" << (numeric_limits<int>::min)() << endl;

    cout << "double: \t" << "所占字节数：" << sizeof(double);
    cout << "\t最大值：" << (numeric_limits<double>::max)();
    cout << "\t最小值：" << (numeric_limits<double>::min)() << endl;

    cout << "float: \t\t" << "所占字节数：" << sizeof(float);
    cout << "\t最大值：" << (numeric_limits<float>::max)();
    cout << "\t最小值：" << (numeric_limits<float>::min)() << endl;

    cout << "type: \t\t" << "************size**************"<< endl;
}


void std_datatype(){
    /*  基本内置基础数据类型：
     *     1. 字符串   char
     *     2. 整数    int
     *     3. 浮点数   float
     *     4. 双浮点数  double
     *     5. 布尔值   bool
     *     6. 无类型   void
     *     7. 宽字符型  wchar_t
     *   以上这些基础数据类型可以使用下面的一个或多个修饰符进行修饰：
     *     1. signed  (int, char)
     *     2. unsigned (int, char)
     *     3. short (int)
     *     4. long  (int, double)
     *     比如：unsigned long int
     *
     */

    // 查看每种字符串的占用字节大小
    // std_datatype_size();

    // 字符串
    char name1;
    char name2[10] = "wangzihao";
    std::cout << "default string = <" << name1 << ">end" << endl;  //"\0"

    // 整数
    int num1;
    int num2 = 2;
    std::cout << "default int = " << num1 << endl;      // 0

    // 浮点数
    float f1;
    float f2 = 1.1;
    std::cout << "default float = " << f1 << endl;      // 0

    // 布尔值
    bool unkonwn;
    bool _true = true;
    bool _false = false;
    std::cout << "default bool = " << unkonwn << endl;      // 0

    // 枚举类型（如果一个变量的值只允许在指定的几个范围内，那么就可以使用枚举，变量初始化的时候，变量值只能在列举出来的值的范围内）
    enum color{
        red = 1,
        blue = 3,
        yellow
    } c;
    c = red;
    std::cout << "c = " << c << endl;       // 1

    c = blue;
    std::cout << "c = " << c << endl;       // 3

    c = yellow;
    std::cout << "c = " << c << endl;       // 4

    enum color c2;      // 也可以先声明，再定义
    c2 = red;
}


void std_typedef(){
    /*  typedef声明
     *      1. 用来给一个已有的类型声明一个新的类型名，没有创造新的类型。
     *      2. typedef 可以声明各种类型名，但不能用来定义变量。用 typedef 可以声明数组类型、字符串类型，使用比较方便
     *      3. 当在不同源文件中用到同一类型数据（尤其是像数组、指针、结构体、共用体等类型数据）时，常用 typedef 声明一些数据类型，
     *         把它们单独放在一个头文件中，然后在需要用到它们的文件中用 ＃include 命令把它们包含进来，以提高编程效率。
     *      4. 使用 typedef 有利于程序的通用与移植
     */

    typedef int count;

    count restart_count;
    count failed_count = 10;
}


void std_bool(){
    // 0 表示假，非 0 表示真，空字符串也是真
    if ("") {
        std::cout << "空字符串布尔值为true" << endl;
    }

    if (!0) {
        std::cout << "非0的值为true" << endl;
    }

    if (0){
        std::cout << "never execute" << endl;
    }
}


void std_c_char(){
    /*  C风格的字符串
     *      概述：c++是支持c语言字符串的，c语言字符串实际上是一个字符数组，这个字符串数组以null字符'\0'结尾，
     *  声明与初始化：
     *      因为这种字符串本质上是一个字符数组，所以我们可以用数据的方式来声明。
     *      比如：
     *          char name[10] = "wangzihao";
     *          char name2[10] = {'w', 'a', 'n', 'g', 'z', 'i', 'h', 'a', 'o'};
     *
     *  相关函数：
     *      c语言提供了很多用来操作这种以null结尾字符串的函数，比如strcpy、strcat等等（见<cstring>库）
     */
    // 长度为10，是因为最后跟着一个 null 字符
    char name1[10] = "wangzihao";       // 可修改的，可以声明为const
    char name2[10] = {'w', 'a', 'n', 'g', 'z', 'i', 'h', 'a', 'o'};

    std::cout << name1 << std::endl;        // wangzihao
    std::cout << name2 << std::endl;        // wangzihao
}


void std_cpp_string(){
    /* c++风格的string
     *      c++提供了自己的字符串 string
     *
     * 特点：
     *      1. 不再以null结尾
     */

    string name1 = "wangzihao";         // 初始化的时候不需要像c字符串一样指定长度
    string name2 = "wzh";

    string name3 = name2;               // 通过赋值来初始化name3，实际上是将name2的值拷贝给name3

    string name4 = name1 + name2;       // 拼接的时候，不用再担心会溢出
}


void std_cpp_array(){
    /* c++ 数组
     *      特点：
     *          1. 存储一个固定大小的相同类型元素的顺序集合。
     *          2. 所有的数组都是由连续的内存位置组成。数组中的元素可以通过下标索引来访问
     * 声明数据：
     *      element_type array_name[array_size]
     *      比如 int nums[10]，用来存储10个整数的数组。
     *      也可以不指定array_size，比如  int nums[]，但是此时必须对其进行初始化，因为如果不初始化，编译器就不知道这个数据类型具体占用多大空间了。
     *      实际上，大小也可以作为数组类型的一种：
     *          比如 int nums[1]和int nums[2]就不是一种类型
     *          而 int nums[10]和int arr[10]就是同一种类型
     *
     *
     */

    int nums1[] = {1, 2, 3};        // 中括号中不指定大小的时候，必须对齐进行初始化

    int nums2[3];                   // 只声明，不初始化
    nums2[0] = 1;
    nums2[0] = 2;

    std::cout << nums2 << std::endl;
    std::cout << &nums2[0] << std::endl;
    assert(nums2 == &nums2[0]);     // 数组变量实际上就是一个指针，指针的值就是数组中第一个元素的内存地址。

    std::cout << nums2[0] << std::endl;

    int nums3[2] = {1, 2};

    // 试试字符串数组
    char *names[3] = {"wangzihao", "wzh", "WZH"};
    assert(names[0] == "wangzihao");

}


void std_cpp_multi_array(){
    /* c++ 多维数组
     *      多维数据本质上还是一个一维数组。c++支持我们声明和创建一个多维数组。
     *
     * 声明格式：
     *      element_type array_name[dim1][dim2]...[dim_n]
     *      element_type是数组中数据的类型
     *      array_name是数组的名称，该变量持有的同样是数组第一个元素的内存地址。
     *      dim1、dim2...dim_n是每一维的大小。
     *
     *      比如：
     *          int arr[4][3]表示声明了一个四行三列，数据类型为int的二维数组。
     *          float arr[4][3][2]表示声明了一个四行三列两页，数据类型为float的三维数组。
     *
     * 初始化：
     *      初始化的时候有两种方式：
     *          一种是按照维度将数据排列成多个数组赋值
     *              int nums[2, 3] = {{1, 2, 3}, {4, 5, 6}}
     *          另一种是直接赋值一个数组，但是这个数组的大小要与声明的大小一致。
     *              int multi_arr2[2][3] = {1, 2 ,3 , 4, 5, 6};
     *
     *              如果大小不一致，则剩余的值会被初始化为，该类型的默认值，比如int就是0。
     *  访问：
     *      访问多维数据也是通过下标索引访问的。每一个中括号中的值，都对应着该维度下的索引位置的数据。
     *
     */

    int multi_arr1[2][3] = {{1, 2, 3}, {4, 5, 6}};

    int multi_arr2[2][3] = {1, 2, 3, 4, 5, 6};

    assert(multi_arr1[0][0] == multi_arr2[0][0]);       // 比较元素的值
    assert(multi_arr1 != multi_arr2);                   // 这样比较的实际上是数组的第一个元素的指针。肯定不相等

    int multi_arr3[2][3] = {1, 2, 3, 4};
    assert(multi_arr3[1][0] == 4);
    assert(multi_arr3[1][1] == 0);
    assert(multi_arr3[1][2] == 0);
}


void std_for(){
    int count = 3;
    int sum = 0;

    for (int i=0;i<=count; i++){
        sum += i;
    }
    std::cout << "sum = " << sum << endl;

    // 死循环，不指定循环条件的时候，默认为true
    for (;;){
        if (count == 15){
            break;
        }
        else if (count == 12) {
            count += 1;
            continue;
        }
        else{
            sum += count;
            count += 1;
        }
    }

    // for循环代码块内部定义的变量，在for代码块之外是没法调用的
    for (int i=1;i<=2;i++){
        int tmp = 0;
    }

    // std::cout << tmp << endl;       // error: Use of undeclared identifier 'tmp'
}


void std_while(){
    int count = 0;

    int sum = 0;
    while (count < 10){
        sum += 1;

        count += 1;
    }
}


void std_do_while(){
    /*  do...while...
     *      与for、while不同的是：do...while保证至少执行一次循环体中的逻辑，执行完一次之后再检查条件是否满足。
     *      而for、while是在执行循环体之前就做一下是否执行循环体代码的判断
    */

    int count = 0;

    do {
        count += 1;
    }while (false);

    assert(count == 1);
}


void std_switch(){
    enum color{red, blue, black, yellow} c;

    c = blue;

    switch (c) {
        case red:
            std::cout << "red" << endl;
            break;
        case blue:
            std::cout << "red" << endl;
            break;
        case black:
            std::cout << "black" << endl;
        case yellow:
            std::cout << "yellow" << endl;
            break;
        default:
            std::cout << "default" << endl;
    }
}


void std_func(){
    /*  函数
     *
     *  注意:
     *      1. C/C++ 编译 cpp 文件是从上往下编译，所以 main 函数里面调用其他函数时，如果其他函数在 main 函数的下面，
     *         则要在 main 函数上面先声明这个函数。
     */
}


// 在文件全局环境中使用static声明的变量只会在该文件的全局环境中生效
static int count = 1;
static void std_local_static_var(){
    static int n = 1;
    std::cout << "static int n = " << n << endl;
    n++;
}


static void std_static_var(){
    /*  static静态变量：
     *      1. static修饰全局变量的时候，这个全局变量只能在本文件中访问，不能在其它文件中访问，即便是在其他文件中使用 extern 外部声明也不可以访问。
     *      2. static修饰函数的时候，该函数只能在本文件中访问。
     *      3. static在一个头文件中声明变量，会为每个包含该头文件的cpp都创建一个全局变量，但他们都是独立的。
     *      4. static修饰静态局部变量的时候，该变量不会在代码块执行结束的时候随着代码块对应栈内存的释放而释放，因为它是存在于全局数据区。
     *              通常，在函数体内定义了一个变量，每当程序运行到该语句时都会给该局部变量分配栈内存。但随着程序退出函数体，系统就会收回栈内存，
     *                  局部变量也相应失效。但有时候我们需要在两次调用之间对变量的值进行保存。
     *              通常的想法是定义一个全局变量来实现。但这样一来，变量已经不再属于函数本身了，不再仅受函数的控制，给程序的维护带来不便。
     *              静态局部变量正好可以解决这个问题。静态局部变量保存在全局数据区，而不是保存在栈中，每次的值保持到下一次调用，直到下次赋新值。
     *              静态局部变量特点：
     *                  1. 该变量在全局数据区分配内存
     *                      * 在局部变量前加上“static”关键字，就成了静态局部变量。静态局部变量存放在内存的全局数据区。函数结束时，静态局部变量不会消失，
     *                        每次该函数调用 时，也不会为其重新分配空间。它始终驻留在全局数据区，直到程序运行结束。静态局部变量的初始化与全局变量类似．
     *                        如果不为其显式初始化，则C++自动为其 初始化为0。
     *                      * 静态局部变量与全局变量共享全局数据区，但静态局部变量只在定义它的函数中可见。静态局部变量与局部变量在存储位置上不同，
     *                        使得其存在的时限也不同，导致对这两者操作 的运行结果也不同。
     *                  2. 静态局部变量在程序执行到该对象的声明处时被首次初始化，即以后的函数调用不再进行初始化（只会初始化一次）
     *                  3. 静态局部变量一般在声明处初始化，如果没有显式初始化，会被程序自动初始化为0
     *                  2. 它始终驻留在全局数据区，直到程序运行结束。但其作用域为局部作用域，当定义它的函数或语句块结束时，其作用域随之结束
     */

    std_local_static_var();         //  1
    std_local_static_var();         //  2
    std_local_static_var();         //  3
    std_local_static_var();         //  4

    // TODO 还需要在深入了解一下，有点乱。
}


int std_func_with_default_params(int a, int increment=1){
    // 自增increment的简单函数
    a += increment;
    std::cout << "a = " << a << endl;
    return a;
}


void std_operator(){
    /* C++运算符
     *      算术运算符
     *          +、-、*、/、%
     *          +=、-=、*=、/=、%=
     *      逻辑运算符
     *          ||  或
     *          &&  与
     *          !   非
     *      关系运算符
     *          ==、!=
     *          >、<
     *          >=、<=
     *      其他运算符
     *          & ：
     *              1. 返回变量的内存地址（即指针的值）
     *              2. 用于声明引用
     *          *：
     *              1. 声明指针，指向一个变量。
     *
     */
}


void std_pragma(){
    Demo obj;

    std::cout << sizeof(obj) << endl;
};


int main() {
/* 头文件
 *  char *s = "111111";
 *  std_declare_func_in_head_file(s);
 */

/*  基础数据类型
 *  std_datatype();
 */

/*  变量命名空间
 *  std_var_scope();
 */

/* 静态局部变量
 *     std_static_var();
 */

/*  循环
 *  std_for();
 *  std_while();
 *  std_do_while();
 */

/*  判断
 *  std_switch();
 */

/*  数据类型大小
    char name[10] = "wangzihao";        // 10，每一个字符占一个字节
    std::cout << "size of char name[10] = " << sizeof(name) << endl;

    std_datatype_size();
    return 0;
*/

/* pragma
    std_pragma();
*/

/* 数组
    std_cpp_array();

*/

    std_cpp_string();
    return 1;
}
