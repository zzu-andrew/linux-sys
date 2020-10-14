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

class Banana : public Fruit
{
public:
    virtual void GetFruit(void)
    {
        cout << "I'm banana." << endl;
    }
};


class Apple : public Fruit
{
public:
    virtual void GetFruit(void)
    {
        cout << "I'm apple." << endl;
    }
};

class AbstractFactory
{
public:
    virtual Fruit *CreateProduct(void) = 0;
    // 这里析构函数使用虚函数的原因是因为，只有父类中析构函数使用虚函数，
    // 多态时才会从子类析构函数一直调用到基类结束，否则只会调用父类的不会调用子类的析构函数
    virtual ~AbstractFactory(void)
    {

    }
};

class BananaFactory : public AbstractFactory
{
public:
    virtual Fruit *CreateProduct(void)
    {
        return new Banana;
    }
};

class AppleFactory : public AbstractFactory
{
public:
    virtual Fruit *CreateProduct(void)
    {
        return new Apple;
    }
};

/**
 * 后期产品扩展
 */

class Peer : public Fruit
{
public:
    virtual void GetFruit(void)
    {
        cout << "I'm peer." << endl;
    }
};

class PeerFactory : public AbstractFactory
{
public:
   virtual Fruit *CreateProduct()
   {
       return new Peer;
   }

};

int main(int argc, char const *argv[])
{
    AbstractFactory  *factory = NULL;
    Fruit            *fruit = NULL;

    // 制造香蕉
    factory = new BananaFactory;
    fruit = factory->CreateProduct();
    fruit->GetFruit();

    delete fruit;
    delete factory;

    factory = new AppleFactory;
    fruit = factory->CreateProduct();
    fruit->GetFruit();

    delete fruit;
    delete factory;

    // 前期系统稳定之后，后期扩展
    cout << "extern" << endl;
    factory = new PeerFactory;
    fruit = factory->CreateProduct();
    fruit->GetFruit();
    
    delete fruit;
    delete factory;

    cout << "simple factory test" << endl;
    return 0;
}

