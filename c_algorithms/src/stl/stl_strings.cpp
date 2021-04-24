//
// Created by andrew on 2021/3/20.
//
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// 截断区间发现和删除
void find_fro() {
    string s1 = "hello world coder";

    auto a = s1.find('e', 0);
    cout << a << endl;
    // find 返回迭代器的位置
    string::iterator it = find(s1.begin(), s1.end(), 'l');
    if (it != s1.end()) {
        s1.erase(it);
    }

    cout << "s1 删除l之后的结果" << s1 << endl;
    // 字符串转换成之后，指针指向的内容是const 类型的，不能进行更改
    const char* pStr = s1.c_str();

    cout << pStr << endl;
//    删除整个字符串
    s1.erase(s1.begin(), s1.end());
    // 字符串完全删除之后
    cout << "delete all:" << s1.length() << endl;
    // 插入字符串
    s1.insert(0, "aaa");
    cout << "insert aaa:" << s1 << endl;
    cout << "======== find_fro ==========" << endl;
}

void transform_test() {

    string s1 = "AAAbbb";
    char buff[6];
    s1.copy(buff, 5, 0);


    cout << buff << endl;
    // 函数的入口地址
    // 在C++中函数前面强制 加上::代表的意思是使用C语言定义的函数
    transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
    cout << "transform str = " << s1 << endl;

    string s2 = "AAAbbb";
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    cout << "tolower = " << s2 << endl;

    cout << "======== transform_test ========" << endl;
}

int main(int argc, char* argv[]) {


    find_fro();
    transform_test();

    return 0;
}
