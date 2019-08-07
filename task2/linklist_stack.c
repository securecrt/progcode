
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef unsigned int uint;

typedef struct _list_node_t
{
    uint val;
    struct _list_node_t *next;
} list_node_t;

typedef struct
{

    list_node_t *next;
} link_list_stack_t;

bool is_empty(link_list_stack_t *stack)
{
    return (stack->next == NULL) ? true : false;
}

bool pop(link_list_stack_t *stack, uint *item)
{

    list_node_t *pnode;

    if (stack == NULL)
        return false;

    if (stack->next == NULL)
        return NULL;

    pnode = stack->next;

    stack->next = pnode->next;
    *item = pnode->val;

    free(pnode);

    return true;
}

bool push(link_list_stack_t *stack, uint item)
{
    list_node_t *pnode;

    if (stack == NULL)
        return false;

    pnode = (list_node_t *)malloc(sizeof(list_node_t));
    if (pnode == NULL)
        return false;

    pnode->next = stack->next;
    stack->next = pnode;
    pnode->val = item;

    return true;
}

bool is_full(link_list_stack_t *stack)
{
    return false;
}

bool peek(link_list_stack_t *stack, uint *item)
{
    list_node_t *pnode;
    if (stack == NULL)
        return false;
    if (stack->next == NULL)
        return false;

    pnode = stack->next;
    *item = pnode->val;
    return true;
}

link_list_stack_t *create_stack( void )
{

    link_list_stack_t *stack;
    stack = (link_list_stack_t *)malloc(sizeof(link_list_stack_t));
    if (stack == NULL)
        return NULL;
    stack->next = NULL;
    return stack;
}
void destory_stack(link_list_stack_t *stack)
{
    list_node_t *pnode;
    if(stack == NULL)
        return ;

    while(stack->next != NULL)
    {
        pnode = stack->next;
        stack->next = pnode->next;
        free(pnode);
    }
    free(stack);
}
int main(int argc, char *argv[])
{

    link_list_stack_t *mystack;
    int stack_size = 16;
    uint item;
    int i;
    mystack = create_stack();

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