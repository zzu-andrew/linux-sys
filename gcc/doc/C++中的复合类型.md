[TOC]

# 重温C++ 复合类型

## 在程序中 使用结构体

```c
// structur.cpp -- a simple structure
#include <iostream>
struct inflatable   // structure declaration
{
    char name[20];
    float volume;
    double price;
};

int main()
{
    using namespace std;
    inflatable guest =
    {
        "Glorious Gloria",  // name value
        1.88,               // volume value
        29.99               // price value
    };  // guest is a structure variable of type inflatable
// It's initialized to the indicated values
    inflatable pal =
    {
        "Audacious Arthur",
        3.12,
        32.99
    };  // pal is a second variable of type inflatable
// NOTE: some implementations require using
// static inflatable guest =

    cout << "Expand your guest list with " << guest.name;
    cout << " and " << pal.name << "!\n";
// pal.name is the name member of the pal variable
    cout << "You can have both for $";
    cout << guest.price + pal.price << "!\n";
    // cin.get();
    return 0; 
}

```

## 结构体赋值

```c
// assgn_st.cpp -- assigning structures
#include <iostream>
struct inflatable
{
    char name[20];
    float volume;
    double price;
};
int main()
{
    using namespace std;
    inflatable bouquet =
    {
        "sunflowers",
        0.20,
        12.49
    };
    inflatable choice;
    cout << "bouquet: " << bouquet.name << " for $";
    cout << bouquet.price << endl;
	//C++ 11中结构体可以直接赋值
    choice = bouquet;  // assign one structure to another
    cout << "choice: " << choice.name << " for $";
    cout << choice.price << endl;
    // cin.get();
    return 0; 
}

```

## 结构体数组

```c
// arrstruc.cpp -- an array of structures
#include <iostream>
struct inflatable
{
    char name[20];
    float volume;
    double price;
};
int main()
{
    using namespace std;
    //< guests 是一个结构体数组，类型是 inflatable
    inflatable guests[2] =          // initializing an array of structs
    {
        {"Bambi", 0.5, 21.99},      // first structure in array
        {"Godzilla", 2000, 565.99}  // next structure in array
    };
	//< guests可以使用据点访问结构体相应的成员
    cout << "The guests " << guests[0].name << " and " << guests[1].name
         << "\nhave a combined volume of "
         << guests[0].volume + guests[1].volume << " cubic feet.\n";
    // cin.get();
    return 0; 
}

```

## 结构体中位字段 

* 与C语言一样C++也允许指定占用特定位数的结构体成员，这使得创建与某个硬件设备上寄存器对应的数据结构非常方便，字段的类型为整数或者枚举，接下来是冒号，冒号后面是一个数字，它指定使用的位数，可以使用没有名称的字段来提供间距，每个成员都被称为位字段(bit field)

```c
struct torgle_register
{
    unsigned int SN : 4;// 4bit for SN value
    unsigned int : 4;//4 bits unused
    bool goodIn :1; //valid input (1 bit)
    bool goodTorgle : 1;//successful torgling
};
```

## 共用体

- 共用体是一种数据格式，它能够存储不同的数据类型，但是只能同时存储其中一种数据类型
- 可以采用共用提的特性，就能在传参的时候既能传入浮点型，也能传入整形，或者字符串。

## 枚举

- C++的enum工具提供了另一种创建符号常量的方式，这种方式可以代替const，它还允许定义新类型，但是必须安严格的限制进行，使用enum的句法与使用结构体相似。

```c
enum spectrum {red, orange , yellow, green, blue, violet, indigo, ultraviolet}
```

**这条语句完成了两件事情**

1. 让spectrum称为新类型的名称；spectrum被称为枚举，就像struct被称为结构一样
2. 将 red, orange, yellow等作为符号常量
- 可以使用枚举名来声明这种类型的变量；

  ` specrum band;// band a veriable of type spectrum`

  

- 如果只是想使用枚举型常量，而不想使用枚举型变量，则可以按照下面这种形式定义

```c
enum {red, orange , yellow, green, blue, violet, indigo, ultraviolet}
```

## 指针

```c
// address.cpp -- using the & operator to find addresses
#include <iostream>
int main()
{
    using namespace std;
    int donuts = 6;
    double cups = 4.5;

    cout << "donuts value = " << donuts;
    cout << " and donuts address = " << &donuts << endl;
// NOTE: you may need to use unsigned (&donuts)
// and unsigned (&cups)
    cout << "cups value = " << cups;
    cout << " and cups address = " << &cups << endl;
    // cin.get();
    return 0; 
}

```

