// str1.cpp -- introducing the string class
#include <iostream>
#include <string>
// using string constructors

int main()
{
    using namespace std;
    //初始化为  对应的字符串
    string one("Lottery Winner!");     // ctor #1
    cout << one << endl;               // overloaded <<
    //初始化为 20 个 $字符
    string two(20, '$');               // ctor #2
    cout << two << endl;
    //用one初始化为  three
    string three(one);                 // ctor #3
    cout << three << endl;
    // 增加  Oops字符
    one += " Oops!";                   // overloaded +=
    cout << one << endl;
    //赋值初始化
    two = "Sorry! That was ";
    three[0] = 'P';
    string four;                       // ctor #4
    four = two + three;                // overloaded +, =
    cout << four << endl;
    char alls[] = "All's well that ends well";
    string five(alls,20);              // ctor #5
    cout << five << "!\n";
    string six(alls+6, alls + 10);     // ctor #6
    cout << six  << ", ";
    string seven(&five[6], &five[10]); // ctor #6 again
    cout << seven << "...\n";
    string eight(four, 7, 16);         // ctor #7
    cout << eight << " in motion!" << endl;
    // std::cin.get();
    return 0; 
}
