//
// Created by andrew on 2020/11/25.
//
#include <iostream>

using namespace std;
/*
 * 责任链模式
 * */

// 在造车的过程，一部分造完之后，需要将任务传递下去
class CarHandle {
public:
    virtual void HandleCar() = 0;

    virtual ~CarHandle() = default;

    CarHandle *setNextHandle(CarHandle *handle) {
        m_handle = handle;
        return m_handle;
    }

protected:
    CarHandle *m_handle{}; // 指向下一个处理单元
};

class HeadCarHandle : public CarHandle {
public:
    void HandleCar() override {
        cout << "make head" << endl;
//       开始造车头，车头造好之后，交给下一个调用者
        if (m_handle != nullptr) {
            m_handle->HandleCar();
        }
    }
};

class BodyCarHandle : public CarHandle {
public:
    void HandleCar() override {
        cout << "make body" << endl;
//        车身造好之后，把任务递交给 下一个处理者
        if (m_handle != nullptr) {
            m_handle->HandleCar();
        }
    }
};

class TailCarHandle : public CarHandle {
public:
    void HandleCar() override {
        cout << "make tail" << endl;
//        造车尾  把任务递交给 下一个处理器
        if (m_handle != nullptr) {
            m_handle->HandleCar();
        }
    }
};


int main(int argc, char *argv[]) {
    CarHandle *headHandle = new HeadCarHandle;
    CarHandle *bodyHandle = new BodyCarHandle;
    CarHandle *tailHeadle = new TailCarHandle;

    headHandle->setNextHandle(tailHeadle);
    tailHeadle->setNextHandle(bodyHandle);
    bodyHandle->setNextHandle(nullptr);

    headHandle->HandleCar();

    delete tailHeadle;
    delete bodyHandle;
    delete headHandle;

    return 0;
}