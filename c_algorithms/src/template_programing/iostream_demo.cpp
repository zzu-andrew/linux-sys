//
// Created by andrew on 2021/4/25.
//
#include <iostream>
#include <fstream>

using namespace std;

/*
 * cin.get() 一次只能获取一个字符
 * cin.get(一个参数) 读取一个字符
 * cin.get(三个自负) 可以读取字符串
 * cin.getline()获取一行字符
 * cin.ignore()
 * cin.peek()
 * cin.putback()
 * */

int main(int argc, char *argv[]) {

    char a,b,c;
    cin.get(a).get(b).get(c);
    cout << a << b << c << endl;

    // 使用文件流创建文件
    const char* fileName = "./1.txt";
    ofstream fileOut(fileName);

    fileOut << "test" << endl;

    fileOut.close();
    return 0;
}
