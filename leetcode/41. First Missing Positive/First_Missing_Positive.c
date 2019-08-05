/*
Given an unsorted integer array, find the smallest missing positive integer.

Example 1:

Input: [1,2,0]
Output: 3
Example 2:

Input: [3,4,-1,1]
Output: 2
Example 3:

Input: [7,8,9,11,12]
Output: 1
Note:

Your algorithm should run in O(n) time and uses constant extra space.

 */
#include <stdio.h>

int firstMissingPositive(int *nums, int numsSize)
{
    int seed = 1;
    int i;

    for (i = 0; i < numsSize; i++)
    {
        /* 
        实际上不需要 判断正负号 ，可以减少程序执行时间
        if (nums[i] <= 0)
            continue;
        else
        {
            if (seed == nums[i])
                seed++;
        }
         */
        if (seed == nums[i])
            seed++;
    }
    return seed;
}

int main(int argc, char *argv[])
{
    int nums1[] = {1, 2, 0};
    int numsSize1 = 3;
    int nums2[] = {3, 4, -1, 1};
    int numsSize2 = 4;
    int nums3[] = {7, 8, 9, 11, 12};
    int numsSize3 = 5;
    int elem;

    elem = firstMissingPositive(nums1, numsSize1);
    printf("firstMissingPositive is %d\r\n", elem);
    elem = firstMissingPositive(nums2, numsSize2);
    printf("firstMissingPositive is %d\r\n", elem);
    elem = firstMissingPositive(nums3, numsSize3);
    printf("firstMissingPositive is %d\r\n", elem);

    return 0;
}