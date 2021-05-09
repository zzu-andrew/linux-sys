//
// Created by andrew on 2021/4/5.
//

#include <iostream>
#include <map>
#include <random>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
#include <vector>
#include <memory>


using namespace std;


// 函数对象
/*
 * 类重载了 ()
 * */
template<typename T>
class ShowElem {
public:
    void operator()(const T &t) {
        cout << t << endl;
    }
};

bool IsOdd(int data) {
    return data % 2;
}

void for_each_test() {
    vector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(3);
    vec1.push_back(5);

    for_each(vec1.begin(), vec1.end(), ShowElem<int>()); // 在不是对象的时候就是匿名仿函数

    auto it = find_if(vec1.begin(), vec1.end(), IsOdd);
//    查找到一个就会停止
    cout << "*it is Odd =" << *it << endl;
}

class IsGreat {
public:
    explicit IsGreat(int i) {
        m_num = i;
    }

    bool operator()(int &num) {
        if (num > m_num) {
            return true;
        }
        return false;
    }

private:
    int m_num{};
};

class IsGreat2 {
public:
    bool operator()(int &num) {
        if (num > 2) {
            return true;
        }
        return false;
    }

};

// 函数适配器综合案例
void vector_adaptor() {
    vector<int> v1;
    v1.reserve(11);
    for (int i = 0; i < 10; ++i) {
        v1.push_back(i + 1);
    }

    v1.push_back(3);
    // 迭代器计数，统计当前迭代器有多少符合的值
    int num = count(v1.begin(), v1.end(), 3);
    cout << "num = " << num << endl;

    // 条件统计， 通过谓词求大于2的个数 有谓词的需要填入谓词
    int count = count_if(v1.begin(), v1.end(), IsGreat(2));
    cout << "count = " << count << endl;

    // 通过预定义对象求大于2的个数
    // greater<int>() 有两个参数，左参数来自容器的元素，右参数固定成2 通过bind2nd做的
    int num3 = count_if(v1.begin(), v1.end(), bind2nd(greater<int>(), 2));
    cout << num3 << endl;

    // 求奇数的个数 modulus 对第二个数求
    int num4 = count_if(v1.begin(), v1.end(), bind2nd(modulus<int>(), 2));
    cout << "num4 = " << num4 << endl;
    // 求偶数的个数

    int num5 = count_if(v1.begin(), v1.end(), not1(bind2nd(modulus<int>(), 2)));
    cout << "num4 = " << num5 << endl;

}

void show_element(int ele) {
    cout << ele << endl;
}

int increase(int i) {
    return i + 1;
}

bool GreatThree(int iNum) {
    return iNum > 3;
}

// 常用算法函数示例
void stl_algorithm() {
    vector<int> v1;
    v1.reserve(10);
    v1.insert(v1.begin(), 1);
    for (int i = 0; i < 10; ++i) {
        v1.push_back(i + 1);
    }
    //    函数对象 或者回调函数的入口地址
    for_each(v1.begin(), v1.end(), show_element);

    //  transform
    //
    //    vector<int> v2;
    transform(v1.begin(), v1.end(), v1.begin(), increase);

    // 查找相邻元素  两个相邻元素相等就返回对应的迭代器的位置
    auto it = adjacent_find(v1.begin(), v1.end());
    if (it == v1.end()) {
        cout << "can not find increase" << endl;
    } else {
        cout << *it << endl;
    }

    int index = distance(v1.begin(), it);
    cout << "index = " << index << endl;

    // 二分查找
    bool b = binary_search(v1.begin(), v1.end(), 7);
    if (b) {
        cout << "find = " << b << endl;
    } else
        cout << "not find " << endl;

    // 统计某个值的个数
    int num = count(v1.begin(), v1.end(), 2);
    cout <<  "num = " << num << endl;

    int num2 = count_if(v1.begin(), v1.end(), GreatThree);
    cout << "great three = " << num2 << endl;

    it = std::find(v1.begin(), v1.end(), 7);
    cout << "*it = " << *it << endl;

    // 排序算法
    // 合并两个有序的序列 merge
    vector<int> v2;
    v2.push_back(2);
    v2.push_back(4);
    v2.push_back(6);
    vector<int> v3;
    v3.resize(v1.size() + v2.size());
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());

    for (auto &ait:v3) {
        cout << ait << endl;
    }

    //     sort函数
    sort(v1.begin(), v1.end());
    // random_shuffle 随机排序 函数在C++ 17中移除 替代函数shuffle
    shuffle(v1.begin(), v1.end(), std::mt19937(std::random_device()()));

    //  进行逆序处理
    reverse(v1.begin(), v1.end());

    // 拷贝和替换算法
    vector<int> v4;
    v4.resize(v1.size());
    copy(v1.begin(), v1.end(), v4.begin());
    for (auto ait:v4) {
        cout << ait << endl;
    }
    // 替换 将迭代器中所有的3替换成8
    replace(v1.begin(), v1.end(), 3, 8);
    // 将大于5的元素都替换为4
    replace_if(v1.begin(), v1.end(), [&](int &n) { return n > 5; }, 4);
    cout << "==========" << endl;
    for (auto ait:v1) {
        cout << ait << endl;
    }
    // 交换
    swap(v1, v4);

    // 累加函数
    int tmp = accumulate(v1.begin(), v1.end(), 100);
    cout << tmp << endl;

    // fill填充 使用迭代器将对应的vector填充指定值
    fill(v1.begin(), v1.end(), 8);


}

void union_demo() {
    // 并集 交集 差集
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(5);

    vector<int> v2;
    v2.resize(v1.size());
    copy(v1.begin(), v1.end(), v2.begin());
    v1.insert(v1.begin(), 2);

    // v3拿出来
    vector<int> v3;
    v3.resize(v1.size() + v2.size());
    set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
    cout << "------------------------" << endl;
    for (auto &it:v3) {
        cout << it << endl;
    }


}


int main(int argc, char *argv[]) {

//    函数对象的执行
    ShowElem<int> showData;
    showData(10); // 定义成对象时，是仿函数而 直接用类调用是匿名仿函数ShowElem<int>()

    // 函数的遍历
    for_each_test();

    vector_adaptor();
    // 常用stl算法使用示例
    stl_algorithm();

    union_demo();

    return 0;
}