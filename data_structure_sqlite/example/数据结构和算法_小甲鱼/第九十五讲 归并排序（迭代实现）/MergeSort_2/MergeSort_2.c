#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10

void MergeSort(int k[], int n)
{
	int i, next, left_min, left_max, right_min, right_max;
	int *temp = (int *)malloc(n * sizeof(int));

	for( i=1; i < n; i*=2 ) 
	{
		for( left_min=0; left_min < n-i; left_min = right_max )
		{
			right_min = left_max = left_min + i;
			right_max = left_max + i;

			if( right_max > n )
			{
				right_max = n;
			}

			next = 0;

			while( left_min < left_max && right_min < right_max )
			{
				if( k[left_min] < k[right_min] )
				{
					temp[next++] = k[left_min++];
				}
				else
				{
					temp[next++] = k[right_min++];
				}
			}

			while( left_min < left_max )
			{
				k[--right_min] = k[--left_max];
			}

			while( next > 0 )
			{
				k[--right_min] = temp[--next];
			}
		}
	}
}

int main()
{
	int i, a[10] = {5, 2, 6, 0, 3, 9, 1, 7, 4, 8};

	MergeSort(a, 10);

	printf("排序后的结果是：");
	for( i=0; i < 10; i++ )
	{
		printf("%d", a[i]);
	}
	printf("\n\n");

	return 0;
}