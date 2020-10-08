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
// 饿汉式是在初始化指变量的时候就对其进行创建，不管是否被调用
Singleton *Singleton::m_psl = new Singleton;

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
 
    cout << "hungry singleton." <<  endl;
    return 0;
}

