//
// Created by andrew on 2020/11/22.
//
#include <iostream>

using namespace std;

class MakeCar {
public:
    virtual ~MakeCar() = default;
    virtual void MakeHead() = 0;

    virtual void MakeBody() = 0;

    virtual void MakeTail() = 0;

public:
    void Make() // 模板函数，把业务逻辑给做好
    {
        MakeTail();
        MakeBody();
        MakeHead();
    }
};

// 只去实现具体过程，逻辑流程由父类进行规定
class Jeep : public MakeCar {
public:
    void MakeHead() override {
        cout << "jeep head" << endl;
    }

    void MakeBody() override {
        cout << "jeep body" << endl;
    }

    void MakeTail() override {
        cout << "jeep tail" << endl;
    }
};

class Bus : public MakeCar {
public:
    void MakeHead() override {
        cout << "bus head" << endl;
    }

    void MakeBody() override {
        cout << "bus body" << endl;
    }

    void MakeTail() override {
        cout << "bus tail" << endl;
    }
};


int main(int argc, char *argv[]) {
    // 模板模式
    MakeCar *car = new Bus;
    car->Make();
    delete car;

    MakeCar *car2 = new Jeep;
    car2->Make();
    delete car2;

    return 0;
}