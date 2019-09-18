#include <stdio.h>

void InsertSort(int k[], int n)
{
	int i, j, temp;
	int gap = n;

	do
	{
		gap = gap/3 + 1;

		for( i=gap; i < n; i++ )
		{
			if( k[i] < k[i-gap] )
			{
				temp = k[i];

				for( j=i-gap; k[j] > temp; j-=gap )
				{
					k[j+gap] = k[j];
				}

				k[j+gap] = temp;
			}
		}
	}while(gap > 1);
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