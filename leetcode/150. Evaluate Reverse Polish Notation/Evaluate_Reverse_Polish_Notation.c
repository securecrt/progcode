/*
150. Evaluate Reverse Polish Notation
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct _list_node_t
{
    int val;
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

bool pop(link_list_stack_t *stack, int *item)
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

bool push(link_list_stack_t *stack, int item)
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

bool peek(link_list_stack_t *stack, int *item)
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

link_list_stack_t *create_stack(void)
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
    if (stack == NULL)
        return;

    while (stack->next != NULL)
    {
        pnode = stack->next;
        stack->next = pnode->next;
        free(pnode);
    }
    free(stack);
}

/*

This the best solution:

int evalRPN(char ** tokens, int tokensSize){
    int ret=0,idx=-1;
    int *stack=malloc(sizeof(int)*tokensSize);
    for(int i=0;i<tokensSize;i++)
    {
        if(!strcmp(tokens[i],"+"))
        {
            stack[idx-1]=stack[idx-1]+stack[idx];
            idx-=1;
        }
        else if(!strcmp(tokens[i],"-"))
        {
            stack[idx-1]=stack[idx-1]-stack[idx];
            idx-=1;
        }
        else if(!strcmp(tokens[i],"*"))
        {
            stack[idx-1]=stack[idx-1]*stack[idx];
            idx-=1;
        }
        else if(!strcmp(tokens[i],"/"))
         {
            stack[idx-1]=stack[idx-1]/stack[idx];
            idx-=1;
        }
        else {
            stack[++idx]=atoi(tokens[i]);
        }
    }
    return stack[0];
}
 */

int evalRPN(char **tokens, int tokensSize)
{

    link_list_stack_t *pstack;
    int i;
    int a, b, c;

    if (tokensSize == 1)
        return atoi(tokens[0]);

    pstack = create_stack();

    for (i = 0; i < tokensSize; i++)
    {
        if (tokens[i][0] == '+' || (tokens[i][0] == '-' && (strlen(tokens[i]) == 1)) || tokens[i][0] == '*' || tokens[i][0] == '/')
        {
            pop(pstack, &b);
            pop(pstack, &a);
            switch (tokens[i][0])
            {
            case '+':
                c = a + b;
                break;
            case '-':
                c = a - b;
                break;
            case '/':
                c = a / b;

                break;
            case '*':
                c = a * b;
                break;
            default:
                break;
            }
            push(pstack, c);
        }
        else
            push(pstack, atoi(tokens[i]));
    }

    destory_stack(pstack);
    return c;
}

int main(int argc, char *argv[])
{
    char *str[5] = {"-33", "196", "+", "-19", "-"};
    printf("%d", evalRPN(str, 5));

    return 0;
}
