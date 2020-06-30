# `AbstractDataTypes`



## C语言的灵活

C语言很灵活，不但有基础数据类型，char、int、double等，还允许程序员自定义类型，如：

定义一个链表使用的数据类型，其中有Node节点和自己需要使用的其他数据信息。

```c
typedef struct node {
    struct node * next;
    ... information ...
} node;
```



## 一个小例子-set

`set`会有这些操作：

```c
#ifndef	SET_H
#define	SET_H

extern const void * Set;

void * add (void * set, const void * element);
void * find (const void * set, const void * element);
void * drop (void * set, const void * element);
int contains (const void * set, const void * element);
unsigned count (const void * set);

#endif
```

这些方法中`set`就是一个抽象数据类型，而这些方法描述的是我们能对`set`进行的操作。

`add`向`set`中添加一个`element`

`find`查找一个`element`是否在`set`中

`drop`将一个`element`从`set`中剔除

`contains`将`find`的结果转变为真假值

`set`类型定义成`void`类型是为了能够像`set`传递任何类型的数据+

### 内存管理函数方法

在`new.h`中定义了内存管理的方法

`new`和`delete`是用来代替`ANSI-C`中的`calloc`还有`free`方法的

```c
#ifndef	NEW_H
#define	NEW_H

void * new (const void * type, ...);
void delete (void * item);

#endif
```



### 对象

想让`set`更有意思，我们需要另外一个抽象数据类型`Object`

```c
#ifndef	OBJECT_H
#define	OBJECT_H

extern const void * Object;		/* new(Object); */

int differ (const void * a, const void * b);

#endif
```



`differ`用于对比`Objects`是否相等。



### 一个小应用

这也是这里说明的重点，不同的实现方式但是表现形式是一样的，这就达到了数据抽象的效果，同一个应用程序框架，底层更换之后，程序还是能正常运行。

```c
#include <stdio.h>

#include "new.h"
#include "Object.h"
#include "Set.h"



int main ()
{	
    /* 新建一个Set对象 */
    void * s = new(Set);  //*s = 10
    /* 将一个新建的Object添加到s中 */
	void * a = add(s, new(Object)); //*a = 1
    /* 将一个新建的Object添加到s中 */  
	void * b = add(s, new(Object));   // *b = 1
    /* 新建一个  Object 对象*/
	void * c = new(Object); //  *c = 10

     /* s中是佛包含 a 是否包含b */
	if (contains(s, a) && contains(s, b))
		puts("ok");
	/* s中是否含有c */
	if (contains(s, c))
		puts("contains?");
	/*  a, add(s, a)) 相同*/
	if (differ(a, add(s, a)))
		puts("differ?");
	
	if (contains(s, drop(s, a)))
		puts("drop?");

	delete(drop(s, b));
	delete(drop(s, c));

	return 0;
}

```



```c
#include <assert.h>
#include <stdio.h>

#include "new.h"
#include "Set.h"
#include "Object.h"

const void * Set;
const void * Object;

#if ! defined MANY || MANY < 1
#define	MANY	10
#endif

/* 定义一个数组用于模拟堆 */
static int heap [MANY];

/* 创建一个对象，这里使用在堆里赋值MANY表示 */
void * new (const void * type, ...)
{	int * p;							/* & heap[1..] */

	for (p = heap + 1; p < heap + MANY; ++ p)
		if (! * p)
			break;
	assert(p < heap + MANY);
	* p = MANY;
	return p;
}
/* 删除一个对象，将对应数组中的值进行清空表示 */
void delete (void * _item)
{	int * item = _item;

	if (item)
	{	assert(item > heap && item < heap + MANY);
		* item = 0;
	}
}
/* 向_set中添加一个  _element元素 */
void * add (void * _set, const void * _element)
{	int * set = _set;
	const int * element = _element;

	assert(set > heap && set < heap + MANY);
	assert(* set == MANY);
	assert(element > heap && element < heap + MANY);

	if (* element == MANY)
		* (int *) element = set - heap;
	else
		assert(* element == set - heap);

	return (void *) element;
}
/* 查找_set中是否有_element */
void * find (const void * _set, const void * _element)
{	const int * set = _set;
	const int * element = _element;

	assert(set > heap && set < heap + MANY);
	assert(* set == MANY);
	assert(element > heap && element < heap + MANY);
	assert(* element);

	return * element == set - heap ? (void *) element : 0;
}
/* 将_set是否包含_element转换为是否为真 */
int contains (const void * _set, const void * _element)
{
	return find(_set, _element) != 0;
}
/* 从_set中删除 _element */
void * drop (void * _set, const void * _element)
{	int * element = find(_set, _element);

	if (element)
		* element = MANY;
	return element;
}
/* 对比a与b是否相同 */
int differ (const void * a, const void * b)
{
	return a != b;
}

```



到这里整个`set`的例子就结束了，接下来看下`Bags`的例子，通过这两个例子的对比你就能明白如何通过设计良好的数据类型也就是对数据进行抽象，来达到代码复用，同一个应用程序，调用同样的接口来达到不同的目的。

