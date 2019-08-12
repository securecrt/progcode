/* 递归法求斐波那契数列 */

#include<stdio.h>
int fun(int n)      //n代表第几项。特别指出：0是第0项，不是第1项。
{
    if (n <= 1)
        return n;
    else
        return fun(n-1) + fun(n-2);
}
 
int main(int argc, char *argv[])
{
    int n = 16;
    int i;
    for (i = 0; i < n+1; i++)         //输出所有项
    {
        printf("%d, ", fun(i));
        if (i != 0 && i%5 == 0) 
            printf("\r\n");
    }
    printf("\r\n%d : %d\n", n, fun(n)); //输出要求的项
    return 0;
}

