//
// Created by andrew on 2021/3/28.
//
#include <iostream>
#include <map>
#include <string>
using namespace std;
#include <algorithm>
#include <numeric>
#include <functional>

/*
 *  map是标准的关联式容器，一个map是一个键值对序列，即(key，value)对，它日工基于key的快速检索能力
 *  map的key值是唯一的，集合中的元素按照一定的顺序进行排列，元素插入过程是按照排序规则插入，所以不能指定插入位置
 *  map的具体实现采用红黑树的变体平衡二叉树的数据结构，即插入元素和删除元素比vector快
 *  map可以直接存取key所对应的value，支持[]操作符，如map[key] = value
 *  multimap和map的区别：map支持唯一的键值，每个键只能出现一次，而multimap中相同的键可以出现多次，multimap不支持[]操作符
 * */

/*
 * 添加遍历删除操作
 *
 * */
void map_demo() {
    map<int, string> map1;
    // 1. 方法一
    map1.insert(pair<int, string>(1, "stu"));
    map1.insert(pair<int, string>(2, "teacher"));

    // 2.方法二
    map1.insert(make_pair(3, "stu2"));
    // 3.方法三
    map1.insert(map<int, string>::value_type(4, "teacher2"));
    // 4.方法四  因为[]操作符返回的是引用
    map1[5] = "stu3";

    // 容器的遍历
    for (const auto& it : map1) {
        cout << it.first << "  " << it.second << endl;

    }
    auto it = map1.find(100);

    if (it == map1.end()) {
        cout << "查找map 对应的值100失败" << endl;
    }
    // map元素的删除
    while (!map1.empty()) {
        it = map1.begin();
        cout << it->first << " delete " << it->second << endl;
        map1.erase(it);
    }

}

void find_data(const int &count) {
}

int main(int argc, char *argv[]) {

    map_demo();

    return 0;
}

