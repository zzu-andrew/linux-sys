// ********************************
// By 小甲鱼，http://www.fishc.com
// ********************************
#include <stdio.h>

int bin_search( int str[], int n, int key )
{
    int low, high, mid;
    
    low = 0;
    high = n-1;

    while( low <= high )
    {
        mid = low + (key-a[low]/a[high]-a[low])*(high-low); // 插值查找的唯一不同点
        
        if( str[mid] == key )
        {
            return mid;              
        }
        if( str[mid] < key )
        {
            low = mid + 1;       
        }
        if( str[mid] > key )
        {
            high = mid - 1;       
        }
    }

    return -1;                      
}

int main()
{
    int str[11] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
    int n, addr;

    printf("请输入待查找的关键字: ");
    scanf("%d", &n);

    addr = bin_search(str, 11, n);
    if( -1 != addr )
    {
        printf("查找成功，可喜可贺，可口可乐! 关键字 %d 所在的位置是: %d\n", n, addr);
    }
    else
    {
        printf("查找失败!\n");
    }

    return 0;
}