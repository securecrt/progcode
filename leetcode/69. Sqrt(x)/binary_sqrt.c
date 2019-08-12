/*
69. Sqrt(x)
Easy

839

1464

Favorite

Share
Implement int sqrt(int x).

Compute and return the square root of x, where x is guaranteed to be a non-negative integer.

Since the return type is an integer, the decimal digits are truncated and only the integer part of the result is returned.

Example 1:

Input: 4
Output: 2
Example 2:

Input: 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since 
             the decimal part is truncated, 2 is returned.
 */

int mySqrt(int x)
{

    int start = 1, end = x, ans = 1, m;
    if (x == 0 || x == 1)
        return x;
    while (start <= end)
    {
        m = start + (end - start) / 2;
        if (m == x / m)
            return m;
        if (m < x / m)
        {
            start = m + 1;
            ans = m;
        }
        else
            end = m - 1;
    }
    return ans;
}
