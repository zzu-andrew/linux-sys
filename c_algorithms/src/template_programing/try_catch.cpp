//
// Created by andrew on 2021/4/24.
//
#include <iostream>
#include <exception>

using  namespace std;

/*
 * 异常的基本语法
 * */

class error : std::exception {
    const char * what() const noexcept override;
};

const char *error::what() const noexcept {
    return exception::what();
}

class construct_test {
public:
    construct_test() {
        cout << "construct test" << endl;
    };
    ~construct_test() {
        cout << "destruct test" << endl;
    }
};

int divide_demo(int x, int y) {

    construct_test constTest;

    if (y == 0) {
        cout << "before throw " << endl;
        // throw之前将所有的栈进行析枸
        throw x; // 抛出 int类型 异常
    }

    cout << "divide y " << x / y << endl;

    return 0;
}

class Student {
public:
    explicit Student(int &&studentAge) {
        if (studentAge > 250) {
            throw out_of_range("age is too big.");
        }
        cout << "construct student" << endl;
        age = studentAge;
    }

    ~Student() {
        cout << "destruct student" << endl;
     }

private:
    unsigned int age{};
};

/*
 * 从标准异常类中进行继承
 * */
class MyException : exception {
public:
    explicit MyException(const char *p) {
        this->m_p = p;
    }
    ~MyException() override = default;
    virtual const char* what() {
        cout << "MyException " <<  m_p << endl;
        return m_p;
    }

private:
    const char *m_p{};
};

void TestMyException() {
    throw MyException("func exception");
}

/*
 *  构造函数中没有返回值，也通常需要通过异常来处理构造函数中的异常
 * */

int main(int argc, char*argv[]) {

    try {
        // 1.将可能引起异常的代码放到try的地方
        divide_demo(10, 2);
        divide_demo(10, 0);
    }
    catch (int e) {
        cout << "after throw" << endl;
        cout <<  "e = " << e << endl;
    } // ... 是其他未知类型的异常
    catch (...) {

    }

    /*
     *  使用标准异常
     * */
    try {
        Student student(300);
    }
    catch (out_of_range &eOut) {
        cout <<  eOut.what() << endl;
    }

    try {
        TestMyException();
    }
    catch (MyException &exceptData) {
        exceptData.what();
    }
    catch (...) {
        cout << "unknow  error" << endl;
    }

    return 0;
}
