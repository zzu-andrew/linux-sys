//
// Created by andrew on 2020/11/26.
//
#include <iostream>

using namespace std;

class Strategy {

public:
    virtual void crypt() = 0;

    virtual ~Strategy() = default;
};

class AES : public Strategy {
public:
    void crypt() override {
        cout << "AES strategy" << endl;
    }
};

class DES : public Strategy {
public:
    void crypt() override {
        cout << "DES strategy" << endl;
    }
};


class Context {
public:
    void setStrategy(Strategy *pStrategy) {
        this->strategy = pStrategy;
    }

    void myOperator() {
        strategy->crypt();
    }

private:
    Strategy *strategy;
};

int main(int argc, char *argv[]) {
    Strategy *strategy = nullptr;

    strategy = new AES;
    Context *context = new Context;
    context->setStrategy(strategy);
    context->myOperator();

    delete strategy;
    delete context;

    return 0;
}
