#include <iostream>
using namespace std;

/* namespace
 * 用来解决什么问题？
 *    * 命名冲突（c语言中，所有的全局标识符是共享了一个作用域，因此标识符之间会存在命名冲突）
 *
 * 相关细节：
 *    1. 将全局作用域区分为不同的部分。
 *    2. 不同命名空间中，相同的标识符不会发生冲入
 *    3. 命名空间可以嵌套（比如namespace中可以定义其他namespace）
 *    4. 全局命名空间实际上是默认的一个namespace，即默认命名空间。
 *
 * 使用：
 *    使用整个命名空间：
 *          using namespace std;
 *
 *    使用命名空间中指定的变量来覆盖当前默认空间的变量：
 *          using using boost::shared_ptr;
 *
 *    使用默认命名空间中的变量：
 *          ::var_name
 *
 *
 *
 */


const char *a = "default namespace";



// namespace只能在全局或者其他namespace中定义
namespace n1{
    const char *a = "namespace n1";
}


namespace n2{
    const char *a = "namespace n2";
}


void std_namespace(){
    cout << "a =  " <<  a << endl;          // a = default namespace
    cout << "::a =  " <<  ::a << endl;      // ::a = default namespace

    cout << "n1::a = " << n1::a << endl;    // n1::a = namespace n1

    cout << "n2::a = " << n2::a << endl;    // n2::a = namespace n2

    using n1::a;
    cout << "a =  " <<  a << endl;          // a = n1

    cout << "::a =  " <<  ::a << endl;          // a = default namespace
}

int main() {
    std_namespace();
}