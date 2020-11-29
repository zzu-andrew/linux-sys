//
// Created by andrew on 2020/11/28.
//
#include <iostream>
#include <list>

using namespace std;

class ParkElement;

class Visitor{
public:
    virtual ~Visitor() = default;
    virtual void visit(ParkElement *parkElement) = 0;
};

class ParkElement{
public:
    virtual ~ParkElement() = default;
    virtual void accept(Visitor *visitor) = 0;
};

class ParkA : public ParkElement{
public:
    void accept(Visitor *v) override{
        // 公园接收访问者， 让访问者操作
        v->visit(this);
    }
};

class ParkB : public ParkElement{
public:
    void accept(Visitor *v) override{
        v->visit(this);
    }
};

// 整个公园
class Park : ParkElement {
public:
    Park(){
        m_list.clear();
    }

    void setParkElement(ParkElement *pe){
        m_list.push_back(pe);
    }

    void accept(Visitor *v) override{
        for(auto it=m_list.begin();it!=m_list.end(); it++)
        {
            (*it)->accept(v);
        }
    }

private:
    list<ParkElement *>m_list;
};

class VisitorA : public Visitor{
    void visit(ParkElement *parkElement) override {
        cout << "part A is clear" << endl;
    }
};

class VisitorB : public Visitor {
public:
    void visit(ParkElement *parkElement) override{
        cout << "part B is clear" << endl;
    }
};

class ManagerVisitor : public Visitor {
public:
    void visit(ParkElement * parkElement) override {
        cout << "visit all part" << endl;
    }
};

void PartVisitor() {
    Visitor *vA = new VisitorA;
    Visitor *vB = new VisitorB;

    auto *parkA = new ParkA;
    auto *parkB = new ParkB;

    parkA->accept(vA);
    parkB->accept(vB);

    delete vA;
    delete vB;
    delete parkB;
    delete parkA;
}

void ManagerVisit() {
    Visitor *vManager = new ManagerVisitor;
    Park *park = new Park;

    ParkElement *parkA = new ParkA;
    ParkElement *parkB = new ParkB;

    park->setParkElement(parkA);
    park->setParkElement(parkB);

//    整个公园接受管理员的访问
    park->accept(vManager);

    delete parkA;
    delete parkB;
    delete park;
    delete vManager;
}

int main(int argc, char* argv[]){

    PartVisitor();
    ManagerVisit();

    return 0;
}
