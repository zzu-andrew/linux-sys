#include <iostream>

using namespace std;

class Singleton
{
private:
    Singleton()
    {
        cout << "sluggard singleton construct start." << endl;
    }

public:
    static Singleton *getInstance(void)
    {
        if(NULL == m_psl) // 懒汉式，每次获取实例都要判断，在多线程中会存在问题
        {
            m_psl = new Singleton;
        }
        return m_psl;
    }

    static void FreeInstance()
    {
        if(NULL != m_psl)
        {
            delete m_psl;
            m_psl = NULL;
        }
    }
private:
    static Singleton *m_psl;
};

// 静态变量初始化的方法，要放到类的外面
Singleton *Singleton::m_psl = NULL;

// 懒汉式，只有在使用的时候才会去创建
// 存在的问题，多个线程同时首次调用时，可能会出现创建多次的问题(导致内存泄漏)

int main(int argc, char const *argv[])
{
    // 使用功能去全局获取接口获取资源
    Singleton *p1 = Singleton::getInstance(); 
    Singleton *p2 = Singleton::getInstance();

    if(p1 == p2)
    {
        cout << "p1 equal p2" << endl;
    }
    else
    {
        cout << "p1 not equal p2" << endl;
    }
    
    // 手动释放单例模式创建的唯一一个对象
    Singleton::FreeInstance();
 
    cout << "singleton." <<  endl;
    return 0;
}