----

## 另外一个例子—Bag

`Bag`例子使用的主函数和`set`一样但是实现不一样，达到的效果就是对数据进行抽象之后，使用同一个框架运行不同的底层程序。

在不改变方法的情况下，我们可以改变方法的实现，在`Bag`中我们使用动态内存管理来实现

在`Bag`中`Set`和`Object`表现形式如下，是两个结构体

```c
count -- 用于记录Set中元素的个数，也可以说count是记录有多少次element add到Set中了
struct Set { unsigned count; };
struct Object { unsigned count; struct Set * in; };
```

因为使用动态内存呈现`sets`和`objects`我们需要初始化描述下`Set`和`Object`，`new`可以定位到需要为新的对象申请多少内存。

```c
static const size_t _Set = sizeof(struct Set);
static const size_t _Object = sizeof(struct Object);

const void * Set = & _Set;
const void * Object = & _Object;

```

主函数中申请内存使用的方式是`void * s = new(Set);` `* (const size_t *) type`就相当于`* (const size_t *) Set`大小刚好等于`Set`

`new`函数很好理解就是使用`calloc`申请固定大小的内存，并将内存的指针赋返回给要`New`的对象

```c
void * new (const void * type, ...)
{	const size_t size = * (const size_t *) type;
	void * p = calloc(1, size);

	assert(p);
	return p;
}
```

```bash
The  calloc()  function  allocates  memory for an array of nmemb elements of size bytes each and returns a pointer to the allocated memory.  The memory is set to zero.  If nmemb or size is 0, then calloc() returns  either NULL, or a unique pointer value that can later be successfully passed to free().
```

`delete`方法只是对`free`的一个简单封装而已，直接将需要释放内存的指针传递给`free`就可以了，当然这里只是一个玩具代码，真正使用的代码需要对释放的对象进行合法性检测。

```c
void delete (void * item)
{
	free(item);
}
```

`add`方法将`element`元素`add`到对应的`set`对象中，`add`之后对`set`中的`count`和`element`中的`count`进行递增，用于统计`set`中`add element`个数。

```c

void * add (void * _set, const void * _element)
{	struct Set * set = _set;
	struct Object * element = (void *) _element;

	assert(set);
	assert(element);

	if (! element -> in)
		element -> in = set;
	else
		assert(element -> in == set);
	++ element -> count, ++ set -> count;

	return element;
}
```

`find` 函数作用就是检查对应的`element`是否已经`add`进 `set`了，一旦`add`之后`element -> in == _set`将会成立:accept:

```c

void * find (const void * _set, const void * _element)
{	const struct Object * element = _element;

	assert(_set);
	assert(element);

	return element -> in == _set ? (void *) element : 0;
}
```

`contains`和`Set.c`中实现的一样，`contains`函数依然时对`find`函数的一个封装，`find`函数返回非0的时候也就是在`set`中已经添加了对应的元素`element`

```c
int contains (const void * _set, const void * _element)
{
	return find(_set, _element) != 0;
}
```

<font size=12 color= red>drop</font>函数

```c
void * drop (void * _set, const void * _element)
{	struct Set * set = _set;
	struct Object * element = find(set, _element);

	if (element)
	{	if (-- element -> count == 0)
			element -> in = 0;
		-- set -> count;
	}
	return element;
}
```

`Count`函数，用于提供`set`中`add`的`element`个数

虽然更加快捷的方法是直接调用`set->Count`但是最好不要这样做，这样会破坏数据的封装性。

```c
unsigned count (const void * _set)
{	const struct Set * set = _set;

	assert(set);
	return set -> count;
}
```

`differ`函数

```c
int differ (const void * a, const void * b)
{
	return a != b;
}
```



主函数

```c
#include <stdio.h>

#include "new.h"
#include "Object.h"
#include "Set.h"

int main ()
{	void * s = new(Set);
	void * a = add(s, new(Object));
	void * b = add(s, new(Object));
	void * c = new(Object);

	if (contains(s, a) && contains(s, b))
		puts("ok");

	if (contains(s, c))
		puts("contains?");

	if (differ(a, add(s, a)))
		puts("differ?");

	if (contains(s, drop(s, a)))
		puts("drop?");

	delete(drop(s, b));
	delete(drop(s, c));

	return 0;
}

```



---



执行结果

```bash
andrew@DESKTOP-GDC67HT:/mnt/u/linux-sys/ooc/test/c.01$ ./sets 
ok
andrew@DESKTOP-GDC67HT:/mnt/u/linux-sys/ooc/test/c.01$ ./bags
ok
drop?
```

执行结果可以看出bags比sets多一个drops打印，这是因为a被add了两次，但是sets中无论添加多少次都只是被添加一次，所以drop之后就不在set里面了，但是bags能够添加多次，a添加了两次到那时drop一次，所以a还是在s中。

















