## 如何声明一个指针

```c
// pointer.cpp -- our first pointer variable
#include <iostream>
int main()
{
    using namespace std;
    int updates = 6;        // declare a variable
    int * p_updates;        // declare pointer to an int

    p_updates = &updates;   // assign address of int to pointer

// express values two ways
    cout << "Values: updates = " << updates;
    cout << ", *p_updates = " << *p_updates << endl;

// express address two ways
    cout << "Addresses: &updates = " << &updates;
    cout << ", p_updates = " << p_updates << endl;

// use pointer to change value
    *p_updates = *p_updates + 1;
    cout << "Now updates = " << updates << endl;
    // cin.get();
    return 0; 
}

```

-----

```c
$ ./a.out 
Values: updates = 6, *p_updates = 6
Addresses: &updates = 0x7fffbadc28dc, p_updates = 0x7fffbadc28dc
Now updates = 7

```



## 将指针初始化为一个地址

```c
// init_ptr.cpp -- initialize a pointer
#include <iostream>
int main()
{
    using namespace std;
    int higgens = 5;
    int * pt = &higgens;

    cout << "Value of higgens = " << higgens
         << "; Address of higgens = " << &higgens << endl;
    cout << "Value of *pt = " << *pt
         << "; Value of pt = " << pt << endl;
    // cin.get();
    return 0; 
}

```



**==警告==**

- 一定要在对指针应用解除引用运算符(*)，之前，将指针初始化为一个确定的、适当的地址，这时关于使用指针的金科玉律

## 使用new来分配内存

```c
//< 运行时分配内存
int * pn = new int;
typeName * Pointer_name = new typeName;

```

- 将new用于两种不同的类型

```c
// use_new.cpp -- using the new operator
#include <iostream>
int main()
{
    using namespace std;
    int nights = 1001;
    int * pt = new int;         // allocate space for an int
    *pt = 1001;                 // store a value there

    cout << "nights value = ";
    cout << nights << ": location " << &nights << endl;
    cout << "int ";
    cout << "value = " << *pt << ": location = " << pt << endl;

    double * pd = new double;   // allocate space for a double
    *pd = 10000001.0;           // store a double there

    cout << "double ";
    cout << "value = " << *pd << ": location = " << pd << endl;
    cout << "location of pointer pd: " << &pd << endl;
    cout << "size of pt = " << sizeof(pt);
    cout << ": size of *pt = " << sizeof(*pt) << endl;
    cout << "size of pd = " << sizeof pd;
    cout << ": size of *pd = " << sizeof(*pd) << endl;
    // cin.get();
    return 0;
}

```

```bash
nights value = 1001: location 0x7ffc082d2304
int value = 1001: location = 0x17a8c20
double value = 1e+07: location = 0x17a9050
location of pointer pd: 0x7ffc082d2308
size of pt = 8: size of *pt = 4
size of pd = 8: size of *pd = 8

```

## 指针和数组之间的差别

```c
// arraynew.cpp -- using the new operator for arrays
//< c/C++中使用指针来处理数组，两者基本上相同，但是还是由细微的差别
#include <iostream>
int main()
{
    using namespace std;
    double * p3 = new double [3]; // space for 3 doubles
    p3[0] = 0.2;                  // treat p3 like an array name
    p3[1] = 0.5;
    p3[2] = 0.8;
    cout << "p3[1] is " << p3[1] << ".\n";
    //< 指针可以进行加减操作，但是数组不可以
    p3 = p3 + 1;                  // increment the pointer
    cout << "Now p3[0] is " << p3[0] << " and ";
    cout << "p3[1] is " << p3[1] << ".\n";
    p3 = p3 - 1;                  // point back to beginning
    delete [] p3;                 // free the memory
    // cin.get();
    return 0; 
}

```



## 指针、数组和指针算术

指针和数组基本上等价的原因在于指针算术(pointer arithmetic)和C++内部处理数组的方式，指针算术是按照步长进行增减的，和数组的增减方式一样，C++底层将数组解释为地址：

