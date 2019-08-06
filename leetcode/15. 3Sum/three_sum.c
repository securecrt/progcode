/*

Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:

The solution set must not contain duplicate triplets.

Example:

Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]

        X0 X1 X2 X3 X4 X5 X6 X7 X8 X9 ....   Xn
        |   ^                                ^
        i ---->                              |
            |                                |
            j ---->                    <---- k

        i is the first level loop  from x0 -> xn 
        j is the second level  from i+1 --> xn 
        k is the second level from xn --> i+1  
        the second level loop and stop when j == k
 */

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/*
https://www.cnblogs.com/tsingke/p/6194737.html
C语言 产生标准高斯分布 随机数
 */
#define PI 3.141592654
double gaussrand()
{
    static double U, V;
    static int phase = 0;
    double Z;

    if (phase == 0)
    {
        U = rand() / (RAND_MAX + 1.0);
        V = rand() / (RAND_MAX + 1.0);
        Z = sqrt(-2.0 * log(U)) * sin(2.0 * PI * V);
    }
    else
    {
        Z = sqrt(-2.0 * log(U)) * cos(2.0 * PI * V);
    }

    phase = 1 - phase;
    return Z;
}

void swap(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;

    return;
}
void quicksort(int *array, int maxlen, int begin, int end)
{
    int i, j;

    if (begin < end)
    {
        i = begin + 1; // 将array[begin]作为基准数，因此从array[begin+1]开始与基准数比较！
        j = end;       // array[end]是数组的最后一位

        while (i < j)
        {
            if (array[i] > array[begin]) // 如果比较的数组元素大于基准数，则交换位置。
            {
                swap(&array[i], &array[j]); // 交换两个数
                j--;
            }
            else
            {
                i++; // 将数组向后移一位，继续与基准数比较。
            }
        }

        /* 跳出while循环后，i = j。
         * 此时数组被分割成两个部分  -->  array[begin+1] ~ array[i-1] < array[begin]
         *                           -->  array[i+1] ~ array[end] > array[begin]
         * 这个时候将数组array分成两个部分，再将array[i]与array[begin]进行比较，决定array[i]的位置。
         * 最后将array[i]与array[begin]交换，进行两个分割部分的排序！以此类推，直到最后i = j不满足条件就退出！
         */

        if (array[i] >= array[begin]) // 这里必须要取等“>=”，否则数组元素由相同的值时，会出现错误！
        {
            i--;
        }

        swap(&array[begin], &array[i]); // 交换array[i]与array[begin]

        quicksort(array, maxlen, begin, i);
        quicksort(array, maxlen, j, end);
    }
}

void bubblesort(int *array, int len)
{
    int i, j, tmp;
    for (i = 0; i < len; i++)
        for (j = i; j < len; j++)
            if (array[j] < array[i])
            {
                tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
}
int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    int i, j, k, sum;
    int **ret;
    int pre_alloc_size = 2;
    *returnSize = 0;
    ret = NULL;
    *returnColumnSizes = NULL;
    ret = (int **)malloc(pre_alloc_size * sizeof(int **));

    i = 0;
    j = 0;
    k = 0;
    quicksort(nums, numsSize, 0, numsSize - 1);
    if (numsSize < 3)
        return NULL;

    for (i = 0; i < numsSize - 2; i++)
    {

        if (nums[i] > 0)
            break;
        if (i >= 1 && nums[i] == nums[i - 1])
            continue;
        j = i + 1;
        k = numsSize - 1;
        while (j < k)
        {
            sum = nums[i] + nums[j] + nums[k];
            if (sum == 0)
            {
                ret[*returnSize] = (int *)malloc(3 * sizeof(int));
                ret[*returnSize][0] = nums[i];
                ret[*returnSize][1] = nums[j];
                ret[*returnSize][2] = nums[k];
                *returnSize = *returnSize + 1;

                while (j < k && nums[j] == nums[j + 1])
                    j++;
                while (j < k && nums[k] == nums[k - 1])
                    k--;
                j++, k--;
            }
            else if (sum > 0)
                k--;
            else
                j++;
            if ((*returnSize) == pre_alloc_size)
            {
                pre_alloc_size = pre_alloc_size * 2;
                ret = (int **)realloc(ret, pre_alloc_size * sizeof(int **));
            }
        }
    }
    *returnColumnSizes = (int *)malloc((*returnSize) * sizeof(int));
    for (i = 0; i < (*returnSize); i++)
        (*returnColumnSizes)[i] = 3;
    return ret;
}

#define USE_RAND_NUM 1

int main(int argc, char *argv[])
{

    int **result;
    int returnSize = 0;
    int *returnColumnsizes;
    int i;

#if !USE_RAND_NUM
    int nums[] = {-1, 0, 1, 2, -1, -4};
    int numsSize = 6;
    //int nums[] = {0,0,0,0};
    //int numsSize = 4;
#else
    int *nums;
    int numsSize = 10240;
    //使用高斯随机函数 产生数据
    nums = malloc(numsSize * sizeof(int));
    for (i = 0; i < numsSize; i++)
        nums[i] = (int)(10 * gaussrand());
#endif
    returnColumnsizes = NULL;
    result = threeSum(nums, numsSize, &returnSize, &returnColumnsizes);
    if (result)
    {
        for (i = 0; i < returnSize; i++)
        {
            printf("%d,%d,%d \r\n", result[i][0], result[i][1], result[i][2]);
            free(result[i]);
        }
        printf("total %d results", returnSize);
        free(result);
    }
#if USE_RAND_NUM
    free(nums);
#endif
    return 0;
}