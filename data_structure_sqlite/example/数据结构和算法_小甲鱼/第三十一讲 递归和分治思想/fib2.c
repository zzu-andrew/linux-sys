#include <stdio.h>

int Fib(int i)
{
	if( i < 2 )
	{
		return i == 0 ? 0 : 1;
	}
	
	return Fib(i-1) + Fib(i-2);
}

int main()
{
	int i;
	for( i=0; i < 40; i++ )
	{
		printf("%d ", Fib(i));
	}
	
	return 0;
}