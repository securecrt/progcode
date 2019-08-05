/*
Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.

Example 1:

Input: [3,2,3]
Output: 3
Example 2:

Input: [2,2,1,1,1,2,2]
Output: 2

基本的思想就是 使用一次循环。 依次的比较 两个数字是否相等， 利用一个计数器来记录 比较的结果， 如果相等就 +1 ， 如果不等 就 -1 。
由于 众数  的个数一定是大于 整个数组数量的一半 那么 这样操作之后 最终 count 计数器 >= 0

 */

#include <stdio.h>


int majorityElement(int* nums, int numsSize){
    int i;
    int cnt = 0;
    int val;
    for(i=0;i<numsSize;i++)
    {
        if(cnt == 0)
        {
            val  = nums[i];
            cnt++;
        }
        else if(val == nums[i])
            cnt++;
        else
            cnt--;
    }
    return val;
}

int main(int argc, char *argv[])
{
    int nums[] = {2,2,1,2,1,2,2,7,9,2,3};
    int numsSize = 11;

    int elem;

    elem = majorityElement(nums,numsSize);

    printf("majority Element is %d\r\n",elem);

    return 0;
}