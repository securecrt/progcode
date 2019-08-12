/*
实现模糊二分查找算法（比如大于等于给定值的第一个元素）

more info could be found at below link
https://blog.csdn.net/jyxmust/article/details/78237329

 */
#include <stdio.h>
int binary_search_i(int *arr, int size, int val)
{
	int low = 0, high = size - 1, mid;

	while (low <= high) {
		mid = (low + high) / 2;
		if (arr[mid] >= val)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return low;
}

int main(int argc, char *argv[])
{
    int array_nums[16] = {1, 2, 3, 6, 6, 6, 7, 7, 9, 11, 11, 13, 14, 15, 16, 17};
    int i;

    for (i = 0; i < 16; i++)
        printf("%d ", array_nums[i]);
    printf("\r\n");

    i = binary_search_i(array_nums, 15, 7);
    printf("%d\r\n", i);

}