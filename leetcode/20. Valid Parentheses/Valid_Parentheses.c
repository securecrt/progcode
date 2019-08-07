/*
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Note that an empty string is also considered valid.

Example 1:

Input: "()"
Output: true
Example 2:

Input: "()[]{}"
Output: true
Example 3:

Input: "(]"
Output: false
Example 4:

Input: "([)]"
Output: false
Example 5:

Input: "{[]}"
Output: true
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef char _VAL_T;
typedef struct
{

    int top;
    int capacity;
    _VAL_T *array;

} array_stack_t;

bool is_empty(array_stack_t *stack)
{
    return (stack->top == -1) ? true : false;
}

bool pop(array_stack_t *stack, _VAL_T *item)
{
    if (stack == NULL)
        return false;

    if (stack->top == -1)
        return false;

    *item = stack->array[stack->top--];
    return true;
}

bool push(array_stack_t *stack, _VAL_T item)
{
    if (stack == NULL)
        return false;
    if (stack->top == stack->capacity - 1)
        return false;
    stack->array[++stack->top] = item;
    return true;
}

bool is_full(array_stack_t *stack)
{
    return (stack->top == stack->capacity - 1) ? true : false;
}

bool peek(array_stack_t *stack, _VAL_T *item)
{
    if (stack == NULL)
        return false;
    if (stack->top == -1)
        return false;

    *item = stack->array[stack->top];
    return true;
}

array_stack_t *create_stack(int capacity)
{

    array_stack_t *stack;
    stack = (array_stack_t *)malloc(sizeof(array_stack_t));
    if (stack == NULL)
        return NULL;

    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (_VAL_T *)malloc(stack->capacity * sizeof(_VAL_T));

    if (stack->array == NULL)
    {
        free(stack);
        stack = NULL;
    }
    return stack;
}
void destory_stack(array_stack_t *stack)
{
    if (stack)
    {
        if (stack->array)
            free(stack->array);
        free(stack);
    }
}

bool is_pair(_VAL_T a, _VAL_T b)
{
    int i, j;
    bool ret = false;
    _VAL_T brackets[3][2] = {{'(', ')'}, {'[', ']'}, {'{', '}'}};

    for (i = 0; i < 3; i++)
        if (a == brackets[i][0] && b == brackets[i][1])
        {
            ret = true;
            break;
        }

    return ret;
}

bool isValid(char *s)
{

    int len, i;
    bool ret;
    array_stack_t *stack;
    _VAL_T ch;
    len = strlen(s);

    if (len == 0)
        return true;
    if (len % 2)
        return false;

    stack = create_stack(len);
    for (i = 0; i < len; i++)
    {
        if (is_empty(stack))
            push(stack, s[i]);
        else
        {
            peek(stack, &ch);
            if (is_pair(ch, s[i]))
            {
                pop(stack, &ch);
            }
            else
            {
                push(stack, s[i]);
            }
        }
    }
    ret = is_empty(stack);
    destory_stack(stack);
    return ret;
}

int main(int argc, char *argv[])
{
    char *pstr = "(){[[()]]}{}{{}}";

    if (isValid(pstr))
    {
        printf("true");
    }
    else
    {
        printf("false");
    }

    return 0;
}