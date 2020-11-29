//
// Created by andrew on 2020/11/29.
//
#include <iostream>

using namespace std;

typedef int Object;

#define SIZE 5

class MyIterator {
public:
    virtual ~MyIterator() = default;
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone() = 0;
    virtual Object CurrentItem() = 0;
};

class Aggregate {
public:
    virtual ~Aggregate() = default;
    virtual MyIterator *CreateIterator() = 0;
    virtual Object getItem(int index) = 0;
    virtual int getSize() = 0;
};
// 进行迭代的地方
class ConcreteIterator : public MyIterator {
public:
    ConcreteIterator(Aggregate *ag) {
        _ag = ag;
        _current_index = 0;
    }

    virtual void First() {
        _current_index = 0;
    }

    virtual void Next() {
        if(_current_index < _ag->getSize())
        {
            _current_index ++;
        }
    }
    virtual bool IsDone() {
        return (_current_index == _ag->getSize());
    }

    virtual Object CurrentItem() {
        return _ag->getItem(_current_index);
    }

private:
    int _current_index;
    Aggregate *_ag;
};

// 存储需要迭代的内容
class ConcreteAggregate : public Aggregate {
public:
    ConcreteAggregate() {
        for(int i = 0; i < SIZE; i++) {
            object[i] = i + 100;
        }
    }

    MyIterator *CreateIterator() override{
        return new ConcreteIterator(this); // 让迭代器持有一个集合的引用
    }

    Object getItem(int index) override {
        return object[index];
    }

    int getSize() override {
        return SIZE;
    }
private:
    Object object[SIZE];
};

int main(int argc, char *argv[]) {

    Aggregate *aggregate = new ConcreteAggregate;
    MyIterator *myIterator = aggregate->CreateIterator();

    for(; !(myIterator->IsDone()); myIterator->Next()) {
        cout << myIterator->CurrentItem() << "  ";
    }

    delete myIterator;
    delete aggregate;

    cout << "iterator demo" << endl;
    return 0;
}
