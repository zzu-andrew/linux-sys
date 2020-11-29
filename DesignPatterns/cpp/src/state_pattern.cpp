//
// Created by andrew on 2020/11/29.
//
#include <iostream>

using namespace std;

class Worker;

class State {
public:
    virtual ~State() = default;
    virtual void doSomeThing(Worker *w);
};

void State::doSomeThing(Worker *w) {

}

class Worker {
public:
    Worker();

    void setHour(int hour) {
        m_hour = hour;
    }

    State *getCurrentState() {
        return m_currState;
    }

    void setCurrentState(State *state) {
        m_currState = state;
    }

    void doSomeThing() {
        m_currState->doSomeThing(this);
    }

public:
    int getHour() const {
        return m_hour;
    }

private:
    int m_hour{};
    State *m_currState{}; // 对象当前状态
};

class State1 : public State {
public:
    void doSomeThing(Worker * w) override;
};

class State2 : public State {
public:
    void doSomeThing(Worker * w) override;
};



void State1::doSomeThing(Worker *w) {
    if(w->getHour() == 7 || w->getHour() == 0)
    {
        cout << "morning " << endl;
    }else
    {
        delete w->getCurrentState();
        w->setCurrentState(new State2);  // 状态1不满足，转到状态2
        w->getCurrentState()->doSomeThing(w);

    }
}

void State2::doSomeThing(Worker *w) {
    if(w->getHour() == 9 || w->getHour() == 10)
    {
        cout << "work" << endl;
    }else
    {
        delete w->getCurrentState(); // 状态2不满足转到状态
        w->setCurrentState(new State1);
        cout << "当钱时间点：" << w->getHour() << "unkonwn" << endl;
    }
}

Worker::Worker() {
    m_currState = new State1;
}


int main(int argc, char *argv[]) {
    auto *w1 = new Worker;
    w1->setHour(7);
    w1->doSomeThing();

    w1->setHour(9);
    w1->doSomeThing();

    delete w1;

    cout << "state demo" << endl;
    return 0;
}
