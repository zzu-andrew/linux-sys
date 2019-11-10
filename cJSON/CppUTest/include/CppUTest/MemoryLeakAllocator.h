/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
#ifndef D_MemoryLeakAllocator_h
#define D_MemoryLeakAllocator_h

struct MemoryLeakNode;

class MemoryLeakAllocator
{
public:
	virtual char* alloc_memory(size_t size, const char* file, int line)=0;
	virtual void free_memory(char* memory, const char* file, int line)=0;

	virtual const char* name()=0;
	virtual const char* alloc_name()=0;
	virtual const char* free_name()=0;

	virtual bool isOfEqualType(MemoryLeakAllocator* allocator);
	virtual ~MemoryLeakAllocator()
	{
	}

	virtual bool allocateMemoryLeakNodeSeparately();
	virtual char* allocMemoryLeakNode(size_t size);
	virtual void freeMemoryLeakNode(char* memory);

	static void setCurrentNewAllocator(MemoryLeakAllocator* allocator);
	static MemoryLeakAllocator* getCurrentNewAllocator();
	static void setCurrentNewAllocatorToDefault();

	static void setCurrentNewArrayAllocator(MemoryLeakAllocator* allocator);
	static MemoryLeakAllocator* getCurrentNewArrayAllocator();
	static void setCurrentNewArrayAllocatorToDefault();

	static void setCurrentMallocAllocator(MemoryLeakAllocator* allocator);
	static MemoryLeakAllocator* getCurrentMallocAllocator();
	static void setCurrentMallocAllocatorToDefault();

private:
	static MemoryLeakAllocator* currentNewAllocator;
	static MemoryLeakAllocator* currentNewArrayAllocator;
	static MemoryLeakAllocator* currentMallocAllocator;
};

class StandardMallocAllocator: public MemoryLeakAllocator
{
public:
	virtual char* alloc_memory(size_t size, const char* file, int line);
	virtual void free_memory(char* memory, const char* file, int line);

	const char* name();
	const char* alloc_name();
	const char* free_name();

	virtual bool allocateMemoryLeakNodeSeparately();

	static MemoryLeakAllocator* defaultAllocator();
};

class StandardNewAllocator: public MemoryLeakAllocator
{
public:
	virtual char* alloc_memory(size_t size, const char* file, int line);
	virtual void free_memory(char* memory, const char* file, int line);

	const char* name();
	const char* alloc_name();
	const char* free_name();

	static MemoryLeakAllocator* defaultAllocator();
};

class StandardNewArrayAllocator: public MemoryLeakAllocator
{
public:
	virtual char* alloc_memory(size_t size, const char* file, int line);
	virtual void free_memory(char* memory, const char* file, int line);

	const char* name();
	const char* alloc_name();
	const char* free_name();

	static MemoryLeakAllocator* defaultAllocator();
};

class NullUnknownAllocator: public MemoryLeakAllocator
{
public:
	virtual char* alloc_memory(size_t size, const char* file, int line);
	virtual void free_memory(char* memory, const char* file, int line);

	const char* name();
	const char* alloc_name();
	const char* free_name();

	static MemoryLeakAllocator* defaultAllocator();
};

#endif
