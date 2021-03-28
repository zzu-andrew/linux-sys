//
// Created by andrew on 2021/3/23.
//
#include <iostream>
#include <queue>

using namespace std;

/*
 * 一个有优先级的queue
 * */
void priority_queue_init() {
    // 由大到小 队列头最大
    priority_queue<int> q1; // 默认是情况下是最大优先级队列
    // 相当于
    priority_queue<int, vector<int>, less<int>> q2; // 提前定义好预定义函数
    // 有小到大，队列头最小
    priority_queue<int, vector<int>, greater<int>> q3;
    // 测试数据添加
    q1.push(33);
    q1.push(11);
    q1.push(55);
    q1.push(22);

    // 虽然 55 是最后push的但是因为55最大所以在队列头上
    cout << q1.top() << endl;

    while (!q1.empty()) {
        cout << "q1 pop = " << q1.top() << endl;
        q1.pop();
    }
    // 测试数据添加
    q3.push(33);
    q3.push(11);
    q3.push(55);
    q3.push(22);

    // 虽然 55 是最后push的但是因为55最大所以在队列头上
    cout << q3.top() << endl;

    while (!q3.empty()) {
        cout << "q3 pop = " << q3.top() << endl;
        q3.pop();
    }
}

int main(int argc, char* argv[]) {

    priority_queue_init();
    return 0;
}
