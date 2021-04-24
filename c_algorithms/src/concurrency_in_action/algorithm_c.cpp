//
// Created by andrew on 2021/4/17.
//
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int inf = 1e9;
        int minprice = inf, maxprofit = 0;
        for (int price: prices) {
            maxprofit = max(maxprofit, price - minprice);
            minprice = min(price, minprice);
        }
        return maxprofit;
    }
};

// 插入排序
void InsertionSort(int *arr, int size)    
{    
    int i, j, tmp;    
    for (i = 1; i < size; i++) {    
        if (arr[i] < arr[i-1]) {    
            tmp = arr[i];    
            for (j = i - 1; j >= 0 && arr[j] > tmp; j--) {  
                arr[j+1] = arr[j];    
            }  
            arr[j+1] = tmp;    
        }          
    }    
}


// 快速排序
void QuickSort(int *arr, int maxlen, int begin, int end)  
{  
    int i, j;  
    if (begin < end) {  
        i = begin + 1;  
        j = end;        
        while (i < j) {  
            if(arr[i] > arr[begin]) {  
                swap(&arr[i], &arr[j]); 
                j--;  
            } else {  
                i++; 
            }  
        }  
        if (arr[i] >= arr[begin]) {  
            i--;  
        }  
        swap(&arr[begin], &arr[i]);      
        QuickSort(arr, maxlen, begin, i);  
        QuickSort(arr, maxlen, j, end);  
    }  
}  
 
void swap(int *a, int *b)    
{  
    int temp;  
    temp = *a;  
    *a = *b;  
    *b = temp;  
}  