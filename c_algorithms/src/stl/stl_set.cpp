//
// Created by andrew on 2021/3/23.
//
#include <iostream>
#include <set>
#include <random>

extern "C" {
#include <cstdlib>
#include <cstring>
}

using namespace std;

/*
 *  set是一个容器，其中所包含的元素是唯一的，集合中的元素按一定的顺序排列，元素插入的过程是按排序规则插入，所以不能指定插入的位置
 *  set的红黑树的变体的数据结构实现，红黑树属于平衡二叉树，在插入和删除操作上比vector快
 *  set不可以直接取元素(不可以使用at.(pos)与[]操作符)
 *  multiset与set的区别：set支持唯一键值，每个元素值只能出现一次，而multiset中同一值可以出现多次
 *  不可以直接修改set或multiset容器中的元素值，因为该容器是自动排列顺序的，如果希望修改一个元素必须先删除原有的元素，在插入新的元素=
 * */
int gen_random(int num)
{
    std::random_device rd;     //Get a random seed from the OS entropy device, or whatever
    std::mt19937_64 eng(rd()); //Use the 64-bit Mersenne Twister 19937 generator
    std::uniform_int_distribution<unsigned long long> distr(1, num);// distribution in range [1, num]
    return distr(eng);
}

/*
 *  集合，元素唯一，自动排序，不能按照[]方式插入元素
 *  底层是红黑树实现
 * */
/*
 *  默认情况下是从小到大
 * */
void set_init() {
    set<int> set1; // ==> set<int, less<int>> set1;

    for (int i = 0; i < 5; ++i) {
        int tmp = gen_random(19856);
    // cout << tmp << endl;
        set1.insert(tmp);
    }

    // 元素唯一，并且自动排序

    set1.insert(100);
    set1.insert(100);
    set1.insert(100);

    for (auto it:set1) {
        cout << it << endl;
    }
    // 找不到时会发生什么？
   /* auto it = set1.find(111);
    cout << *it << endl;*/

    while (!set1.empty()) {
       set1.erase(set1.begin());
    }
    cout << "==============less set==============" << endl;
}

void set_reverse() {
    // 这样设置之后排序方式就是从大到小
    set<int, greater<int>> set1;
    for (int i = 0; i < 5; ++i) {
        int tmp = gen_random(19856);
        // cout << tmp << endl;
        set1.insert(tmp);
    }

    // 元素唯一，并且自动排序
    set1.insert(100);
    set1.insert(100);
    set1.insert(100);
    
    for (auto it:set1) {
        cout << it << endl;
    }
    cout << "============== greater set =============" << endl;
}

class Teacher {
public:
    Teacher(const char *name, int age) {
        ::strcpy(this->name, name);
        this->age = age;
    }

    void teacher_show() {
        cout << this->name << "  ";
        cout << this->age  << endl;
    }
public:
    char name[64]{};
    int age{};
};

// 仿函数 --  通过重载 ()操作符实现仿函数
// 真实是个类但是能像函数一样进行调用
struct FuncTeacher {
    // less 首个元素小于后面的就直接返回true
    bool operator()(const Teacher &left, const Teacher &right) {
        if (left.age < right.age) {
            return true;
        } else {
            return false;
        }
    }
};

void set_teacher() {
    set<Teacher, FuncTeacher> set1;

    Teacher t1("s1", 32);
    Teacher t2("s2", 25);
    Teacher t3("s3", 26);
    Teacher t4("s4", 33);

    set1.insert(t1);
    set1.insert(t2);
    set1.insert(t3);
    set1.insert(t4);

    for (auto it : set1) {
        it.teacher_show();
    }

    for (auto it : set1) {
        cout << it.name << "  " << it.age << endl;
    }
    cout << "============== Teacher show ===============" << endl;
}

int main(int argc, char* argv[]) {
    set_init();
    set_reverse();
    set_teacher();
    return 0;
}
