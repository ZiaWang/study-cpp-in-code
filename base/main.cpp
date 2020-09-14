#include <iostream>
using namespace std;

/*
 * 基础语法
 *      输入与输出
 *      变量定义
 *      逻辑处理
 *      流程控制
 *      等等。。。。。
 */

void std_cin_cout(){
    // http://c.biancheng.net/view/2194.html
    // 标准输出，count后面跟多个 "<<"，会将这些字符串拼接起来输出到标准输出
    std::cout << "hello" << " " << "world" << std::endl;

    // 标准输入
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
    // 变量声明不像C语言一样，严格要求在函数起始处声明，C++中只要在初始化变量之前声明即可
    std::cout << "不在函数起始位置声明变量" << std::endl;
    int num1, num2 = 2;
    num1 = num2 + 1;
    std::cout << "num1 = " << num1 << endl;

    // 这个好处是可以让我们在for循环等代码块中声明变量了
    for (int i=1; i<=3; i++){
        std::cout << "i = " << i << endl;
    }
    // 在for循环外部，i变量的值就无法获得的，这里编译main.cpp文件的时候会抛出异常
//    std::cout << "try get i = " << i << endl;       // error: use of undeclared identifier 'i'
}

void std_datatype(){
    // 字符串
    string name1;
    string name2 = "wangzihao";
    std::cout << "default string = <" << name1 << ">end" << endl;  //""空字符串

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
}

int std_func_with_default_params(int a, int increment=1){
    // 自增increment的简单函数
    a += increment;
    std::cout << "a = " << a << endl;
    return a;
}

int main() {
    std_func_with_default_params(1, 2);
    return 0;
}
