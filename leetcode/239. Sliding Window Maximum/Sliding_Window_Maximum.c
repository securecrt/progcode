/*
Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position. Return the max sliding window.

Example:

Input: nums = [1,3,-1,-3,5,3,6,7], and k = 3
Output: [3,3,5,5,6,7] 
Explanation: 

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Note: 
You may assume k is always valid, 1 ≤ k ≤ input array's size for non-empty array.

 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *maxSlidingWindow(int *nums, int numsSize, int k, int *returnSize)
{

    int *retarr, i, j, t;
    
    if(numsSize == 0)
    {
        *returnSize = 0;
        return nums;
    }
    *returnSize = numsSize - k + 1;
    retarr = (int *)malloc((*returnSize) * sizeof(int));

    for (i = 0; i < *returnSize; i++)
    {
        t = nums[i];
        for (j = i; j < k + i; j++)
        {
            if (nums[j] > t)
                t = nums[j];
        }
        retarr[i] = t;
    }
    return retarr;
}