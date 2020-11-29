//
// Created by andrew on 2020/11/28.
//
#include <iostream>

using namespace std;

// Caretaker 管理者
// Memento 备忘录

class Memento{
public:
    Memento(string name, int age){
        m_name = name;
        m_age = age;
    }
    string getName(){
        return m_name;
    }
    int getAge() const{
        return m_age;
    }
    void setName(string name){
        this->m_name = name;
    }
    void setAge(int age){
        this->m_age = age;
    }

private:
    string m_name;
    int m_age;
};

class Person{
public:
    Person(string name, int age){
       m_name = name;
       m_age = age;
    }
    string getName(){
        return m_name;
    }
    int getAge() const{
        return m_age;
    }
    void setName(string name){
        this->m_name = name;
    }
    void setAge(int age){
        m_age = age;
    }
    // 保存,将需要的信息记录到Memento中
//    原生者 创建一个备忘录，用于保存信息
    Memento *createMemento()
    {
        return new Memento(m_name, m_age);
    }
    //还原
    void setMemento(Memento *memento)
    {
        this->m_name = memento->getName();

        this->m_age = memento->getAge();
    }

    void printT(){
        cout << "m_name:" << m_name << "m_age:" << m_age << endl;
    }

private:
    string m_name;
    int m_age;
};

class Caretaker{
public:
    explicit Caretaker(Memento * memento){
        this->memento = memento;
    }
    Memento *getMemento(){
        return memento;
    }

    void setMemento(Memento *memento){
        this->memento = memento;
    }

private:
    Memento *memento;
};


int main(int argc, char* argv[]){

    Caretaker *caretaker = nullptr;
    auto *p = new Person("bob", 32);
    p->printT();

    cout << "----------------------" << endl;
    caretaker = new Caretaker(p->createMemento());
    p->setAge(42);
    p->printT();

    cout << "ro back" << endl;
    p->setMemento(caretaker->getMemento());
    p->printT();

    cout << "memento pattern" << endl;
}
