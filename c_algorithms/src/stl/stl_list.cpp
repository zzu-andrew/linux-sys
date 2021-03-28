//
// Created by andrew on 2021/3/22.
//
#include <iostream>
#include <list>

using namespace std;

/*
 * list 是一个双向链表容器，可以高效进行数据的插入和删除操作
 * list 不可以随机存取数据(因为是链表)，所以不支持at.(pos)函数和[]操作符 可以it++但是不能it+5
 * */

/*
 *  list指定位置插入元素的含义
 *
 *  list删除操作是 [0, 3)左闭又开的
 * */

/*
 * 在几号位置插入元素，就把元素放到几号位置
 * */

void list_init() {
    list<int> l;
    cout << "list size " << l.size() << endl;

    for (int i = 0; i < 10; ++i) {
        l.push_back(i);
    }
    cout << "pushed list size " << l.size() << endl;
    auto it = l.begin();
    while (it != l.end()) {
        cout << *it << endl;
        it++;
    }
    cout << "================ insert test ===============" << endl;
    it = l.begin();
    it ++;
    it ++;
    it ++;
//    it = it + 5; // 报错
    /*
     * 在几号位置插入元素，就把元素放到几号位置
     * */
    l.insert(it, 100);  // 前面进行了三次 ++ 这里的insert插入到了哪里？是3位置前面还是后面
    for (auto q:l) {
        cout << q << endl;
    }

    // 删除的时候是左闭右开
    // list.clear(); 删除容器中的所有数据
    // list.erase(beg, end); 删除容器中[beg, end)区间内的数据
    // list.erase(pos); 删除pos位置的数据，返回下一个数据的位置
    // list.remove(elem); 删除容器中所有值与elem相等的元素

    l.erase(l.begin(), l.begin()++);
}

int main(int argc, char* argv[]) {

    list_init();
    return 0;
}
