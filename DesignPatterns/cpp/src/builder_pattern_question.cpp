#include <iostream>
#include <string>
using namespace std;


class House
{
public:
    void setDoor(string door)
    {
        this->m_door = door;
    }
    void setWall(string wall)
    {
        this->m_wall = wall;
    }
    void setWindow(string window)
    {
        this->m_window = window;
    }

    string getDoor(void)
    {
        cout << m_door << endl;
        return m_door;
    }

    string getWall(void)
    {
        cout << m_wall << endl;
        return m_wall;
    }

    string getWindow(void)
    {
        cout << m_window << endl;;
        return m_window;
    }

private:
    string m_door;
    string m_wall;
    string m_window;
};

class Builder
{
public:
    Builder(void)
    {
        m_house = new House;
    }
    ~Builder(void)
    {
        delete m_house;
    }

    void MakeBuilder(void)
    {
        BuildDoor(m_house);
        BuildWall(m_house);
        BuildWindow(m_house);
    }

    void BuildDoor(House *h)
    {
        h->setDoor("door");
    }

    void BuildWall(House *h)
    {
        h->setWall("wall");
    }

    void BuildWindow(House *h)
    {
        h->setWindow("window");
    }

    House *GetHouse(void)
    {
        return m_house;
    }

private:
    House *m_house;
};

int main(int argc, char const *argv[])
{
    
    // 不需要建造者，客户直接造房子
    //  门窗  墙体玻璃等都需要用户管理
    House *house = new House;
    house->setDoor("user door");
    house->setWall("user Wall");
    house->setWindow("big window");
    house->getDoor();
    house->getWall();
    house->getWindow();
    delete house;

    // 华丽的分割线
    cout << "=========================" << endl;
    // 请工程队 建造房子
    // 将建造过程交给工程队， 是不是还可以请个指挥建造的？ 这样客户就能完全解放出来了
    Builder *builder = new Builder;
    builder->MakeBuilder();
    house = builder->GetHouse();
    house->getDoor();
    house->getWall();
    house->getWindow();
    delete builder;

    cout << "builder pattern question." << endl;
    return 0;
}
