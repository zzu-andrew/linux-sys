#include <iostream>

using namespace std;

// 让computer框架和具体的厂商 进行解耦合

// 1. 定义虚类，主要目的是为了规定后期子类的行为
class HardDisk
{
public:
    virtual void work(void) = 0;
};

class Memory
{
public:
    virtual void work(void) = 0;
};

class Cpu
{
public:
    virtual void work(void) = 0;
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
    void work(void)
    {
        cout << "inter cpu work status ok." << endl;
    }
};

class XSDisk : public HardDisk
{
public:
    void work(void)
    {
        cout << "xs data work status ok." << endl;
    }

};

class KingStonMemory : public Memory
{
public:
    void work(void)
    {
        cout << "KingSton memory status is ok." << endl;
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


