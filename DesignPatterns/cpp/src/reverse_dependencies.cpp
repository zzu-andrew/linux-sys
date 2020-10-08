#include <iostream>

using namespace std;

// 让computer框架和具体的厂商 进行解耦合
/*
在基类析构函数声明为virtual的时候，delete基类指针，会先调用派生类的析构函数，再调用基类的析构函数。
在基类析构函数没有声明为virtual的时候，delete基类指针，只会调用基类的析构函数，而不会调用派生类的析构函数，这样会造成销毁对象的不完全。
*/

// 1. 定义虚类，主要目的是为了规定后期子类的行为
class HardDisk
{
public:
    virtual void work(void) = 0;
    virtual ~HardDisk()
    {
        cout << "HardDisk" << endl;
    }
};

class Memory
{
public:
    virtual void work(void) = 0;
    virtual ~Memory()
    {
        cout << "Memory" << endl;
    }
};

class Cpu
{
public:
    virtual void work(void) = 0;
    virtual ~Cpu()
    {
        cout << "Cpu" << endl;
    }
};

class Computer
{
public:
    Computer(HardDisk *hardDisk, Memory *memory, Cpu *cpu)
    {
        m_hardDisk = hardDisk;
        m_memory = memory;
        m_cpu = cpu;
    }
    ~Computer(void)
    {
        cout << "computer" << endl;
    }
    void work()
    {
        m_hardDisk->work();
        m_memory->work();
        m_cpu->work();
    }

private:
    HardDisk *m_hardDisk;
    Memory *m_memory;
    Cpu *m_cpu;
};
class InterCpu : public Cpu
{
public:
    virtual void work(void)
    {
        cout << "inter cpu work status ok." << endl;
    }
    ~InterCpu()
    {
        cout << "cpu" << endl;
    }
};

class XSDisk : public HardDisk
{
public:
    virtual void work(void)
    {
        cout << "xs data work status ok." << endl;
    }
    ~XSDisk(void)
    {
        cout << "XSDisk"<< endl;
    }

};

class KingStonMemory : public Memory
{
public:
    virtual void work(void)
    {
        cout << "KingSton memory status is ok." << endl;
    }
    ~KingStonMemory(void)
    {
        cout << "KingStonMemory" << endl;
    }
};


int main(int argc, char const *argv[])
{
    // 基于多态实现依赖颠倒
    HardDisk *hardDisk = NULL;
    Memory *memory = NULL;
    Cpu *cpu = NULL;

    hardDisk = new XSDisk;
    memory = new KingStonMemory;
    cpu = new InterCpu;

    Computer *myComputer = new Computer(hardDisk, memory, cpu);
    myComputer->work();

    delete myComputer;
    delete cpu;
    delete memory;
    delete hardDisk;

    cout << "hello world." << endl;
    return 0;
}


