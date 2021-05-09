//
// Created by andrew on 2021/4/24.
//
#include <iostream>



using namespace std;

/*
 *

`C`风格的类型转换

`C++`风格的类型转换，提供了4种类型操作符来应对不同场合的应用

`static_cast` 静态类型转换，如`int`转换为`char`

`reinterpreter_cast` 重新解释类型

`dynamic_cast`  命名上理解是动态类型转换，如子类父类之间多态类型转换

`const_cast` 字面上就是去`const`属性
 *
 * */


void convert_demo() {
    double dpi = 3.1415926;

    /* C风格的强制类型转换 */
    int num1 = (int) dpi;
    /* C++风格的强制类型转换 */
    int num2 = static_cast<int>(dpi);
    cout << "num2 = " << num2 << endl;

    /*
    * 如果我们不想修改const变量的值，那我们又为什么要去const呢？
   原因是，我们可能调用了一个参数不是const的函数，而我们要传进去的实际参数确实const的，
    但是我们知道这个函数是不会对参数做修改的。于是我们就需要使用const_cast去除const限定，以便函数能够接受这个实际参数。*/
    const int a=10;
    int *p = const_cast<int*>(&a);	//p和a指向同一块内存地址
    *p = 100;	//修改*p，但a=10，*p=100
    cout << p << "  " << &a << endl;
    cout << *p << "  " << a << endl;
}

void const_convert(const char * p) {
    // char *p
    // 转换为非const之后，要程序员保证数据指向的内容是能够进行修改的，否则将会导致直接的崩溃
    cout << "======================" << endl;
    char *p1 = const_cast<char *>(p);
    p1[0] = 'Z';
    cout <<  " ======= "  << p << endl;
}



int main(int argc, char* argv[]) {

    convert_demo();

    const char buf[] = "name_test";
    const_convert(buf);

    return 0;
}


