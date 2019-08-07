/*
Return the largest possible k such that there exists a_1, a_2, ..., a_k such that:

Each a_i is a non-empty string;
Their concatenation a_1 + a_2 + ... + a_k is equal to text;
For all 1 <= i <= k,  a_i = a_{k+1 - i}.
 

Example 1:

Input: text = "ghiabcdefhelloadamhelloabcdefghi"
Output: 7
Explanation: We can split the string on "(ghi)(abcdef)(hello)(adam)(hello)(abcdef)(ghi)".
Example 2:

Input: text = "merchant"
Output: 1
Explanation: We can split the string on "(merchant)".
Example 3:

Input: text = "antaprezatepzapreanta"
Output: 11
Explanation: We can split the string on "(a)(nt)(a)(pre)(za)(tpe)(za)(pre)(a)(nt)(a)".
Example 4:

Input: text = "aaa"
Output: 3
Explanation: We can split the string on "(a)(a)(a)".

Constraints:

text consists only of lowercase English characters.
1 <= text.length <= 1000

 */

#include <stdio.h>
#include <string.h>

int _n_strcmp(char *a, char *b, int n)
{
    int i;
    int ret = 0;
    for (i = 0; i < n; i++)
    {
        if (a[i] != b[i])
        {
            ret = 1;
            break;
        }
    }
    return ret;
}

int longestDecomposition(char *text)
{

    int n, m, k, l;
    int len;

    len = strlen(text);

    if (len == 0)
        return 0;
    if (len == 1)
        return 1;

    n = 0;
    m = 0;
    k = 0;
    l = 0;
    while (1)
    {

        if (&text[n] > &text[len - n - m - 1])
            break;

        if (_n_strcmp(&text[n], &text[len - n - m - 1], m + 1) == 0)
        {
            k++;
            if (&text[len - n - m - 1] == &text[n])
            {
                l = 1;
                break;
            }

            n = n + m + 1;
            m = 0;
        }
        else
            m++;
    };
    return k * 2 - l;
}

int main(int argc, char *argv[])
{
    char *text = "ghiabcdefhelloadamhelloabcdefghi";
    char *text1 = "elvtoelvto";
    char *text2 = "aaa";
    printf("%d\r\n", longestDecomposition(text));
    printf("%d\r\n", longestDecomposition(text1));
    printf("%d\r\n", longestDecomposition(text2));
    return 0;
}
