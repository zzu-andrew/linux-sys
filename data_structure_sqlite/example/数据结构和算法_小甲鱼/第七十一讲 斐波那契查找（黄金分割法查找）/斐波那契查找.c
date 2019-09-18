// ********************************
// By 小甲鱼，http://www.fishc.com
// ********************************

#include <stdio.h>

#define MAXSIZE 20

void fibonacci(int *f)
{
	int i;

	f[0] = 1;
	f[1] = 1;
	
	for(i=2; i < MAXSIZE; ++i)
	{
		f[i] = f[i-2] + f[i-1];

	}
}

int fibonacci_search(int *a,int key,int n)
{
	int low = 0;
	int high = n - 1;
	int mid = 0;
	int k = 0;
	int F[MAXSIZE];
	int i;

	fibonacci(F);
	
	while( n > F[k]-1 ) 
	{
		++k;
	}

	for( i=n; i < F[k]-1; ++i)
	{
		a[i] = a[high];
	}

	while( low <= high )
	{
		mid = low + F[k-1] - 1;

		if( a[mid] > key )
		{
			high = mid - 1;
			k = k - 1;
		}
		else if( a[mid] < key )
		{
			low = mid + 1;
			k = k - 2;
		}
		else
		{
			if( mid <= high ) 
			{
				return mid;
			}
			else
			{
				return high;
			}
		}
	}

	return -1;
}

int main()
{
	
	int a[MAXSIZE] = {1, 5, 15, 22, 25, 31, 39, 42, 47, 49, 59, 68, 88};
	int key;
	int pos;

	printf("请输入要查找的数字:");
	scanf("%d", &key);
	
	pos = fibonacci_search(a, key, 13);
	
	if( pos != -1 )
	{
		printf("\n查找成功，可喜可贺，可口可乐! 关键字 %d 所在的位置是: %d\n\n", key, pos);
	}
	else
	{
		printf("\nO~No~~小的办事不力，未在数组中找到元素:%d\n\n", key);
	}
		
	return 0;
}