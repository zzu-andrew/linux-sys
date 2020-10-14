#include <iostream>
#include <string>
using namespace std;

// 建造者模式，就是通过虚工程对基类，实现
// 通过指挥者，指挥不同的建筑队建设不同的房子

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
    virtual void BuildWall(void) = 0;
    virtual void BuildDoor(void) = 0;
    virtual void BuildWindow(void) = 0;
    virtual House* GetHouse(void) = 0;
public:
    virtual ~Builder(void)
    {

    }
};

//公寓建筑工程队
class FlatBuilder : public Builder
{
public:
    FlatBuilder()
    {
        m_house = new House;
    }

    virtual void BuildWall(void)
    {
        m_house->setWall("flat wall");
    }

    virtual void BuildDoor(void)
    {
        m_house->setDoor("flat door");
    }

    virtual void BuildWindow(void)
    {
        m_house->setWindow("flat window");
    }

    virtual House* GetHouse(void)
    {
        return m_house;
    }

private:
    House *m_house;
};

// 别墅工程队
class VillaBuilder : public Builder
{
public:
    VillaBuilder(void)
    {
        m_house = new House;
    }

    virtual void BuildWall(void)
    {
        m_house->setWall("villa wall");
    }

    virtual void BuildDoor(void)
    {
        m_house->setDoor("villa door");
    }

    virtual void BuildWindow(void)
    {
        m_house->setWindow("villa window");
    }

    virtual House* GetHouse(void)
    {
        return m_house;
    }
    
private:
    House *m_house;
};

// 设计师 指挥者，负责建造的逻辑
// 建筑队，干具体的活
class Director
{
public:
    Director(Builder *builder)
    {
        m_build = builder;
    }

    void Construct(void)
    {
        m_build->BuildWall();
        m_build->BuildWindow();
        m_build->BuildDoor();
    }

private:
    Builder * m_build;
};

int main(int argc, char const *argv[])
{
    House       *house = NULL;
    Builder     *builder = NULL;
    Director    *director = NULL;
    cout << "villa build" << endl;
    // 请一个建造别墅的工程队，建造一个别墅
    builder = new VillaBuilder;

    // 设计师 指挥工程队进行建造
    director = new Director(builder);
    // 指挥干活
    director->Construct();
    // 建好 交工
    house = builder->GetHouse();
    // 客户验房
    house->getWindow();
    house->getDoor();
    house->getWall();
    delete house;
    delete builder;

    cout << "flat build" << endl;
    builder = new FlatBuilder;
    director = new Director(builder);
    director->Construct();
    house = builder->GetHouse();
    house->getDoor();
    house->getWall();
    house->getWindow();
    delete house;
    delete builder;

    delete director;
    cout << "builder pattern." << endl;
    return 0;
}
