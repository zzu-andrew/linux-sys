#include <iostream>
#include <string>

using namespace std;

//  抽象类中定义子类中需要实现的功能，也就是限定了子类必须实现的一些函数
class Fruit
{
public:
    virtual void GetFruit(void) = 0;
    virtual ~Fruit(void)
    {

    }
};

class AbstractFactory
{
public:
    virtual Fruit *CreateBanana(void) = 0;
    virtual Fruit *CreateApple(void) = 0;
    // 这里析构函数使用虚函数的原因是因为，只有父类中析构函数使用虚函数，
    // 多态时才会从子类析构函数一直调用到基类结束，否则只会调用父类的不会调用子类的析构函数
    virtual ~AbstractFactory(void)
    {

    }
};

class NorthBanana : public Fruit
{
public:
    virtual void GetFruit(void)
    {
        cout << "I'm North banana." << endl;
    }
};

class NorthApple : public Fruit
{
public:
    virtual void GetFruit(void)
    {
        cout << "I'm North apple." << endl;
    }
};

class SourthBanana : public Fruit
{
public:
    virtual void GetFruit(void)
    {
        cout << "I'm Sourth banana." << endl;
    }
};

class SourthApple : public Fruit
{
public:
    virtual void GetFruit(void)
    {
        cout << "I'm Sourth apple." << endl;
    }
};

class NorthFactory : public AbstractFactory
{
public:
    virtual Fruit *CreateBanana(void)
    {
        return new NorthBanana;
    }

    virtual Fruit *CreateApple(void)
    {
        return new NorthApple;
    }
};

class SourthFactory : public AbstractFactory
{
public:
    virtual Fruit *CreateBanana(void)
    {
        return new SourthBanana;
    }

    virtual Fruit *CreateApple(void)
    {
        return new SourthApple;
    }
};

int main(int argc, char const *argv[])
{
    AbstractFactory  *abstractFactory = NULL;
    Fruit            *fruit = NULL;

    abstractFactory = new SourthFactory;
    fruit = abstractFactory->CreateApple();
    fruit->GetFruit();
    delete fruit;
    fruit = abstractFactory->CreateBanana();
    fruit->GetFruit();
    delete fruit;

    delete abstractFactory;

    abstractFactory = new NorthFactory;
    fruit = abstractFactory->CreateApple();
    fruit->GetFruit();
    delete fruit;
    fruit=abstractFactory->CreateBanana();
    fruit->GetFruit();
    delete fruit;
    delete abstractFactory;

    cout << "simple factory test" << endl;
    return 0;
}

