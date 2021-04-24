//
// Created by andrew on 2021/3/31.
//
#include <iostream>
#include <list>
#include <mutex>
#include <algorithm>
#include <stack>

/*
 *
struct empty_stack: std::exception
{
    // throw() 表示函数不能抛出异常， throw(...)表示函数可以抛出任何形式的异常
    // throw(exceptionType)表示函数只能抛出exceptionType类型的异常
    const char* what() const noexcept override
    {
        return "empty stack";
    }

};
 *
 *
 * */

using namespace std;

// 声明一个却局链表
list<int> g_list;
// 声明一个互斥锁用于保护全局链表数据
mutex list_mutex;


void push_data_to_list(int newValue) {
//    每次进来创建guard， 构造函数中会调用全局锁，在该函数退出的时候会自动调用析构函数实现
// 锁的释放
    lock_guard<std::mutex> guard(list_mutex);
    g_list.push_back(newValue);
}

bool find_list_data(int valueData) {
    lock_guard<mutex> guard(list_mutex);
    return find(g_list.begin(), g_list.end(), valueData) != g_list.end();
}


// C++左值和右值
void left_data(int &&data) {
    cout << "right data = " << data << endl;
}

void left_data(int &data) {
    cout << "left data = " << data << endl;
}

int main(int argc, char * argv[]) {

    // 1 是右值只能调用 && 右值引用
    left_data(1);
    int i= 0;
    left_data(i);
    push_data_to_list(42);
    cout << "find 1 = " << find_list_data(1) << "    find 42 = " << find_list_data(42) << endl;
    return 0;
}
