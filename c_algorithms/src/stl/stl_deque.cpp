//
// Created by andrew on 2021/3/21.
//
#include <iostream>
#include <string>
// 双端数组头文件
#include <deque>
#include <algorithm>

using namespace std;

/*
 * 双端数组
 *    可以在头部和尾部插入和删除元素
 *    可以用于解决vector只有尾部插入数据删除数据库快，但是其他部位慢的问题
 *
 * */


void deque_push_pop() {
    deque<int> d1;
    // 先在尾部放入三个元素
    d1.push_back(1);
    d1.push_back(2);
    d1.push_back(3);

    // 头部放入数据
    d1.push_front(4);
    d1.push_front(5);
    d1.push_front(6);

    cout << "output d1 value" << endl;
    for (auto &i : d1) {
        cout << i << endl;
    }
    // 弹出元素
    d1.pop_back();
    d1.pop_front();
    // 元素查找
    auto it = find(d1.begin(), d1.end(), 4);
    // 找到了就打印出数组的下标
    if (it != d1.end()) {
        cout << "数组下标是：" << distance(d1.begin(), it)  << endl;
    } else {
        cout << "没有找到值为6的deque" << endl;
    }

}

int main(int argc, char *argv[]) {

    deque_push_pop();
    return 0;
}