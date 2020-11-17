//
// Created by andrew on 2020/11/15.
//
#include <iostream>

using namespace std;

class Subject {
public:
    virtual ~Subject(){

    }
    virtual void sailBook() = 0;
    virtual void Dstroy() = 0;
};

class RealSubjectBook : public Subject {
public:
    virtual void sailBook() {
        cout << "sail book" << endl;
    }
    virtual void Dstroy(){

    }
};

class taobaoProxy : public Subject {
public:
    virtual void sailBook(){
        RealSubjectBook *rsb = new RealSubjectBook;
        dazhe();
        rsb->sailBook();
        dazhe();
    }
    void Dstroy()
    {
        delete m_subject;
    }

public:
    void dazhe(){
        cout << "双 11 打折" << endl;
    }

private:
    Subject *m_subject;
};


int main(int argc, char *argv[]) {

    Subject *s = new taobaoProxy;
    s->sailBook();
    s->Dstroy();
    delete s;
    return 0;
}
