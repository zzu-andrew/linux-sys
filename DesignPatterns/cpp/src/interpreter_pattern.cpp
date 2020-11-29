//
// Created by andrew on 2020/11/29.
//
#include <iostream>

using namespace std;

class Context {
public:
    explicit Context(int num) {
        this->m_num = num;
    }

    int getNum() const {
        return m_num;
    }

    int getRes() const {
        return m_res;
    }

    void setNum(int num) {
        this->m_num = num;
    }

    void setRes(int res) {
        this->m_res = res;
    }

private:
    int m_num;
    int m_res{};
};

class Expression {
public:
    virtual void interpreter(Context *context) = 0;

private:
    Context *m_context{};
};

//加法
class PlusExpression : public Expression {
public:
    PlusExpression() {
        this->context = nullptr;
    }

    void interpreter(Context *context) override {
        int num  = context->getNum();
        num ++;
        context->setNum(num);
        context->setRes(num);
    }

private:
    Context *context;
};
// 减法
class MinusExpression : public Expression {
public:
    MinusExpression() {
        this->context = nullptr;
    }

    void interpreter(Context * context) override{
        int num = context->getNum();
        num --;
        context->setNum(num);
        context->setRes(num);
    }

private:
    Context * context;
};

int main(int argc, char *argv[]) {
    Expression *expression = nullptr;
    Context  *context = nullptr;

    Expression * expression2 = nullptr;

    context = new Context(10);
    cout << context->getNum() << endl;

    expression = new PlusExpression;
    expression->interpreter(context);

    cout << context->getRes() << endl;

    ////   -----------------------------------------------

    expression2 = new MinusExpression;
    expression2->interpreter(context);
    cout << context->getRes() << endl;

    cout << "interpreter demo" << endl;
    return 0;
}
