# tring类和标准模板库



| 构造函数                                                     | 描述                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| string(const char *s)                                        | 将string初始化为s指向的NBTS                                  |
| string(size_type n, char c)                                  | 创建一个包含n个元素的string对象，其中每个元素都被初始化为字符c |
| string(const string & str)                                   | 将一个string对象初始化为string对象str(复制构造函数)          |
| string()                                                     | 创建一个默认的string对象，长度为0                            |
| string(const char * s, size_type n)                          | 将string初始化为s指向的NBTS的前n个字符，即使超过NBTS的结尾   |
| template<class Iter>                                               string(Iter begain, Iter end) | 将string初始化为区间为(begin, end)内的字符，其中begin和end的行为就像指针，用于指定位置，范围包括begin在内，但不 |
| string(const string & str, string size_type pos = 0, size_type n = npos) | 将一个string对象初始化为对象str中从位置pos开始到结尾的字符，或从位置pos开始的n个字符 |
| string(string && str)noexcept                                | 将一个string对象初始化为string对象str，并修改str             |
| string(inittializer_list<char> i1)                           | 将一个string对象初始化为初始化列表i1中的字符                 |

```c
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

```



## 模板类vector



```c
// vect1.cpp -- introducing the vector template
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int NUM = 5;
int main()
{

    /**
    * 省略模板参数的值，模板类，默认使用class Allocator  = allocator<T>
    * template <class T, class Allocator  = allocator<T>>
    */
    vector<int> ratings(NUM);
    vector<string> titles(NUM);
    cout << "You will do exactly as told. You will enter\n"
         << NUM << " book titles and your ratings (0-10).\n";
    int i;
    for (i = 0; i < NUM; i++)
    {
        cout << "Enter title #" << i + 1 << ": ";
        getline(cin,titles[i]);
        cout << "Enter your rating (0-10): ";
        cin >> ratings[i];
        cin.get();
    }
    titles.size();
    cout << "Thank you. You entered the following:\n"
          << "Rating\tBook\n";
    for (i = 0; i < NUM; i++)
    {
        cout << ratings[i] << "\t" << titles[i] << endl;
    }
    // cin.get();

    return 0; 
}

```







































![](/work/linux-sys/gcc/doc/picture/weixin.jpg)













































