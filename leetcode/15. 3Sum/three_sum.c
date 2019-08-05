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
double gaussrand( )
{
    static double U, V;
    static int phase = 0;
    double Z;

    if(phase == 0)
    {
         U = rand() / (RAND_MAX + 1.0);
         V = rand() / (RAND_MAX + 1.0);
         Z = sqrt(-2.0 * log(U))* sin(2.0 * PI * V);
    }
    else
    {
         Z = sqrt(-2.0 * log(U)) * cos(2.0 * PI * V);
    }

    phase = 1 - phase;
    return Z;
}

void quickSort(int *nums, int left, int right)
{
    int i, j, pivot, temp;
    if (left < right)
    {
        i = left;
        j = right + 1;
        pivot = nums[left];
        do
        {
            do
            {
                i++;
            } while (nums[i] < pivot);
            do
            {
                j--;
            } while (nums[j] > pivot);
            if (i < j)
            {
                temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        } while (i < j);
        temp = nums[left];
        nums[left] = nums[j];
        nums[j] = temp;

        quickSort(nums, left, j - 1);
        quickSort(nums, j + 1, right);
    }
}

void *re_alloc(void *p, int old_size, int new_size)
{
    if (p == NULL)
        return malloc(new_size);

    void *p_new;
    p_new = (void *)malloc(new_size);

    memcpy(p_new, p, old_size);
    free(p);
    return p_new;
}

int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    int i, j, k, sum;
    int **ret;
    i = 0;
    j = 0;
    k = 0;
    quickSort(nums, 0, numsSize - 1);
    if (numsSize < 3)
        return NULL;

    for (i = 0; i < numsSize - 2; i++)
    {
        j = i;
        k = numsSize - 1;
        if (nums[i] == nums[i + 1] && ((i + 1) < numsSize - 2))
            continue;
        while (j < k)
        {
            sum = nums[i] + nums[j] + nums[k];
            if (sum == 0)
            {
                returnColumnSizes = (int **)re_alloc(returnColumnSizes, (*returnSize) * sizeof(int *), (*returnSize + 1) * sizeof(int *));

                returnColumnSizes[*returnSize] = (int *)malloc(3 * sizeof(int));
                returnColumnSizes[*returnSize][0] = nums[i];
                returnColumnSizes[*returnSize][1] = nums[j];
                returnColumnSizes[*returnSize][2] = nums[k];
                *returnSize = *returnSize + 1;
                j++, k--;
                while (j < k && nums[j] == nums[j - 1])
                    j++;
                while (j < k && nums[k] == nums[k - 1])
                    k--;
            }
            else if (sum > 0)
                k--;
            else
                j++;
        }
    }
    ret = returnColumnSizes;
    return ret;
}

int main(int argc, char *argv[])
{
    //int nums[] = {-1, 0, 1, 2, -1, -4};
    //int numsSize = 6;

    int *nums;
    int numsSize = 10240;
    int **result;
    int returnSize = 0;
    int **returnColumnsizes;

    int i;

    //使用高斯随机函数 产生数据
    nums = malloc(numsSize * sizeof(int));
    for (i=0;i< numsSize;i++ )
        nums[i] = (int)(10*gaussrand());

    returnColumnsizes = NULL;
    result = threeSum(nums, numsSize, &returnSize, returnColumnsizes);
    if (result)
    {
        for (i = 0; i < returnSize; i++)
        {
            printf("%d,%d,%d \r\n", result[i][0], result[i][1], result[i][2]);
            free(result[i]);
        }

        free(result);
    }
    free(nums);

    return 0;
}