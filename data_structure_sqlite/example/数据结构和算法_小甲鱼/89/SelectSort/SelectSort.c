#include <stdio.h>

void SelectSort(int k[], int n)
{
	int i, j, min, temp, count1=0, count2=0;

	for( i=0; i < n-1; i++ )
	{
		min = i;
		
		for( j=i+1; j < n; j++ )
		{
			count1++;
			if( k[j] < k[min] )
			{
				min = j;
			}
		}

		if( min != i )
		{
			count2++;
			temp = k[min];
			k[min] = k[i];
			k[i] = temp;
		}
	}

	printf("总共进行了%d次比较，进行了%d次移动！", count1, count2);
}

int main()
{
	int i, a[10] = {5, 2, 6, 0, 3, 9, 1, 7, 4, 8};

	SelectSort(a, 10);

	printf("排序后的结果是：");
	for( i=0; i < 10; i++ )
	{
		printf("%d", a[i]);
	}
	printf("\n\n");

	return 0;
}