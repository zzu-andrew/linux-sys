//
// Created by andrew on 2021/3/22.
//
#include <iostream>
#include <string>
// 先进后出栈
#include <stack>

using namespace std;

void stack_init() {
    stack<int> sta;
    // 数据入栈
    for (int i = 0; i < 10; ++i) {
        sta.push(i);
    }
    // 数据出栈
    while (!sta.empty()) {
        // 获取栈顶元素
        int top = sta.top();
        cout << top << endl;
        sta.pop(); // 将栈顶元素弹出
    }
    cout << "========= stack_init =========" << endl;
}

// teacher
class Teacher {
public:
    int age;
    char name[10];
public:
    void show_status() {
        cout << name << "    " << age << endl;
    }
};

void stack_teacher() {
    Teacher t1{31, "小红"};
    Teacher t2{32, "小花"};
    Teacher t3{33, "小明"};

    stack<Teacher> stackTeacher;
    stackTeacher.push(t1);
    stackTeacher.push(t2);
    stackTeacher.push(t3);

    while (!stackTeacher.empty()) {
        Teacher tmp = stackTeacher.top();
        tmp.show_status();
        stackTeacher.pop();
    }
    cout << "========== stack_teacher ==========" << endl;
}

int main(int argc, char *argv[]) {

    stack_init();
    stack_teacher();

    return 0;
}