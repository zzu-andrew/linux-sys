//
// Created by andrew on 2021/3/22.
//
#include <iostream>
#include <queue>

using namespace std;

void queue_init() {
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    cout << "queue front " << q.front() << endl;
    cout << "queue size " << q.size() << endl;

    while (!q.empty()) {
        cout << q.front() << endl;
        // 数据弹出队列
        q.pop();
    }
}

int main(int argc, char* argv[]) {

    queue_init();

    return 0;
}
