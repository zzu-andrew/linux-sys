//
// Created by andrew on 2021/4/24.
//
#include <iostream>

/*
 * 1. 函数模板可以像普通函数一样被重载
 * 2. C++编译器优先考虑普通函数
 * 3. 如果函数模板可以产生一个更好的匹配，那么选择函数模板
 * 4. 可以通过空模板实参裂变的语法限定编译器只能通过模板匹配 mySwap<int, int>
 * */


using namespace std;

template <typename T>
class A {
public:
    explicit A(T &&a) {
        _a = a;
    }

    void showData() {
        cout << " _a = "<< _a << endl;
    }

private:
    T _a;
};

template <typename T>
class B: A<T> {

};

template <typename T>
void useA(A<T> &classA) {
    classA.showData();
}

template <typename T>
void mySwap(T &a, T &b) {
    T tmp;
    cout << "地址" << endl;
    cout << &a << "   " << &b << endl;
    tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
    cout << "地址" << endl;
    cout << &a << "   " << &b << endl;
}

/*
 * 模板函数，和普通函数在一起，优先调用普通函数
 * */
void mySwap(int &a, int  &b) {
    cout << "normal function" << endl;
}

int main(int argc, char*argv[]) {

    int a = 3;
    int b = 4;
    mySwap(a,b);
    cout << a << "   " << b << endl;
    char c = 3;
    char d = 4;
    mySwap(c, d);

    A<int> classA(10);
    useA(classA);

    return 0;
}
