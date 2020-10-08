#include <iostream>

using namespace std;

// 在使用开闭原则之前
// 所有的事情都一个对象中完成，显得类很臃肿
class BankWorker
{
public:
    void SaveMoney(void)
    {
        cout << "save money" << endl;
    }

    void WithdrawMoney(void)
    {
        cout << "withdraw money" << endl;
    }

    void TransferMoney(void)
    {
        cout << "transfer money" << endl;
    }
};

/* 使用开闭原则之后 */
// 定义一个虚类，相当于java中的接口
class OcpBankWorker
{
public:
    virtual void DoSomething(void) = 0;
    virtual ~OcpBankWorker(void)
    {
        cout << "OcpBankWorker" << endl;
    }
};

// 虚函数实现
class SaveBankWorker : public OcpBankWorker
{
public:
    virtual void DoSomething(void)
    {
        cout << "save money ocp" << endl;
    }
};

class WithdrawBankWorker : public OcpBankWorker
{
public:
    virtual void DoSomething(void)
    {
        cout << "withdraw money ocp" << endl;
    }
};

class TransferBankWorker : public OcpBankWorker
{
public:
    virtual void DoSomething(void)
    {
        cout << "transfer money ocp" << endl;
    }

};

// 框架函数
void HowDo(OcpBankWorker &ocpBankWorker)
{
    ocpBankWorker.DoSomething();
}

// 使用多态的三个
// 1.要有继承
// 2.要有函数重写
// 3.要有父类指针(父类引用)指向子类对象


int main(int argc, char const *argv[])
{
    // 在使用开闭原则之前
    cout << "before use open close principle" << endl;

    BankWorker *bw = new BankWorker;
    bw->SaveMoney();
    bw->TransferMoney();
    bw->WithdrawMoney();

    cout << "=========================================" << endl;
    // 使用开闭原则之后
    // 使用多态技术实现
    OcpBankWorker *aw = NULL;
    aw = new SaveBankWorker;
    HowDo(*aw);
    delete aw;

    aw = new WithdrawBankWorker;
    HowDo(*aw);
    delete aw;

    aw = new TransferBankWorker;
    HowDo(*aw);
    delete aw;

    cout << "open close principle" << endl;
    return 0;
}

