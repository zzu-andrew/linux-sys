#include <stdio.h>

void InsertSort(int k[], int n)
{
	int i, j, temp;

	for( i=1; i < n; i++ )
	{
		if( k[i] < k[i-1] )
		{
			temp = k[i];

			for( j=i-1; k[j] > temp; j-- )
			{
				k[j+1] = k[j];
			}

			k[j+1] = temp;
		}
	}
}

int main()
{
	int i, a[10] = {5, 2, 6, 0, 3, 9, 1, 7, 4, 8};

	InsertSort(a, 10);

	printf("排序后的结果是：");
	for( i=0; i < 10; i++ )
	{
		printf("%d", a[i]);
	}
	printf("\n\n");

	return 0;
}