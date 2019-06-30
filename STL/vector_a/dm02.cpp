#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdio.h>

using namespace std;

/**
 * @brief  string类的初始化
 * @note   
 * @param  argc: 
 * @param  *argv[]: 
 * @retval 
 */
void init_test(void)
{
    string s1 = "aaa";
    string s2("bbbb");
    string s3 = s2; //通过copy构造函数初始化string对象
    string s4(10, 'a');

    cout << "s1   " << s1 << endl;
    cout << "s2   " << s2 << endl;
    cout << "s3   " << s3 << endl;
    cout << "s4   " << s4 << endl;

}

/**
 * @brief  字符串的遍历
 * @note   
 * @param  argc: 
 * @param  *argv[]: 
 * @retval 
 */
void list_string(void)
{
    cout << "list_string" << endl;
    string s1 = "abcdefg";
    //数组方式
    for (int i = 0; i < s1.length(); i++)
    {
        //< 将字符串当成数组一样使用
        cout << s1[i] << endl;
    }
    cout << "--------------------------------" << endl;
    //< 迭代器方式
    for (string::iterator it = s1.begin(); it != s1.end(); it ++)\
    {
        cout << (*it) << endl;
    }
    cout << "----------------------------------" << endl;
    //< at函数
    for (int i = 0; i < s1.length(); i ++)
    {
        //< at函数能偶检测异常，出现异常的时候可以抛出异常，异常可以用sty函数进行捕获
        cout << s1.at(i) << endl; //< 抛出异常
    }
    cout << "---------------------" << endl;

    /* 异常测试 */
    try
    {
        //< 有异常的时候捕获异常
        for (int i = 0; i < s1.length() + 3; i ++) //< 故意多出来三个字节用于抛出异常
        {
            cout << s1.at(i) << endl; //< 抛出异常
        }
            
    }
    catch(...)  //< 捕捉所有的一场呢
    {
        std::cerr << "error exception" << '\n';
    }

}

/**
 * @brief  字符指针和string类型的转换
 * @note   
 * @param  argc: 
 * @param  *argv[]: 
 * @retval 
 */
void charbuf_string(void)
{   cout << "charbuf_string" << endl;
    //< char * ==> string
    string s1 = "aaabcgdjsggkkws";
    //< string ==> char *
    const char *buf;
    buf = s1.c_str();
    printf("%s\n", s1.c_str());

    //< 3 s1的内容copy到buf中
    char buf1[128];
    s1.copy(buf1, 3, 0); //< 从零字符开始copy3个字符到buf1中
    cout << buf1 << endl;


}
/**
 * @brief  string cat
 * @note   字符串连接
 * @param  argc: 
 * @param  *argv[]: 
 * @retval 
 */
void string_cat(void)
{
    //< string方式的连接
    cout << "string cat " << endl;
    string s1 = "aaa";
    string s2 = "bbb";
    string s3 = s1 + s2;

    cout << s3 << endl;
    cout << "-------------------" << endl;
    s2.append(s1);
    cout << s2 << endl;

}

/* 
 * find函数 从pos位置开始查找c字符或者字符串的位置，函数找不到就返回 -1
 * rfind向前查找
 * 
 * replace替换
 * swap交换
 *  */
/**
 * @brief  search string
 * @note   字符串的查找和替换
 * @param  argc: 
 * @param  *argv[]: 
 * @retval 
 */
void search_string(void)
{
    string s1 = "wbm hello hajhdhhfd 111 name name name 3434654655";
    //< 第一次出现 name的位置
    int index = s1.find("name", 0);
    cout << "index = " <<index << endl;

    //< 求 name出现的次数，每一次出现的数组下标
    int offline = s1.find("name", 0);
    while (offline != -1)
    {
        cout << "offline = " << offline << endl;
        offline = offline + 1;
        offline = s1.find("name", offline);        
    }

    //< 替换成大写
    offline = s1.find("name", 0);
    while (offline != string::npos)
    {
        cout << "offline = " << offline << endl;
        s1.replace(offline, 1, "N");
        offline = offline + 1;
        offline = s1.find("name", offline);  
        cout << "s1 替换之后" << s1 << endl;      
    }
}

 /**
  * @brief main  
  * @note  string的简单使用
  * @param  argc: 
  * @param  *argv[]: 
  * @retval 
  */
int main(int argc, char const *argv[])
{
  
   init_test();
   list_string();
   charbuf_string();
   string_cat();
   search_string();
    cout << "hello world!" << endl;
    return 0;
}



