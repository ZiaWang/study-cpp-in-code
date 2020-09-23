#include <iostream>

using namespace std;

/* 程序异常分类：
 *      1. 语法错误：语法错误在编译和链接阶段就能发现，只有 100% 符合语法规则的代码才能生成可执行程序。语法错误是最容易发现、
 *         最容易定位、最容易排除的错误，程序员最不需要担心的就是这种错误。
 *      2. 逻辑错误：逻辑错误是说我们编写的代码思路有问题，不能够达到最终的目标，这种错误可以通过调试来解决。
 *      3. 运行时错误：运行时错误是指程序在运行期间发生的错误，例如除数为 0、内存分配失败、数组越界、文件不存在等。
 *         C++ 异常（Exception）机制就是为解决运行时错误而引入的。
 *
 *         运行时错误如果放任不管，系统就会执行默认的操作，终止程序运行，也就是我们常说的程序崩溃（Crash）。C++ 提供了异常（Exception）机制，
 *         让我们能够捕获运行时错误，给程序一次“起死回生”的机会，或者至少告诉用户发生了什么再终止程序。
 *
 *  try .... catch....
 *      格式：
 *          try{
 *              do something
 *          }
 *          catch (error_type1 error_var1){
 *              do something
 *          }
 *          catch (error_type2 error_var2){
 *              do something
 *          }
 *
 *       异常类型error_type：指明了当前的 catch 可以处理什么类型的异常
 *       异常变量error_var：一个变量，用来接收异常信息，可以看作是异常类型的一个实例。当程序抛出异常时，会创建一份数据，这份数据包含了错误信息，而这份数据就是这个实例对象。
 *
 *  异常类型可以有哪些？
 *      异常类型可以是 int、char、float、bool 等基本类型，也可以是指针、数组、字符串、结构体、类等聚合类型。
 *      C++ 语言本身以及标准库中的函数抛出的异常，都是 exception 类或其子类的异常。也就是说，抛出异常时，会创建一个 exception 类或其子类的对象。
 *
 *  catch:
 *      当异常发生后，会将异常数据传递给 variable 这个变量，这和函数传参的过程类似。当然，只有跟 exceptionType 类型匹配的异常数据才会
 *      被传递给 variable，否则 catch 不会接收这份异常数据，也不会执行 catch 块中的语句
 *      catch和真正的函数调用相比，多了一个"在运行阶段将实参和形参匹配"的过程。
 *          对于 catch，异常是在运行阶段产生的，它可以是任何类型，没法提前预测，所以不能在编译阶段判断类型是否正确，只能等到程序运行后，
 *          真的抛出异常了，再将异常类型和 catch 能处理的类型进行匹配，匹配成功的话就“调用”当前的 catch，否则就忽略当前的 catch。
 *      如果不希望 catch 处理异常数据，也可以将 variable 省略掉，即：
  *         try{
 *              do something
 *          }
 *          catch (error_type){ // 这种情况下，只会将异常类型和 catch 所能处理的类型进行匹配，不会传递异常数据了（即变量对应的异常对象）
 *              do something
 *          }
 *
 */

void std_catch_err(){
    string s = "wangzihao";

    try {
        char sub_s = s[100];
    }catch (std::exception &e) {
        std::cout << "err 1" << std::endl;
    }

    try {
        char sub_s2 = s.at(100);
    }catch (std::exception &e) {
        std::cout << "err 2" << std::endl;
    }
}


void std_catch_err2(){
    // 发现有些时候，catch补货不了某些异常
    string s = "wangzihao";

    try {
        char sub_s = s[10000000000000000];
    }catch (std::exception &e) {
        std::cout << "err 1" << std::endl;
    }

    // 索引太大的时候，程序就会直接退出，catch竟然没有捕获到异常，走不到下面这行代码了
    std::cout << "asddasd" << std::endl;
}


/* 异常类
 *      c++中，所有的异常类都应该继承自 exception类。
 *
 * 自定义异常类: 使用继承即可。
 *
 * c++中的内置异常：
 *      logic_error	逻辑错误。
 *      runtime_error	运行时错误。
 *      bad_alloc	使用 new 或 new[ ] 分配内存失败时抛出的异常。
 *      bad_typeid	使用 typeid 操作一个 NULL 指针，而且该指针是带有虚函数的类，这时抛出 bad_typeid 异常。
 *      bad_cast	使用 dynamic_cast 转换失败时抛出的异常。
 *      ios_base::failure	io 过程中出现的异常。
 *      bad_exception	这是个特殊的异常，如果函数的异常列表里声明了 bad_exception 异常，当函数内部抛出了异常列表中没有的异常时，如果调用的 unexpected() 函数中抛出了异常，不论什么类型，都会被替换为 bad_exception 类型。
 */


class BaseError: public exception{};
class BadRequest: public BaseError{};




/* 抛出异常
 *      类似python中的raise，c++中我们也可以主动抛出异常，使用关键字"throw"即可
 *
 * 格式：
 *      throw ExceptionData。
 *      ExceptionData可以是 int、float、bool 等基本类型，也可以是指针、数组、字符串、结构体、类等聚合类型
 *
 */
void std_throw_err(){
    try {
        // 建议抛出exception的子类
        throw BadRequest();
        // throw "Bad Request";         // 也可以抛出字符串、整数等
        // throw 1;
    }
    catch (int e) {
        std::cout << "error code: " << e << std::endl;
    }
    catch (const char *e) {
        std::cout << e << std::endl;
    }
    catch (BaseError) {
        // throw BadRequest()会因为"向上转型"，被这块代码catch到。或者说子类异常是可以被父类catch到的
        std::cout << "catch : BaseError" << std::endl;
    }
    catch (BadRequest &e) {
        std::cout << "catch : BadRequest" << std::endl;
    }
}


void std_err_change_up(){
    // 异常向上转型
    int nums[3] = {1, 2, 3};

    try {
        throw nums;
    }
    // int[] 会被向上转型为 int *，在被转型成 const int *
    catch (const int *) {
        std::cout << "catch const int *" << std::endl;
    }
    catch (int[]) {
        std::cout << "catch int[]" << std::endl;
    }
}


class OutOfRange{
public:
    void what() const;

    OutOfRange():m_code(1){};
    OutOfRange(int len, int idx):m_len(len), m_idx(idx), m_code(2){};

private:
    int m_code;
    int m_len;
    int m_idx;
};

void OutOfRange::what() const {
    if (m_code == 1){
        std::cout << "OutOfRange, empty array" << std::endl;
    } else if(m_code == 2){
        std::cout << "OutOfRange, len = " << m_len << ", idx = " << m_idx << std::endl;
    } else{
        std::cout << "OutOfRange, unknown error" << std::endl;
    }
}

void std_throw_obj(){
    try {
        throw OutOfRange();
    } catch (OutOfRange obj) {
        obj.what();             // OutOfRange, empty array
    }

    try {
        throw OutOfRange(10, 100);
    } catch (OutOfRange obj) {
        obj.what();             // OutOfRange, len = 10, idx = 100
    }
}

int main() {
    std_throw_obj();
    return 0;
}
