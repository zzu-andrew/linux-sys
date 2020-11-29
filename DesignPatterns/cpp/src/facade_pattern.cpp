//
// Created by andrew on 2020/11/21.
//
#include <iostream>

using namespace std;

class SubSystemA{
public:
    void doThing(){
        cout << "Subsystem A run" << endl;
    }
};

class SubSystemB{
public:
    void doThing(){
        cout << "SubSystem B run" << endl;
    }
};

class SubSystemC{
public:
    void doThing(){
        cout << "SubSystem B run" << endl;
    }
};

class Facade{
public:
    Facade(){
        sysA = new SubSystemA;
        sysB = new SubSystemB;
        sysC = new SubSystemC;
    }
    ~Facade(){
        delete sysA;
        delete sysB;
        delete sysC;
    }

public:
    void doThing(){
        sysA->doThing();
        sysB->doThing();
        sysC->doThing();
    }

private:
    SubSystemA *sysA;
    SubSystemB *sysB;
    SubSystemC *sysC;
};

int main(int argc, char *argv[]) {
//   没有使用之前
    cout << "before use facade" << endl;
    SubSystemA *sysA = new SubSystemA;
    SubSystemB *sysB = new SubSystemB;
    SubSystemC *sysC = new SubSystemC;

    sysA->doThing();
    sysB->doThing();
    sysC->doThing();
    delete sysA;
    delete sysB;
    delete sysC;
//    是要给你之后
    cout << "after usr facade" << endl;
    Facade *f = new Facade;
    f->doThing();
    delete f;
    return 0;
}
