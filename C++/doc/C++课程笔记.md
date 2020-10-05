## 引用



### 指针引用

- 因为入参的`copy`特性，`C`语言中常使用二级指针获取函数内部资源

```c
int getTeacher(Teacher **p)
```

- `C++`中通常使用引用来达到同样的效果

```c++
int getTeacher2(Teacher* &myp)
```

### 常引用

```c++
//普通引用
int  a = 10;
int &b = a;

//常引用 就是让引用变量拥有只读属性
int  x = 20;
const int &y = x;

// 引用就是给一个内存取个别名
int &m = 41;   // 编译报错，因为普通数值是没有内存地址的，所以也不能使用引用取别名
// 但是当使用一个const引用的时候，会给堆数值的引用非配内存空间
const int &m = 43;  //c++编译器 会 分配内存空间 
```





### 运算符重载

`&&` `||`不能进行重载，因为该运算符的截断功能无法使用运算符重载实现。

```c++
// 类定义

#include <iostream>
using namespace std;

//c中没有字符串 字符串类(c风格的字符串)
//空串 ""
class  MyString
{
	friend ostream& operator<<(ostream &out, MyString &s);
	friend istream& operator>>(istream &in, MyString &s);
public:
	MyString(int len = 0);
	MyString(const char *p);
	MyString(const MyString& s);
	~MyString();

public: //重载=号操作符
	MyString& operator=(const char *p);
	MyString& operator=(const MyString &s);
	char& operator[] (int index);

public: //重载 == !== 
	bool operator==(const char *p) const;
	bool operator==(const MyString& s) const;
	bool operator!=(const char *p) const;
	bool operator!=(const MyString& s) const;

public:
	int operator<(const char *p);
	int operator>(const char *p);
	int operator<(const MyString& s);
	int operator>(const MyString& s);

	//把类的指针 露出来
public:
	char *c_str()
	{
		return m_p;
	}
	const char *c_str2()
	{
		return m_p;
	}
	int length()
	{
		return m_len;
	}
private:
	int		m_len;
	char	 *m_p;

};

```

```c++
#define _CRT_SECURE_NO_WARNINGS

#include "MyString.h"
#include <string.h>

ostream& operator<<(ostream &out, MyString &s)
{
	out<<s.m_p;
	return out;
}
istream& operator>>(istream &in, MyString &s)
{
	cin>>s.m_p;
	return in;
}

MyString::MyString(int len)
{
	if (len == 0)
	{
		m_len = 0;
		m_p = new char[m_len + 1];
		strcpy(m_p, "");
	}
	else
	{
		m_len = len;
		m_p = new char[m_len + 1];
		memset(m_p, 0, m_len);
	}

}

MyString::MyString(const char *p)
{
	if (p == NULL)
	{
		m_len = 0;
		m_p = new char[m_len + 1];
		strcpy(m_p, "");
	}
	else
	{
		m_len = strlen(p);
		m_p = new char[m_len + 1];
		strcpy(m_p, p);
	}
}

//拷贝构造函数
//MyString s3 = s2;

MyString::MyString(const MyString& s)
{
	this->m_len = s.m_len;
	this->m_p = new char[m_len +1];
	strcpy(this->m_p, s.m_p);
}

MyString::~MyString()
{
	if (m_p != NULL)
	{
		delete [] m_p;
		m_p = NULL;
		m_len = 0;
	}
}

//// s4 = "s2222";
MyString& MyString::operator=(const char *p)
{
	//1 旧内存释放掉
	if (m_p != NULL)
	{
		delete [] m_p;
		m_len = 0;
	}
	//2 根据p分配内存
	
	if (p == NULL)
	{
		m_len = 0;
		m_p = new char[m_len + 1];
		strcpy(m_p, "");
	}
	else
	{
		m_len = strlen(p);
		m_p = new char[m_len + 1];
		strcpy(m_p, p);
	}
	return *this;
}

// s4 = s2;
MyString& MyString::operator=(const MyString &s)
{
	//1 旧内存释放掉
	if (m_p != NULL)
	{
		delete [] m_p;
		m_len = 0;
	}
	//2 根据s分配内存
	m_len = s.m_len;
	m_p = new char[m_len + 1];
	strcpy(m_p, s.m_p);

	return *this;
}

char& MyString::operator[] (int index)
{
	return m_p[index];
}

//if (s2 == "s222222")
bool MyString::operator==(const char *p) const
{
	if (p == NULL)
	{
		if (m_len == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (m_len == strlen(p))
		{
			return !strcmp(m_p, p);
		}
		else
		{
			return false;
		}
	}
}

bool MyString::operator!=(const char *p) const
{
	return !(*this == p);
}


bool MyString::operator==(const MyString& s)  const
{
	if (m_len != s.m_len)
	{
		return false;
	}
	return !strcmp(m_p, s.m_p);
}

bool MyString::operator!=(const MyString& s) const
{
	return !(*this == s);
}


//if (s3 < "bbbb")
int MyString::operator<(const char *p)
{
	return strcmp(this->m_p , p);
}

int MyString::operator>(const char *p)
{
	return strcmp(p, this->m_p);
}

int MyString::operator<(const MyString& s)
{
	return strcmp(this->m_p , s.m_p);
}

int MyString::operator>(const MyString& s)
{
	return  strcmp(s.m_p, m_p);
}




```











