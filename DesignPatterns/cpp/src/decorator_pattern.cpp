//
// Created by andrew on 2020/11/17.
//
#include <iostream>

using namespace std;

class Car {
public:
    virtual void show() = 0;

    virtual ~Car() {

    }
};

class RunCar : public Car {
public:
    virtual void show() {
        cout << "run car" << endl;
    }

    ~RunCar() {

    }
};

// 当传进来的是runcar的时候，就能实现在不继承runcar的情况下扩展runcar的功能
class SwimCarDirector : public Car {
public:
    SwimCarDirector(Car *car) {
        m_car = car;
    }

    ~SwimCarDirector() {

    }

    void swim() {
        cout << "swim" << endl;
    }

    virtual void show() {
        m_car->show();
        swim();
    }

private:
    Car *m_car;
};

// 当传进来的是runcar的时候，就能实现在不继承runcar的情况下扩展runcar的功能
class FlyCarDirector : public Car {
public:
    FlyCarDirector(Car *car) {
        m_car = car;
    }

    ~FlyCarDirector() {

    }

    void fly() {
        cout << "fly" << endl;
    }

    virtual void show() {
        m_car->show();
        fly();
    }

private:
    Car *m_car;
};


int main(int argc, char *argv[]) {
//   考点，虚基类虽然不能定义对象，但是能定义指针，指针指向子类
    Car *mycar = NULL;
    mycar = new RunCar;
    mycar->show();
    cout << "-------------------------" << endl;
//    修饰模式，将run car修饰之后就能飞了
    FlyCarDirector *flyCar = new FlyCarDirector(mycar);
    flyCar->show();
//
    cout << "-------------------------" << endl;
    SwimCarDirector *swimCar = new SwimCarDirector(mycar);
    swimCar->show();

    delete swimCar;
    delete flyCar;
    delete mycar;

    cout << "decorator demo" << endl;
    return 0;
}
