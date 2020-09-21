#include <iostream>

template<typename T> void swap(T *a, T *b){
    T tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}


template<typename T> T max(T &a, T &b, T &c){
    T _max = a;

    if (b > _max){
        _max = b;
    }

    if (c > _max){
        _max = c;
    }

    return _max;
}


template<typename T1, typename T2>
class Point{
public:
    T1 m_x;
    T2 m_y;

    Point(T1 x, T2 y): m_x(x), m_y(y){};

    void show(){
        std::cout << "m_x: " << m_x << std::endl ;
        std::cout << "m_y: " << m_y << std::endl ;
    }
};



void std_template(){
    int _max;
    int a = 1;
    int b = 2;
    int c = 3;

    _max = max(a, b, c);

    std::cout << "_max = " << _max << std::endl;

}





int main() {
    std_template();

    return 0;
}
