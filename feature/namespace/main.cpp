#include <iostream>
using namespace std;

// namespace只能在全局或者其他namespace中定义
namespace n1{
    int a = 1;
}


namespace n2{
    int a = 2;
}


void std_namespace(){
    using namespace n1;
    std::cout << "n1::a = " << a << std::endl;

    using n2::a;
    std::cout << "n2::a = " << a << std::endl;
    std::cout << "n1::a = " << n1::a << std::endl;
}

int main() {
/*  名称空间
    int a = 3;
    std_namespace();
    //局部命名空间中调用using namespace xxx 或者using xxx::var，只会在该局部环境中生效，并且会覆盖掉上层命名空间中的内容。
    std::cout << "global::a = " << a << std::endl;
*/
}