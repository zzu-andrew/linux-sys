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

class Factory
{
public:
    Fruit *CreateFruit(string &pStr)
    {
        if(0 == pStr.compare("banana"))
        {
            return new Banana;
        }
        else if(0 == pStr.compare("apple"))
        {
            return new Apple;
        }
        else
        {
           cout << "Factory not support" << endl;
        }
        return NULL;
    }
};


int main(int argc, char const *argv[])
{
    Factory *f = new Factory;

    Fruit *fruit = NULL;
    string bananaStr("banana");
    string appleStr("apple"); 


    // 工厂声场香蕉
    fruit = f->CreateFruit(bananaStr);
    if(NULL != fruit)
    {
        fruit->GetFruit();
        delete fruit;
    }
    // 工厂生产苹果
    fruit = f->CreateFruit(appleStr);
    if(NULL != fruit)
    {
        fruit->GetFruit();
        delete fruit;
    }

    delete f;
    cout << "simple factory test" << endl;
    return 0;
}

