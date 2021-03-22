//
// Created by andrew on 2021/3/21.
//

#include <iostream>
#include <vector>

using namespace std;

// vector容器

/*
 * 将元素置于一个动态数组中加以管理的容器
 * 可以随机存取元素(支持索引存取元素)
 * vector尾部添加元素或者移出元素非常快速，但是在中部或头部插入元素或移除元素比较费时
 * */

/* 基本操作 */
void vector_op() {

    vector<int> v1;
    // 定义的vector为空
    cout << v1.size() << endl;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    cout << "length of v1 = " << v1.size()  << endl;


    // 因为 front 和back返回的是引用，可以直接更改vector里面的元素值
    //    修改头部元素
    v1.front() = 11;
    //    修改尾部元素
    v1.back() = 13;
    for (auto a : v1) {
        cout << a << endl;
    }

    // 插入元素
    v1.insert(v1.begin(), 0);

    while (!v1.empty()) {
        cout << "front = " << v1.front() << "  back = " << v1.back() << endl;
        v1.pop_back();
    }
    cout << "============vector_op ===================" << endl;
}

// vector的初始化
void vector_init() {
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);

    // 使用v1初始化v2
    vector<int> v2 = v1;

    vector<int> v3(v1.begin(),v1.end());

    for (auto a:v2) {
        cout << a << endl;
    }

    for (auto &a:v3) {
        cout << a << endl;
        // 采用应用方式可以更改字符串中的对应自负
        a = 2;
    }
    // 原始遍历
    for (int i = 0; i < v3.size(); ++i) {
        cout <<  v3[i] << endl;
    }

    // 要是想使用赋值的方式进行初始化，需要提前在定义的时候指定大小
    vector<int> v4(10); // 提前把内存分配好
    for (int i = 0; i < 5; ++i) {
        // 要是提前没有指定大小，这里就会崩溃
        v4[i] = i;
    }

    v4.push_back(100);
    v4.push_back(200);
    for (auto k:v4) {
        cout << k ;
    }
    cout << endl;
    cout << "==============vector_init==============" << endl;
}

/*
 * 迭代器， begin是指向第一个元素
 *         end是指向最后一个元素 +1的地方
 *         所以迭代器是 左闭右开 的区间
 * 迭代器的种类
 *
 * */
void vector_insert() {
    vector<int> v1(10);
    for (int i = 0; i < 10; ++i) {
        v1[i] = i + 1;
    }

    for (auto it = v1.begin(); it != v1.end(); it ++) {
        cout << *it << endl;
    }
    // 最好用引用 因为可以省去内存的复制
    for (int & it : v1) {
        cout << it << endl;
    }
    // 逆向遍历容器
    cout << "==reverse==" << endl;

    for (auto it = v1.rbegin(); it != v1.rend();  ++it) {
        cout << *it << endl;
    }
    v1.insert(v1.begin(), 10);
    v1.insert(v1.end(), 200);
    cout << "===vector_insert====" << endl;

}

// vector delete
void vector_delete() {
    vector<int> v1(10);
    for (int i = 0; i < 10; ++i) {
        v1[i] = i + 1;
    }
    // 指定区间删除
    v1.erase(v1.begin(), v1.begin() + 3);

    for (auto & v:v1) {
        cout << v << endl;
    }
    // 指定位置删除
    v1.erase(v1.begin());
    for (auto & v:v1) {
        cout << v << endl;
    }

    v1.push_back(1);
    v1.push_back(1);
    v1.push_back(1);
    // 根据元素的值删除
    for (auto it = v1.begin(); it != v1.end();) {
        if (1 == *it) {
            // 这里会导致it ++, 但是会返回已经踢出对应数据的指针
            it = v1.erase(it);
        } else {
            cout << *it << endl;
        }

    }
}

int main(int argc, char *argv[]) {
    vector_op();
    vector_init();
    vector_insert();
    vector_delete();
    return 0;
}
