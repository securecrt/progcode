/*
Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.

Example 1:

Input: "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()"
Example 2:

Input: ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()"

 */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

int max(int x, int y)
{
    return (x > y ? x : y);
}
int longestValidParentheses1(char *s)
{
    int res = 0, stack[10000], top = -1;
    int i = 0;
    top++;
    stack[top] = -1;
    while (s[i] != '\0')
    {
        if (s[i] == '(')
        {
            top++;
            stack[top] = i;
        }
        else
        {
            if (top != -1)
            {
                top--;
            }
            if (top != -1)
            {
                res = max(res, i - stack[top]);
            }
            else
            {
                top++;
                stack[top] = i;
            }
        }
        i++;
    }
    return res;
}

int longestValidParentheses(char *s)
{
    int maxlen = 0, size, left = 0, right = 0;
    size = strlen(s);
    for (int i = 0; i < size; ++i)
    {
        if (s[i] == '(')
            ++left;
        else
            ++right;
        if (left == right)
            maxlen = max(maxlen, 2 * left);
        else if (right > left)
            left = right = 0;
    }

    left = right = 0;

    for (int i = size - 1; i >= 0; --i)
    {
        if (s[i] == '(')
            ++left;
        else
            ++right;
        if (left == right)
            maxlen = max(maxlen, 2 * left);
        else if (left > right)
            left = right = 0;
    }

    return maxlen;
}

int main(int argc, char *argv[])
{
    char *pstr = ")()())((((((((((((((((((((((((((()))))))))))))))((()))))))))))";

    printf("%d", longestValidParentheses1(pstr));

    return 0;
}
