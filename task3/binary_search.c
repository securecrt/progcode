/*
实现一个有序数组的二分查找算法
 */
#include <stdio.h>
#include <math.h>

int binary_search(int *a, int l, int r, int val)
{
    int mid;
    int result = -1;
    mid = floor((l + r) / 2);

    if (a[mid] == val)
        return mid;
    else if (a[mid] > val)
    {
        if (l > mid - 1)
            return result;
        result = binary_search(a, l, mid - 1, val);
    }
    else
    {
        if (mid + 1 > r)
            return result;
        result = binary_search(a, mid + 1, r, val);
    }
    return result;
}

//another method 
int binary_search_i(int *arr, int size, int val)
{
	int low = 0, high = size - 1, mid;

	while (low <= high) {
		mid = (low + high) / 2;
		if (arr[mid] == val)
			return mid;

		if (arr[mid] < val)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}

int main(int argc, char *argv[])
{
    int array_nums[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17};
    int i;

    for (i = 0; i < 16; i++)
        printf("%d ", array_nums[i]);
    printf("\r\n");

    i = binary_search(array_nums, 0, 15, 4);
    printf("%d\r\n", i);

    i = binary_search(array_nums, 0, 15, -4);
    printf("%d\r\n", i);


}
