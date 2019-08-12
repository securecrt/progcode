/*
编程实现 O(n) 时间复杂度内找到一组数据的第 K 大元素 
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

int partition(int *a, int low, int high)
{
    int key,tmp;
    tmp = a[low];
    key = a[low]; // 找一个基准点
    while (low < high)
    {
        while (low < high && a[high] <= key)    /* 从大到小 */
            high--;
        	a[low] = a[high];
        while (low < high && a[low] > key)
            low++;
        	a[high] = a[low];
    }
    a[low] = tmp;
    return low;
}

/* 快速排序 */
void quick_sort(int *a, int low, int high)
{
    int pivot;
    if (low < high)
    {
        pivot = partition(a, low, high);
        quick_sort(a, low, pivot - 1);
        quick_sort(a, pivot + 1, high);
    }
}

int findk(int *a, int low, int high, int k)
{
    int temp;
    temp = partition(a, low, high);
    if (temp == k - 1)
    {
        return a[temp];
    }
    else if (temp > k - 1)
        findk( a, low, temp - 1,k);
    else
        findk(a, temp + 1, high,k);
}

int main(int argc, char *argv[])
{
    int array_nums[16] = {3, 4, 55, 21, 31, 344, 78, 11, 7, 900, 12, 2, 6, 8, 112, 90};
    int N = 16, K=7, i;
    printf("%d",K);
    printf(" --- %d \r\n", findk(array_nums, 0, N, K));
    quick_sort(array_nums, 0, 15);
    for (i = 0; i < N; i++)
    {
        printf("%d ", array_nums[i]);
    }
    printf("\r\n");
    return 0;
}
