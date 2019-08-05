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
    int i, k, seed = 1;

    //对数据做一次伪排序
    for (i = 0; i < numsSize; i++)
    {
        if (nums[i] <= 0 || nums[i] > numsSize)
            continue;
        while (nums[i] != i + 1 && nums[i] != nums[nums[i] - 1])
        {
            if (nums[i] <= 0 ||  nums[i] > numsSize)
                break;
            k = nums[i];
            nums[i] = nums[k - 1];
            nums[k - 1] = k;
        }
    }
    for (i = 0; i < numsSize; i++)
    {
        //printf("i = %d, num = %d \r\n", i, nums[i]);
        if (seed == nums[i])
            seed++;
    }
    return seed;
}

int main(int argc, char *argv[])
{
    int nums1[] = {1, 2, 0};
    int numsSize1 = 3;
    int nums2[] = {3, 4, -1, 1,4,9,6,2};
    int numsSize2 = 8;
    int nums3[] = {7, 8, 9, 11, 12};
    int numsSize3 = 5;

    int nums4[] = {1, 3, 2, 4, 5};
    int numsSize4 = 5;

    int elem;

    elem = firstMissingPositive(nums1, numsSize1);
    printf("firstMissingPositive is %d\r\n", elem);
    elem = firstMissingPositive(nums2, numsSize2);
    printf("firstMissingPositive is %d\r\n", elem);
    elem = firstMissingPositive(nums3, numsSize3);
    printf("firstMissingPositive is %d\r\n", elem);
    elem = firstMissingPositive(nums4, numsSize4);
    printf("firstMissingPositive is %d\r\n", elem);
    return 0;
}