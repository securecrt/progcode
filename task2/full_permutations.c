/* 编程实现一组数据集合的全排列 */

#include <stdio.h>
#include <stdbool.h>

void show_array(int *arr, int len)
{
    printf("{ ");
    for (int i = 0; i < len; ++i)
        printf("%d ", arr[i]);
    printf("}\n");
}

void swap(int *o, int i, int j)
{
    int tmp = o[i];
    o[i] = o[j];
    o[j] = tmp;
}

bool is_swap(int *arr, int len, int index)
{
    for (int i = index + 1; i < len; ++i)
        if (arr[index] == arr[i])
            return false;
    return true;
}

void permutation(int *arr, int len, int index, int *cnt)
{
    if (index == len)
    {
        *cnt = *cnt + 1;
        show_array(arr, len);
    }
    else
        for (int i = index; i < len; ++i)
        {

            if (is_swap(arr, len, i))   //去重
            {
                //将第i个元素交换至当前index下标处
                swap(arr, index, i);
                //以递归的方式对剩下元素进行全排列
                permutation(arr, len, index + 1, cnt);
                //将第i个元素交换回原处
                swap(arr, index, i);
            }
        }
}

int main()
{
    int array[3] = {1, 3, 3};
    int cnt = 0;
    permutation(array, 3, 0, &cnt);
    printf("num %d", cnt);

    return 0;
}
