//
// Created by andrew on 2020/11/17.
//
#include <iostream>

using namespace std;

class Engine {
public:
    virtual void InstallEngine() = 0;

    virtual ~Engine() {

    }
};

class Engine4400cc : public Engine {
public:
    virtual void InstallEngine() {
        cout << "I'm 4400cc install over." << endl;
    }
};

class Engine4500cc : public Engine {
public:
    virtual void InstallEngine() {
        cout << "I'm 4500cc install over." << endl;
    }
};

class Car {
public:
    Car(Engine *engine) {
        m_engine = engine;
    }

    virtual ~Car() {

    }

protected:
    Engine *m_engine;
};

class BMW3 : public Car {
public:
    BMW3(Engine *engine) : Car(engine) {

    }

    // 具体实现和car分离
//    m_engine每个car都要有个引擎，抽象出来，放到公共类中，实现抽象和实现分离
    virtual void intallEngine() {
        //安装的动作是在engine里面实现，与car分离
        m_engine->InstallEngine();
    }
};

class BMW5 : public Car {
public:
    BMW5(Engine *engine) : Car(engine) {}

    virtual void installEngine() {
        cout << "BMW5" << endl;
        m_engine->InstallEngine();
    }
};

int main(int argc, char *argv[]) {

    Engine *engine = NULL;
    BMW5 *bmw5 = NULL;

    engine = new Engine4400cc;
    bmw5 = new BMW5(engine);
    bmw5->installEngine();

    delete bmw5;
    delete engine;

    return 0;
}
