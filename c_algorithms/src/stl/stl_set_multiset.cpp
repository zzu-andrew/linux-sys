//
// Created by andrew on 2021/3/23.
//
#include <iostream>
#include <set>
#include <random>

extern "C" {
#include <cstdlib>
}

using namespace std;

int gen_random(int num)
{
    std::random_device rd;     //Get a random seed from the OS entropy device, or whatever
    std::mt19937_64 eng(rd()); //Use the 64-bit Mersenne Twister 19937 generator
    std::uniform_int_distribution<unsigned long long> distr(1, num);// distribution in range [1, num]
    return distr(eng);
}
/*
 * multiset同一个值可以出现多次·
 * */
void multiset_init() {
    multiset<int, less<int>> set1;
    int tmp = 0;

    cout << "请输入multiset的值：";
    cin >> tmp;
    while (tmp) {
        set1.insert(tmp);
        cout << "请输入multiset的值：";
        cin >> tmp;
    }

    for (auto it:set1) {
        cout << it << endl;
    }
}

int main(int argc, char* argv[]) {

    multiset_init();

    return 0;
}
