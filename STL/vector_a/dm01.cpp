#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void vector_test(void)
{
    vector<int> v1;  //< 容器，定义一个int类型的向量
    //< 向容器中添加元素
    v1.push_back(1);
    v1.push_back(-1);
    v1.push_back(3);
    v1.push_back(3);
    v1.push_back(5);
    v1.push_back(7);

    //迭代器
    for (vector<int>::iterator it = v1.begin(); it != v1.end(); it ++)
    {
        cout << *it << "   "<< endl;
    }

    // 算法
    //< 统计大于零的个数为多少
    //< 使用的算法是 count 

    int num = count(v1.begin(), v1.end(), 3); //< 查找等于3的个数
    cout << "num = " << num << endl;


}
class teacher
{
private:
    /* data */
public:
    int age;
    char name[64];

public:
    void printT()
    {
        cout << "age" << age <<endl;
    }

    teacher(/* args */);
    ~teacher();
};

teacher::teacher(/* args */)
{
    cout << "construct teacher" << endl;
}

teacher::~teacher()
{
    cout << " destruct teacher !" << endl;
}
 /**
  * @brief  类的容器
  * @note   容器中可以放置任何的数据，实现数据和算法的有效分离
  * @retval None
  */
void vector_teacher(void)
{
    teacher T1, T2, T3;
    T1.age = 31;
    T2.age = 32;
    T3.age = 33;
   //< 容器中可以装任何的数据类型
    vector<teacher> Tea;  //< 容器，实现数据算法和数据的有效分离 
    //< 向容器中添加元素
    Tea.push_back(T1);
    Tea.push_back(T2);
    Tea.push_back(T3);

   
    for (vector<teacher>::iterator it = Tea.begin(); it != Tea.end(); it ++)
    {
        cout << it->age << "   "<< endl;
    }
    cout << "-----------------------------" << endl;

}
/**
  * @brief  类的容器
  * @note   容器中可以放置任何的数据，实现数据和算法的有效分离
  * @retval None
  */
void vector_teacher_point(void)
{
    teacher T1, T2, T3;
    T1.age = 31;
    T2.age = 32;
    T3.age = 33;
    teacher *p1, *p2, *p3;
    p1 = &T1;
    p2 = &T2;
    p3 = &T3;
   //< 容器中可以装任何的数据类型
   //< 是将元素copy了一份放到容器中去
    vector<teacher> Tea;  //< 容器，实现数据算法和数据的有效分离 
    //< 向容器中添加元素
    Tea.push_back(T1);
    Tea.push_back(T2);
    Tea.push_back(T3);

    vector<teacher *> pTea;

    pTea.push_back(p1);
    pTea.push_back(p2);
    pTea.push_back(p3);
   
    for (vector<teacher>::iterator it = Tea.begin(); it != Tea.end(); it ++)
    {
        cout << it->age << "   "<< endl;
    }
    cout << "-----------------------------" << endl;

    for (vector<teacher *>::iterator it = pTea.begin(); it != pTea.end(); it ++)
    {
        cout << (*it)->age << "   "<< endl;
    }
    cout << "-----------------------------" << endl;
}

 /**
  * @brief main  
  * @note  简单的测试容器和算法
  * @param  argc: 
  * @param  *argv[]: 
  * @retval 
  */
int main(int argc, char const *argv[])
{
  
    vector_test();
    vector_teacher();
    vector_teacher_point();
    cout << "hello world!" << endl;
    ///system("pause");
    return 0;
}



