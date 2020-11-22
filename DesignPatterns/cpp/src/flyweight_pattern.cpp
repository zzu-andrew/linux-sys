//
// Created by andrew on 2020/11/22.
//
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Person {
public:
    Person(string name, int age) {
        this->age = name;
        this->age = age;
    }
    virtual ~Person(){

    }

    virtual void printT() = 0;


protected:
    string m_name;
    basic_string<char> age;
};

class Teacher : public Person {
public:
    Teacher(string name, int age, string id) : Person(name, age) {
        this->m_id = id;
    }

    void printT() override {
        cout << "name:" << m_name << "age:" << age << "m_id:" << m_id << endl;
    }

private:
    string m_id;
};

// 完成 老师节点 储存
class FlyweightTeacherFactory {
public:
    FlyweightTeacherFactory() {
        map1.clear();
    }

    ~FlyweightTeacherFactory() {
        while (!map1.empty()) {
            Person *tmp = NULL;
            auto it = map1.begin();
            tmp = it->second;
            map1.erase(it);  // 将第一个节点从容器中删除
            delete tmp;
        }
    }

    Person *GetTeacher(string id) {
        Person *tmp = NULL;
        map<string, Person *>::iterator  it;
        it = map1.find(id);
        if (it == map1.end()) {
            string tmpname;
            int tmpage;
            cout << "enter teacher name:";
            cin >> tmpname;
            cout << "enter age";
            cin >> tmpage;
            tmp = new Teacher(tmpname, tmpage, id);
            map1.insert(pair<string, Person *>(id, tmp));
        } else
        {
            tmp = it->second;
        }
        return tmp;
    }

private:
    map<string, Person *> map1;
};


int main(int argc, char *argv[]) {

    Person *p1 = NULL;
    Person *p2 = NULL;
    FlyweightTeacherFactory *fwtf = new FlyweightTeacherFactory;
    p1 = fwtf->GetTeacher("001");
    p1->printT();

    p2 = fwtf->GetTeacher("001");
    p2->printT();

    delete fwtf;

    cout << "flyweight demo" << endl;
    return 0;
}


