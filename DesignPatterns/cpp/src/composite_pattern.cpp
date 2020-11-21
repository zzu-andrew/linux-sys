//
// Created by andrew on 2020/11/21.
//
#include <iostream>
#include <string>
#include  <list>

using namespace std;

/*
 * `Composite`模式也叫做组合模式，是构造型的设计模式之一。通过递归的手段构造树形的对象结构，并可以通过一个对象来访问整个对象树。
 * */

class IFile {
public:
    ~IFile() {

    }

    virtual void display() = 0;

    virtual int add(IFile *ifile) = 0;

    virtual int remove(IFile *ifile) = 0;

    virtual list<IFile *> *getChild() = 0;
};

class File : public IFile {
public:
    // explicit 声明只有单个参数的构造函数
    explicit File(string name) {
        m_name = name;
    }

    void display() override {
        cout << m_name << endl;
    }

    int add(IFile *ifile) override {
        return -1;
    }

    int remove(IFile *ifile) override {
        return -1;
    }

    list<IFile *> *getChild() override {
        return NULL;
    }

private:
    string m_name;

};

// 目录节点
class Dir : public IFile {
public:
    explicit Dir(string name) {
        m_name = name;
        m_list = new list<IFile *>;
        m_list->clear();
    }

    void display() override {
        cout << m_name << endl;
    }

    int add(IFile *ifile) override {
        m_list->push_back(ifile);
        return 0;
    }

    int remove(IFile *ifile) override {
        m_list->remove(ifile);
        return 0;
    }

    list<IFile *> *getChild() override {
        return m_list;
    }

private:
//    父目录中有一个或者多个子目录，因此是个链表， 子目录能通过父节点得到
    string m_name;
    list<IFile *> *m_list;
};

// 递归显示树
void showTree(IFile *root, int level) {
    int i = 0;
    if (root == NULL) {
        return;
    }

    for (i == 0; i < level; i++)
    {
        printf("\t");
    }
//    显示根节点
    root->display();
//    若根节点有孩子
//    判断孩子是文件还是文件，显示名字
    list<IFile *> *mylist = root->getChild(); // 获取子目录
    if(mylist != NULL){
        for (auto it = mylist->begin(); it != mylist->end(); it++){
            if((*it)->getChild() == NULL)
            {
//                不是目录就打印文件名 for循环是按照level等级将制表符打印出来
                for(i = 0;i<=level;i++)
                {
                    printf("\t");
                }
                (*it)->display();
            } else
            {
//                是目录就接着递归
                showTree(*it, level+1);
            }
        }
    }

}

int main(int argc, char *argv[]) {

    Dir *root = new Dir("C");
    Dir *dir1 = new Dir("111dir");
    File *aFile = new File("a.txt");

    // 获取root下的节点 孩子集合
    list<IFile *> *mylist = root->getChild();

    root->add(dir1);
    root->add(aFile);
    for(auto it=mylist->begin(); it != mylist->end(); it++)
    {
        (*it)->display();
    }

    Dir *dir2 = new Dir("dir2");
    File *bFile = new File("b.txt");
    dir1->add(dir2);
    dir1->add(bFile);

    cout << "通过 showTree 方式显示root节点下的所有子节点" << endl;

    showTree(root,0);

    cout << "composite pattern" << endl;
    return 0;
}
