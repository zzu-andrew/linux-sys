//
// Created by andrew on 2020/11/28.
//
#include <iostream>

using namespace std;

class Mediator;

class Person {
public:
    Person(string name, int sex, int condi, Mediator *m) {
        m_name = name;
        m_sex = sex;
        m_condi = condi;
        mediator = m;
    }
    virtual ~Person() = default;

    string getName() {
        return m_name;
    }

    int getSex() const {
        return m_sex;
    }

    int getCondi() const {
        return m_condi;
    }

    virtual void getParter(Person *p) = 0;

protected:
    string m_name;
    int m_sex;
    int m_condi;
    Mediator *mediator;
};

class Mediator {
public:
    virtual ~Mediator() = default;
    void setMan(Person *man) {
        pMan = man;
    }

    void setWoman(Person *woman) {
        pWoman = woman;
    }

    virtual void getParter() {
        if (pWoman->getSex() == pMan->getSex()) {
            cout << "性别相同不能找对象" << endl;
        }
        if (pWoman->getCondi() == pMan->getCondi()) {
            cout << pWoman->getName() << "     and    " << pMan->getName() << "    OK" << endl;
        } else {
            cout << pWoman->getName() << "    and    " << pMan->getName() << "     failed" << endl;
        }
    }


private:
    Person *pMan{};
    Person *pWoman{};
};

class Woman : public Person {
public:
    Woman(string name, int sex, int condi, Mediator *m) : Person(name, sex, condi, m) {

    }

    virtual void getParter(Person *p) {
        mediator->setMan(p);
        mediator->setWoman(this);
        mediator->getParter(); // 找对象
    }
};

class Man : public Person {
public:
    Man(string name, int sex, int condi, Mediator *m) : Person(name, sex, condi, m) {

    }

    virtual void getParter(Person *p) {
        mediator->setMan(this);
        mediator->setWoman(p);
        mediator->getParter();
    }
};

int main(int argc, char *argv[]) {
    auto *m = new Mediator;
    Person *alice = new Woman("alice", 2, 4, m);

    Person *bob = new Man("bob", 1, 4, m);

    alice->getParter(bob);
    bob->getParter(alice);
    delete bob;
    delete alice;
    delete m;
    cout << "mediator demo" << endl;
    return 0;
}