```c
// addpntrs.cpp -- pointer addition
#include <iostream>
int main()
{
    using namespace std;
    double wages[3] = {10000.0, 20000.0, 30000.0};
    short stacks[3] = {3, 2, 1};

// Here are two ways to get the address of an array
    double * pw = wages;     // name of an array = address
    short * ps = &stacks[0]; // or use address operator
// with array element
    cout << "pw = " << pw << ", *pw = " << *pw << endl;
    pw = pw + 1;
    cout << "add 1 to the pw pointer:\n";
    cout << "pw = " << pw << ", *pw = " << *pw << "\n\n";

    cout << "ps = " << ps << ", *ps = " << *ps << endl;
    ps = ps + 1;
    cout << "add 1 to the ps pointer:\n";
    cout << "ps = " << ps << ", *ps = " << *ps << "\n\n";

    cout << "access two elements with array notation\n";
    cout << "stacks[0] = " << stacks[0] 
         << ", stacks[1] = " << stacks[1] << endl;
    cout << "access two elements with pointer notation\n";
    cout << "*stacks = " << *stacks
         << ", *(stacks + 1) =  " << *(stacks + 1) << endl;

    cout << sizeof(wages) << " = size of wages array\n";
    cout << sizeof(pw) << " = size of pw pointer\n";
    // cin.get();
    return 0; 
}

```

**程序输出**

```bash
pw = 0x7ffd05782530, *pw = 10000
add 1 to the pw pointer:
pw = 0x7ffd05782538, *pw = 20000

ps = 0x7ffd05782520, *ps = 3
add 1 to the ps pointer:
ps = 0x7ffd05782522, *ps = 2

access two elements with array notation
stacks[0] = 3, stacks[1] = 2
access two elements with pointer notation
*stacks = 3, *(stacks + 1) =  2
24 = size of wages array
8 = size of pw pointer
```

- 程序解释，在大多数情况下， C++将数组名解释为数组的第一个元素的地址

## 指针和字符串

```c
// ptrstr.cpp -- using pointers to strings
#include <iostream>
#include <cstring>              // declare strlen(), strcpy()
int main()
{
    using namespace std;
    char animal[20] = "bear";   // animal holds bear
    const char * bird = "wren"; // bird holds address of string
    char * ps;                  // uninitialized

    cout << animal << " and ";  // display bear
    cout << bird << "\n";       // display wren
    // cout << ps << "\n";      //may display garbage, may cause a crash

    cout << "Enter a kind of animal: ";
    cin >> animal;              // ok if input < 20 chars
    // cin >> ps; Too horrible a blunder to try; ps doesn't
    //            point to allocated space

    ps = animal;                // set ps to point to string
    cout << ps << "!\n";       // ok, same as using animal
    cout << "Before using strcpy():\n";
    
    //< 如果向cout提供的是一个字符串指针 cout将打印出字符串  如果向打印出地址必须强制转换为 (int *)类型才行
    cout << animal << " at " << (int *) animal << endl;
    cout << ps << " at " << (int *) ps << endl;

    ps = new char[strlen(animal) + 1];  // get new storage
    strcpy(ps, animal);         // copy string to new storage
    cout << "After using strcpy():\n";
    cout << animal << " at " << (int *) animal << endl;
    cout << ps << " at " << (int *) ps << endl;
    delete [] ps;
    // cin.get();
    // cin.get();
    return 0; 
}

```

## 使用new创建动态结构

```c
// newstrct.cpp -- using new with a structure
#include <iostream>
struct inflatable   // structure definition
{
    char name[20];
    float volume;
    double price;
};
int main()
{
    using namespace std;
    inflatable * ps = new inflatable; // allot memory for structure
    cout << "Enter name of inflatable item: ";
    //< 使用get函数获取ps->name的值
    cin.get(ps->name, 20);            // method 1 for member access
    cout << "Enter volume in cubic feet: ";
    cin >> (*ps).volume;              // method 2 for member access
    cout << "Enter price: $";
    cin >> ps->price;
    cout << "Name: " << (*ps).name << endl;              // method 2
    cout << "Volume: " << ps->volume << " cubic feet\n"; // method 1
    cout << "Price: $" << ps->price << endl;             // method 1
    delete ps;                        // free memory used by structure
    // cin.get();
    // cin.get();
    return 0; 
}

```



## delete使用示例

