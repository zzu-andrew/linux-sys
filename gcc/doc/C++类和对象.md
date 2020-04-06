[TOC]

## C++中的类和对象

![](https://img.shields.io/github/forks/zzu-andrew/linux-sys.svg)![](https://img.shields.io/github/license/zzu-andrew/Markdown.svg)![](https://img.shields.io/github/stars/zzu-andrew/linux-sys.svg)![](https://img.shields.io/github/issues/zzu-andrew/linux-sys.svg)

## 抽象和类

**处理复杂生活最简单的方式就是对其进行简化和抽象`-Andrew`**

### 类型

- 决定数据对象需要的内存数量；
- 决定如何解释内存中的位(long和float在内存中占用的位相同但是他们转换为数值的方法不同)；
- 决定可使用数据对象执行的操作或方法

### C++中的类

- 类是一种将抽象转换为用户定义类型的C++工具，它将数据的表示和操纵数据的方法组合成一个整洁的包。



​	在头文件中定义类

```c
// stock00.h -- Stock class interface
// version 00
#ifndef STOCK00_H_
#define STOCK00_H_

#include <string>  

//private 声明的成员只有用成员函数才能访问
//public 声明的成员，使用类的对象的程序都可以访问
class Stock  // class declaration
{
private: 
    std::string company;
    long shares;
    double share_val;
    double total_val;
    //< 内联函数的一种实现方式
    void set_tot() { total_val = shares * share_val; }
public:
    void acquire(const std::string & co, long n, double pr);
    void buy(long num, double price);
    void sell(long num, double price);
    void update(double price);
    void show();
};    // note semicolon at the end

#endif
```



### 实现类成员函数

- 定义成员函数时，使用作用域解析 运算符(::)来标识函数所属的类

- 类方法可以访问类的`private`组件

- 对以上类的声明进行实现

```c
// stock00.cpp -- implementing the Stock class
// version 00
#include <iostream>
#include "stock00.h"

void Stock::acquire(const std::string & co, long n, double pr)
{
    company = co;
    if (n < 0)
    {
        std::cout << "Number of shares can't be negative; "
                  << company << " shares set to 0.\n";
        shares = 0;
    }
    else
        shares = n;
    share_val = pr;
    //< 在类的作用域中， 可以直接调用类中的方法
    set_tot();
}

void Stock::buy(long num, double price)
{
     if (num < 0)
    {
        std::cout << "Number of shares purchased can't be negative. "
             << "Transaction is aborted.\n";
    }
    else
    {
        shares += num;
        share_val = price;
        set_tot();
    }
}

void Stock::sell(long num, double price)
{
    using std::cout;
    if (num < 0)
    {
        cout << "Number of shares sold can't be negative. "
             << "Transaction is aborted.\n";
    }
    else if (num > shares)
    {
        cout << "You can't sell more than you have! "
             << "Transaction is aborted.\n";
    }
    else
    {
        shares -= num;
        share_val = price;
        set_tot();
    }
}

void Stock::update(double price)
{
    share_val = price;
    //< 只有在类的作用域范围内才可以直接使用方法的缩写
    //< 在其他的地方使用类中的方法必须使用，类的作用域进行限定
    set_tot();
}

void Stock::show()
{
    //< 类中可以直接操作函数的私有成员
    std::cout << "Company: " << company
              << "  Shares: " << shares << '\n'
              << "  Share Price: $" << share_val
              << "  Total Worth: $" << total_val << '\n';
}

```

#### 内联方法

1. 定义于类声明中的函数都将自动称为内联函数，因此Stock::set_tot()是一个内联函数。类声明常将短小的成员函数作为内联函数。
2. 在类的声明之外将函数声明为内联函数需要使用`inline`限定符进行限定。



### 使用类

```c
// usestok0.cpp -- the client program
// compile with stock.cpp
#include <iostream>
#include "stock00.h"

int main()
{
    Stock fluffy_the_cat; //< 创建一个对象
    fluffy_the_cat.acquire("NanoSmart", 20, 12.50);
    fluffy_the_cat.show();
    fluffy_the_cat.buy(15, 18.125);
    fluffy_the_cat.show();
    fluffy_the_cat.sell(400, 20.00);
    fluffy_the_cat.show();
    fluffy_the_cat.buy(300000,40.125);
    fluffy_the_cat.show();
    fluffy_the_cat.sell(300000,0.125);
    fluffy_the_cat.show();
    // std::cin.get();
    return 0;
}

```

-----

## 类的构造函数和析构函数

- 类中的数据部分是私有的，因此不能通过直接访问类中的数据成员对其进行初始化，这时就需要使用构造函数和析构函数了

- 为Stock类增加构造函数和析构函数

**声明文件**

```c
// stock10.h � Stock class declaration with constructors, destructor added
#ifndef STOCK1_H_
#define STOCK1_H_
#include <string>
class Stock
{
private:
    std::string company;
    long shares;
    double share_val;
    double total_val;
    void set_tot() { total_val = shares * share_val; }
public:
	//< 构造函数
    Stock();        // default constructor
    Stock(const std::string & co, long n = 0, double pr = 0.0);
    //< 析构函数
    ~Stock();       // noisy destructor
    void buy(long num, double price);
    void sell(long num, double price);
    void update(double price);
    void show();
};

#endif

```

**实现文件**

```c
// stock1.cpp � Stock class implementation with constructors, destructor added
#include <iostream>
#include "stock10.h"

// constructors (verbose versions)
//< 默认构造函数
Stock::Stock()        // default constructor
{
    std::cout << "Default constructor called\n";
    company = "no name";
    shares = 0;
    share_val = 0.0;
    total_val = 0.0;
}

//< 传参构造函数
Stock::Stock(const std::string & co, long n, double pr)
{
    std::cout << "Constructor using " << co << " called\n";
    company = co;

    if (n < 0)
    {
        std::cout << "Number of shares can't be negative; "
                   << company << " shares set to 0.\n";
        shares = 0;
    }
    else
        shares = n;
    share_val = pr;
    set_tot();
}
// class destructor
//< 析构函数
Stock::~Stock()        // verbose class destructor
{
    std::cout << "Bye, " << company << "!\n";
}

// other methods
//< 方法定义
void Stock::buy(long num, double price)
{
     if (num < 0)
    {
        std::cout << "Number of shares purchased can't be negative. "
             << "Transaction is aborted.\n";
    }
    else
    {
        shares += num;
        share_val = price;
        set_tot();
    }
}

void Stock::sell(long num, double price)
{
    using std::cout;
    if (num < 0)
    {
        cout << "Number of shares sold can't be negative. "
             << "Transaction is aborted.\n";
    }
    else if (num > shares)
    {
        cout << "You can't sell more than you have! "
             << "Transaction is aborted.\n";
    }
    else
    {
        shares -= num;
        share_val = price;
        set_tot();
    }
}

void Stock::update(double price)
{
    share_val = price;
    set_tot();
}

void Stock::show()
{
    using std::cout;
    using std::ios_base;
    // set format to #.###
    ios_base::fmtflags orig = 
        cout.setf(ios_base::fixed, ios_base::floatfield); 
    std::streamsize prec = cout.precision(3);

    cout << "Company: " << company
        << "  Shares: " << shares << '\n';
    cout << "  Share Price: $" << share_val;
    // set format to #.##
    cout.precision(2);
    cout << "  Total Worth: $" << total_val << '\n';

    // restore original format
    cout.setf(orig, ios_base::floatfield);
    cout.precision(prec);
}

```

**方法的调用**

```c
// usestok1.cpp -- using the Stock class
// compile with stock10.cpp
#include <iostream>
#include "stock10.h"

int main()
{
  { //< 加这个代码块是为了显示析构函数的调用
    using std::cout;
    cout << "Using constructors to create new objects\n";
     //< 定义对象
    //< 紧凑的对象定义的方式
    Stock stock1("NanoSmart", 12, 20.0);            // syntax 1
    stock1.show();
    //< 显示的调用构造函数，定义一个类
    Stock stock2 = Stock ("Boffo Objects", 2, 2.0); // syntax 2
    stock2.show();

    cout << "Assigning stock1 to stock2:\n";
    stock2 = stock1;
    cout << "Listing stock1 and stock2:\n";
    stock1.show();
    stock2.show();

    cout << "Using a constructor to reset an object\n";
    //< 构造函数不仅仅可以用来初始化，该方法是构造函数创建一个临时的新的对象，并对其进行初始化
    //< 将初始化之后的临时对象赋值给对象stock1
     //< 赋值结束之后程序调用析构函数，删除该临时对象
    //< 因此此处有析构函数的调用
    stock1 = Stock("Nifty Foods", 10, 50.0);    // temp object
    cout << "Revised stock1:\n";
    stock1.show();
    cout << "Done\n";
  }
	// std::cin.get();
    return 0; 
}

```

### `const`成员函数

- 有时候只是想调用成员函数获取值或者调用成员函数显示一下变量，这时可以使用`const`对函数进行修饰， C++中是使用将`const`放在成员函数后面，如下：

```c
 void show() const; //< 确保该函数不修改调用对象
```

- 这种形式定义的函数被称为`const`成员函数，就像应尽可能将`cosnt`引用和指针用作函数的形参一样，只要类方法不修改调用对象，就应该将其声明为`const`，从现在起我们应该准守这一规则。

### 构造函数和析构函数小结

- 构造函数是一种特殊的成员函数，在创建类对象时被调用，构造函数的名称和类名相同。可以通过函数重载创建多个同名的构造函数，条件是每个函数的特征标(参数列表)都不同，另外构造函数没有声明类型，通常构造函数用于初始化类对象的成员，初始化应与构造函数的参数列表匹配。

## `this`指针

- 有时候一个类可能定义多个对象，这种情况下就需要使用C++的this指针
- `this`指针指向用来调用成员函数的对象(this被称为隐式成员函数传递方法)

**this的简单示例**

*头文件*

```c
// stock20.h -- augmented version
#ifndef STOCK20_H_
#define STOCK20_H_
#include <string>

class Stock
{
private:
    std::string company;
    int shares;
    double share_val;
    double total_val;
    void set_tot() { total_val = shares * share_val; }
public:
  //  Stock();        // default constructor
    Stock(const std::string & co, long n = 0, double pr = 0.0);
    ~Stock();       // do-nothing destructor
    void buy(long num, double price);
    void sell(long num, double price);
    void update(double price);
    void show()const;
    const Stock & topval(const Stock & s) const;
};

#endif

```

**源文件**

```c
// stock20.cpp -- augmented version
#include <iostream>
#include "stock20.h"
using namespace std;
// constructors
Stock::Stock()        // default constructor
{
    shares = 0;
    share_val = 0.0;
    total_val = 0.0;
}

Stock::Stock(const std::string & co, long n, double pr)
{
    company = co;
    if (n < 0)
    {
        std::cout << "Number of shares can't be negative; "
                   << company << " shares set to 0.\n";
        shares = 0;
    }
    else
        shares = n;
    share_val = pr;
    set_tot();
}

// class destructor
Stock::~Stock()        // quiet class destructor
{
}

// other methods
void Stock::buy(long num, double price)
{
     if (num < 0)
    {
        std::cout << "Number of shares purchased can't be negative. "
             << "Transaction is aborted.\n";
    }
    else
    {
        shares += num;
        share_val = price;
        set_tot();
    }
}

void Stock::sell(long num, double price)
{
    using std::cout;
    if (num < 0)
    {
        cout << "Number of shares sold can't be negative. "
             << "Transaction is aborted.\n";
    }
    else if (num > shares)
    {
        cout << "You can't sell more than you have! "
             << "Transaction is aborted.\n";
    }
    else
    {
        shares -= num;
        share_val = price;
        set_tot();
    }
}

void Stock::update(double price)
{
    share_val = price;
    set_tot();
}

void Stock::show() const
{
    using std::cout;
    using std::ios_base;
    // set format to #.###
    ios_base::fmtflags orig = 
        cout.setf(ios_base::fixed, ios_base::floatfield); 
    std::streamsize prec = cout.precision(3);

    cout << "Company: " << company
        << "  Shares: " << shares << '\n';
    cout << "  Share Price: $" << share_val;
    // set format to #.##
    cout.precision(2);
    cout << "  Total Worth: $" << total_val << '\n';

    // restore original format
    cout.setf(orig, ios_base::floatfield);
    cout.precision(prec);
}

const Stock & Stock::topval(const Stock & s) const
{
    if (s.total_val > total_val)
        return s;
    else
        //< 若是调用方法的对象比较大就直接返回，该对象的引用
        //< this指向调用方法对象的地址， *this则是对象的地址
        return *this; 
}

```



-----

## 对象数组

- 用户通常常见一个类的多个对象，可以创建独立的对象变量，但是闯将对象数组将更加合适。

- 初始化对象数组的方案是，首先使用默认构造函数创建数组元素，然后花括号中的构造函数将创建临时对象，然后临时对象内容复制到对应的元素中。因此、要创建对象数组，则这个类必须由默认构造函数。

```c
// usestok2.cpp -- using the Stock class
// compile with stock20.cpp
#include <iostream>
#include "stock20.h"

const int STKS = 4;
int main()
{
    {//< 使用大括号括起来是为了能够在主函数退出前就调用构造函数
// create an array of initialized objects
    Stock stocks[STKS] = { //< 使用列表就行初始化
        Stock("NanoSmart", 12, 20.0), /* 创建一个临时变量，然后将临时变量的值复制给数组的对象 */
        Stock("Boffo Objects", 200, 2.0),
        Stock("Monolithic Obelisks", 130, 3.25),
        Stock("Fleep Enterprises", 60, 6.5)
        };

    std::cout << "Stock holdings:\n";
    int st;
    for (st = 0; st < STKS; st++)
        stocks[st].show();
// set pointer to first element
    const Stock * top = &stocks[0];
    for (st = 1; st < STKS; st++)
        top = &top->topval(stocks[st]);
// now top points to the most valuable holding
    std::cout << "\nMost valuable holding:\n";
	top->show();}
    // std::cin.get();
    return 0; 
}

```

## 类的作用域

- 在类中定义的名称作用域都为整个类，类的作用域意味着不能在外部直接访问类的成员，公有成员也是如此，也就是说调用公有成员函数，也必须通过对象。

- 在类声明或成员函数定义中，可以使用未修饰的成员名称(未限定的名称)，

## 抽象数据类型

- 程序员通常需要定义抽象的类，来表示更加通用的概念，而不是向`Stock`一样定义的非常具体。



```c
// stack.h -- class definition for the stack ADT
#ifndef STACK_H_
#define STACK_H_

typedef unsigned long Item;

class Stack
{
private:
	//< 无名的枚举型并不实际创建枚举型类成员
    enum {MAX = 10};    // constant specific to class
    //< 使用数组实现栈，但是在公有部分隐藏了栈的实现细节
    //< 因此可以使用动态数组实现，也不需要更改代码的借口实现的细节
    Item items[MAX];    // holds stack items
    int top;            // index for top stack item
public:
    Stack();
    bool isempty() const;
    bool isfull() const;
    // push() returns false if stack already is full, true otherwise
    bool push(const Item & item);   // add item to stack
    // pop() returns false if stack already is empty, true otherwise
    bool pop(Item & item);          // pop top into item
};
#endif

```



**源代码实现**

```c
// stack.cpp -- Stack member functions
#include "stack.h"
Stack::Stack()    // create an empty stack
{
    top = 0;
}

bool Stack::isempty() const
{
    return top == 0;
}

bool Stack::isfull() const
{
    return top == MAX;
}

bool Stack::push(const Item & item) 
{
    if (top < MAX)
    {
        items[top++] = item;
        return true;
    }
    else
        return false;
}

bool Stack::pop(Item & item)
{
    if (top > 0)
    {
        item = items[--top];
        return true;
    }
    else
        return false; 
}
yhhgfik

```



**使用栈**

```c
// stacker.cpp -- testing the Stack class
#include <iostream>
#include <cctype>  // or ctype.h
#include "stack.h"
int main()
{
    using namespace std;
    Stack st; // create an empty stack
    char ch;
    unsigned long po;
    cout << "Please enter A to add a purchase order,\n"
        << "P to process a PO, or Q to quit.\n";
    while (cin >> ch && toupper(ch) != 'Q')
    {
        while (cin.get() != '\n')   
            continue;
        if (!isalpha(ch))
        {
            cout << '\a';
            continue;
        }
        switch(ch)
        {
             case 'A':
             case 'a': cout << "Enter a PO number to add: ";
                       cin >> po;
                       if (st.isfull())
                           cout << "stack already full\n";
                       else
                           st.push(po);
                       break;
             case 'P':
             case 'p': if (st.isempty())
                           cout << "stack already empty\n";
                       else {
                           st.pop(po);
                           cout << "PO #" << po << " popped\n";
                       }
                       break;
        }
        cout << "Please enter A to add a purchase order,\n"
             << "P to process a PO, or Q to quit.\n";
    }
    cout << "Bye\n";
    return 0; 
}

```









































































