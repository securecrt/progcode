/*
实现朴素的字符串匹配算法
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int match(char *S, char *T)
{
    int i = 0;                   /* i用于主串S中当前位置下标值，若pos不为1，则从pos位置开始匹配 */
    int j = 0;                     /* j用于子串T中当前位置下标值 */
    int sl = strlen(S);
    int tl = strlen(T);
    while (i < sl && j < tl) /* 若i小于S的长度并且j小于T的长度时，循环继续 */
    {
        if (S[i] == T[j]) /* 两字母相等则继续 */
        {
            ++i;
            ++j;
        }
        else /* 指针后退重新开始匹配 */
        {
            i = i - j + 1; /* i退回到上次匹配首位的下一位 */
            j = 0;         /* j退回到子串T的首位 */
        }
    }
    if (j == tl)
        return i - tl ;
    else
        return -1;
}


/*
https://blog.csdn.net/v_july_v/article/details/7041827


 */

int main()
{

    char *s = "helloworld";
    char *t = "world";

    printf("%d",match(s,t));

}