/*
    Stack is a linear data structure which follows a particular order in which the operations are performed. The order may be LIFO(Last In First Out) or FILO(First In Last Out).
Mainly the following three basic operations are performed in the stack:

Push: Adds an item in the stack. If the stack is full, then it is said to be an Overflow condition.
Pop: Removes an item from the stack. The items are popped in the reversed order in which they are pushed. If the stack is empty, then it is said to be an Underflow condition.
Peek or Top: Returns top element of stack.
isEmpty: Returns true if stack is empty, else false.

 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef unsigned int uint;
typedef struct
{

    int top;
    uint capacity;
    uint *array;

} array_stack_t;

bool is_empty(array_stack_t *stack)
{
    return (stack->top == -1) ? true : false;
}

bool pop(array_stack_t *stack, uint *item)
{
    if (stack == NULL)
        return false;

    if (stack->top == -1)
        return false;

    *item = stack->array[stack->top--];
    return true;
}

bool push(array_stack_t *stack, uint item)
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

bool peek(array_stack_t *stack, uint *item)
{
    if (stack == NULL)
        return false;
    if (stack->top == -1)
        return false;

    *item = stack->array[stack->top];
    return true;
}

array_stack_t *create_stack(uint capacity)
{

    array_stack_t *stack;
    stack = (array_stack_t *)malloc(sizeof(array_stack_t));
    if (stack == NULL)
        return NULL;

    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (uint *)malloc(stack->capacity * sizeof(uint));

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
int main(int argc, char *argv[])
{

    array_stack_t *mystack;
    int stack_size = 16;
    uint item;
    uint i;
    mystack = create_stack(stack_size);

    if (mystack == NULL)
    {
        printf("stack create failed!\r\n ");
        return 1;
    }

    for (i = 0; i < stack_size + 1; i++)
    {
        if (push(mystack, i) == false)
            printf("Stack is full ? \r\n");
        else
            printf("push %d to stack\r\n", i);
    }

    if (peek(mystack, &item))
        printf("peek stack : %d \r\n", item);
    else
        printf("peek stack failed \r\n");

    printf("stack is%s full\r\n", is_full(mystack) ? "" : " not");

    while (pop(mystack, &item))
        printf("pop from stack: %d\r\n", item);

    printf("stack is%s empty\r\n", is_empty(mystack) ? "" : " not");

    if (peek(mystack, &item))
        printf("peek stack : %d \r\n", item);
    else
        printf("peek stack failed \r\n");

    destory_stack(mystack);
    return 0;
}