```c
// delete.cpp -- using the delete operator
#include <iostream>
#include <cstring>      // or string.h
using namespace std;
char * getname(void);   // function prototype
int main()
{
    char * name;        // create pointer but no storage

    name = getname();   // assign address of string to name
    cout << name << " at " << (int *) name << "\n";
    delete [] name;     // memory freed

    name = getname();   // reuse freed memory
    cout << name << " at " << (int *) name << "\n";
    delete [] name;     // memory freed again
    // cin.get();
    // cin.get();
    return 0;
}

//< 申请内存可以返回指针的形式，但是要是使用参数的形式就必须使用指向指针的指针
//< 因为C++传入的参数会使用临时变量代替
char * getname()        // return pointer to new string
{	
    //< 自动变量是局部变量，他的作用域就是它所包含的代码块
    //< 自动变量常存储在栈中，这意味着执行代码块时，其中的变量将依次添加到栈中，
    //< 离开代码块是将按照相反的顺序释放这些变量，这被称为后进先出的(LIFO),因此在程序执行的过程中，栈将不
    //< 增大和缩小
    char temp[80];      // temporary storage
    cout << "Enter last name: ";
    cin >> temp;
    char * pn = new char[strlen(temp) + 1];
    strcpy(pn, temp);   // copy string into smaller space

    return pn;          // temp lost when function ends
}


```



## 类型组合

```c
// mixtypes.cpp --some type combinations
#include <iostream>

struct antarctica_years_end
{
    int year;
 /* some really interesting data, etc. */
};

int main()
{
    antarctica_years_end s01, s02, s03; 
    s01.year = 1998;
    antarctica_years_end * pa = &s02;
    pa->year = 1999;
    antarctica_years_end trio[3]; // array of 3 structures
    trio[0].year = 2003;
    std::cout << trio->year << std::endl;
    const antarctica_years_end * arp[3] = {&s01, &s02, &s03};
    std::cout << arp[1]->year << std::endl;
    const antarctica_years_end ** ppa = arp; 
    auto ppb = arp; // C++0x automatic type deduction
// or else use const antarctica_years_end ** ppb = arp; 
    std::cout << (*ppa)->year << std::endl;
    std::cout << (*(ppb+1))->year << std::endl;
    // std::cin.get();
    return 0;
}
```



## 数组的替代品

### 模板类vector

- 模板类类似于string类，也是一种动态数组，可以在运行阶段设置vector对象的长度，可以再末尾附加新数据，还可以在中间插入新数据，基本上它可以是使用new创建动态数组的替代品，实际上的vector确实是用new和delete来管理内存，但是这种工作自动完成的。

1. 使用vector模板必须包含头文件vector，其次vector也在名称空间std中，因此、可以使用using编译指令、using声明，或者使用std::vector。模板中使用不同的语法来之处它存储的数据类型

`vector<typeName> vt(n_elem)`

> vt为vector对象，它存储n_elem个类型为 typeName的元素

### 模板类array

- 使用vector功能比数组强大，但是付出的代价就是效率稍低，鉴于此C++11提供与数组一样的模板类，与数组一样是固定长度的，也是使用栈而不是自由存储区

**对比数组vector和array的不同**

```c
// choices.cpp -- array variations
#include <iostream>
#include <vector>   // STL C++98
#include <array>    // C++0x
int main()
{
    using namespace std;
// C, original C++
    double a1[4] = {1.2, 2.4, 3.6, 4.8};
// C++98 STL
    vector<double> a2(4);   // create vector with 4 elements
// no simple way to initialize in C98
    a2[0] = 1.0/3.0;
    a2[1] = 1.0/5.0;
    a2[2] = 1.0/7.0;
    a2[3] = 1.0/9.0;
// C++0x -- create and initialize array object
    array<double, 4> a3 = {3.14, 2.72, 1.62, 1.41};  
    array<double, 4> a4;
    //< array 同样大小的情况下可以直接进行赋值 
    a4 = a3;     // valid for array objects of same size
// use array notation
    cout << "a1[2]: " << a1[2] << " at " << &a1[2] << endl;
    cout << "a2[2]: " << a2[2] << " at " << &a2[2] << endl;
    cout << "a3[2]: " << a3[2] << " at " << &a3[2] << endl;
    cout << "a4[2]: " << a4[2] << " at " << &a4[2] << endl;
// misdeed
    a1[-2] = 20.2; //< 编译没有问题C++也不做数组超界限的处理
    cout << "a1[-2]: " << a1[-2] <<" at " << &a1[-2] << endl;
    cout << "a3[2]: " << a3[2] << " at " << &a3[2] << endl;
    cout << "a4[2]: " << a4[2] << " at " << &a4[2] << endl;
    //  cin.get();
    return 0;
}
```









