/*
实现归并排序、快速排序、插入排序、冒泡排序、选择排序、堆排序
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
/* 归并排序 */

void merging(int *l, int l_size, int *r, int r_size)
{
    int i, j, k, *temp;
    i = j = k = 0;
    temp = (int *)malloc((l_size + r_size) * sizeof(int));
    while (i < l_size && j < l_size)
    {
        if (l[i] < r[j])
        {
            temp[k++] = l[i++];
        }
        else
        {
            temp[k++] = r[j++];
        }
    }
    while (i < l_size)
    {
        temp[k++] = l[i++];
    }
    while (j < r_size)
    {
        temp[k++] = r[j++];
    }

    for (i = 0; i < l_size + r_size; i++)
    {
        l[i] = temp[i];
    }
    free(temp);
}

void merge_sort(int *a, int n)
{
    int *l = a;
    int *r = a + n / 2;
    int l_size = n / 2;
    int r_size = n - l_size;

    if (n > 1)
    {
        merge_sort(l, l_size);
        merge_sort(r, r_size);
        merging(l, l_size, r, r_size);
    }
}
/* 简单选择排序 */
void select_sort(int *p, int len)
{
    int i, j;
    int min, tmp;
    for (i = 0; i < len; i++)
    {
        min = i;
        for (j = i + 1; j < len; j++)
        {
            if (p[min] > p[j])
            {
                min = j;
            }
        }
        if (i != min)
        {
            tmp = p[i];
            p[i] = p[min];
            p[min] = tmp;
        }
    }
}

/* 冒泡排序 */
void bubble_sort(int *p, int len)
{
    int i, j, tmp;
    for (i = 0; i < len; i++)
    {
        for (j = i + 1; j < len; j++)
        {
            if (p[i] > p[j])
            {
                tmp = p[i];
                p[i] = p[j];
                p[j] = tmp;
            }
        }
    }
}

/* 直接插入排序 */
void insert_sort(int *p, int len)
{
    int i, j, tmp;
    for (i = 1; i < len; i++)
    {
        if (p[i] < p[i - 1])
        {
            tmp = p[i];
            for (j = i - 1; j >= 0 && p[j] > tmp; j--)
            {
                p[j + 1] = p[j];
            }
            p[j + 1] = tmp;
        }
    }
}

int partition(int *a, int low, int high)
{
    int key,tmp;
    tmp = a[low];
    key = a[low]; // 找一个基准点
    while (low < high)
    {
        while (low < high && a[high] >= key)
            high--;
        	a[low] = a[high];
        while (low < high && a[low] <= key)
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

int main(int argc, char *argv[])
{
    int array_nums[16] = {3, 4, 55, 21, 31, 344, 78, 11, 7, 900, 12, 2, 6, 8, 112, 90};
    int array_nums1[16],i;

    memcpy(array_nums1, array_nums, 16 * sizeof(int));
    quick_sort(array_nums1, 0, 15);

    for (i = 0; i < 16; i++)
        printf("%d ", array_nums1[i]);
    printf("\r\n");

    memcpy(array_nums1, array_nums, 16 * sizeof(int));
    merge_sort(array_nums1, 16);

    for (i = 0; i < 16; i++)
        printf("%d ", array_nums1[i]);
    printf("\r\n");
}
