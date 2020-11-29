//
// Created by andrew on 2020/11/28.
//
#include <iostream>
#include <list>

using namespace std;

class Secretary;

// 观察者
class PlayerObserver{
public:
    explicit PlayerObserver(Secretary *secretary){
        this->m_secretary = secretary;
    }
    // 没有操作任何私有变量，建议使用 static 类型函数
    void update(const string& action){
        cout << "action" << action << endl;
        cout << "boss is coming" << endl;
    }

private:
    Secretary *m_secretary;
};

class Secretary{
public:
    Secretary(){
        m_list.clear();
    }
     void Notify(string info){
        // 给所有的 观察者 发送情报
        for(auto it=m_list.begin();it!=m_list.end();it++)
        {
            (*it)->update(info);
        }
    }

    void setPlayerObserver(PlayerObserver *o){
        m_list.push_back(o);
    }

private:
    list<PlayerObserver *>m_list;
};

int main(int argc, char* argv[]){

    Secretary *secretary = nullptr;
    PlayerObserver *playerObserver1 = nullptr;
    PlayerObserver *playerObserver2 = nullptr;

    secretary = new Secretary;
    playerObserver1 = new PlayerObserver(secretary);
    playerObserver2 = new PlayerObserver(secretary);

    secretary->setPlayerObserver(playerObserver1);
    secretary->setPlayerObserver(playerObserver2);

    secretary->Notify("boss is coming");
    secretary->Notify("boss in gone");

    delete playerObserver1;
    delete playerObserver2;
    delete secretary;

    cout << "observer demo" << endl;
    return 0;
}
