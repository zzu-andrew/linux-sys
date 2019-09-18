#include <stdio.h>

void BubbleSort(int k[], int n)
{
	int i, j, temp, count1=0, count2=0;
	
	for( i=0; i < n-1; i++ )
	{
		for( j=n-1; j > i; j-- )
		{
			count1++;
			if( k[j-1] > k[j] )
			{
				count2++;
				temp = k[j-1];
				k[j-1] = k[j];
				k[j] = temp;
			}
		}
	}

	printf("总共进行了%d次比较，进行了%d次移动！", count1, count2);
}

int main()
{
	int i, a[10] = {5, 2, 6, 0, 3, 9, 1, 7, 4, 8};

	BubbleSort(a, 10);

	printf("排序后的结果是：");
	for( i=0; i < 10; i++ )
	{
		printf("%d", a[i]);
	}
	printf("\n\n");

	return 0;
}