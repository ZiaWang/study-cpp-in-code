#include <iostream>

using namespace std;

void std_ref_define(){
    int a = 1;
    int &b = a;

    std::cout << "a = " << a << endl;       // 1
    std::cout << "b = " << b << endl;       // 1

    b = 2;

    std::cout << "a = " << a << endl;       // 2
    std::cout << "b = " << b << endl;       // 2
}


void std_ref_init(){
    // 引用必须在定义的同时初始化
    // int &b;     // error: declaration of reference variable 'b' requires an initializer

    // 引用初始化之后，不能再引用其它数据，这有点类似于常量（const 变量）。
    int a = 1;
    int &c = a;

    int d = 2;
    // &c = d;     //  error: expression is not assignable

    c = d;         // 相当于将d的值赋值给了c，这样做是可以的。
}


void swap_val_(int a, int b){
    // a和b都是一份拷贝，因此只能交换函数命名空间的a、b，不能修改global中的a、b
    int tmp = a;
    a = b;
    b = a;
}


void swap_ptr_(int *a, int *b){
    // a和b都是指针，*a、*b是指针指向的内存中的值，因此修改*a、*b，可以修改global中的a、b
    int tmp = *a;
    *a = *b;
    *b = *a;
}


void swap_ref_(int &a, int &b){
    // a和b都是引用，即对传入的原变量的一个引用，他俩只想的是同一个内存空间，因此修改a、b的值，实际上就是修改原变量的值。
    int tmp = a;
    a = b;
    b = a;
}


void std_ref_params(){
    // 传值
    int a = 1, b = 2;
    swap_val_(a, b);

    //  传指针
    swap_ptr_(&a, &b);

    // 传引用
    int c = 1, d = 2;
    int &m = c;
    int &n = d;
    swap_ref_(m, n);
}


void std_reference_base(){
    /*  引用：
     *      1. 参数的传递本质上就是一个赋值的过程，将实参拷贝到形参身上，本质上就是一次内存拷贝。
     *      2. 引用功能类似指针，它可以看作是指向数据的一个别名，这个别名和数据的变量名都指向了内存中的同一份数据。
     */
    std_ref_define();

    /*  注意：
     *      1.引用必须在定义的同时初始化，并且以后也要从一而终，不能再引用其它数据，这有点类似于常量（const 变量）。
     *      2. 引用在声明和初始化的时候，需要使用&符号，但是在使用变量的时候，是不需要再加&符号的，这个需要跟指针区分开。。
     */
    std_ref_init();
    std_ref_params();
}


void display_array(int arr[5]){
    for (int i=0; i<5; i++){
        std::cout << "idx: " << i << " val: " << arr[i] << endl;
    }
}


void std_cpp_array_params(int nums[5]){
    // 注意，这里参数不能变成 "int &nums[5]", 因为c++会自动的将nums数组的地址作为参数传入，再加上&的化就错误了。（可以使用指针的）
    std::cout << "local &nums = " << &nums << endl;
    display_array(nums);
    nums[0] = 0;
    display_array(nums);
}


void std_cpp_array_params(int *nums[5]){
    // 使用指针
    std::cout << "local &nums = " << &nums << endl;
    display_array(*nums);
    *nums[0] = 0;
    display_array(*nums);
}


/*
 * void std_cpp_array_params(int &nums[5]){
 *   // error 'nums' declared as array of references of type 'int &'
 *   std::cout << "local &nums = " << &nums << endl;
 *   display_array(*nums);
 *   *nums[0] = 0;
 *   display_array(*nums);
 * }
 */


int main() {
    /*  引用基本内容
     *  std_reference_base()
     */

    /*
     *  函数传数组时，是传值还是传引用（结论：传引用）
     *
     *  int _nums[5] = {1, 2, 3, 4, 5};
     *  std::cout << "global &nums = " << &_nums << endl;
     *
     *  std_cpp_array_params(_nums);
     *
     *  display_array(_nums);
     */

    /*  函数使用引用和指针
     *  std_ref_params();
     */
    return 0;
}
