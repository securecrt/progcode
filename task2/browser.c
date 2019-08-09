/*
编程模拟实现一个浏览器的前进、后退功能



*/
#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct _list_node_t
{
    char *val;
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

bool pop(link_list_stack_t *stack, char *item)
{

    list_node_t *pnode;

    if (stack == NULL)
        return false;
    if (stack->next == NULL)
        return false;

    pnode = stack->next;
    stack->next = pnode->next;
    memcpy(item, pnode->val, strlen(pnode->val) * sizeof(char));
    free(pnode->val);
    free(pnode);

    return true;
}

void clear(link_list_stack_t *stack)
{
    list_node_t *pnode;
    pnode = stack->next;
    while (pnode != NULL)
    {
        stack->next = pnode->next;
        free(pnode);
        pnode = stack->next;
    }
    return;
}

bool push(link_list_stack_t *stack, char *item)
{
    list_node_t *pnode;

    if (stack == NULL)
        return false;
    pnode = (list_node_t *)malloc(sizeof(list_node_t));
    if (pnode == NULL)
        return false;

    pnode->next = stack->next;
    stack->next = pnode;
    pnode->val = (char *)malloc(sizeof(char *) * strlen(item));
    memcpy(pnode->val, item, sizeof(char *) * strlen(item));

    return true;
}

bool is_full(link_list_stack_t *stack)
{
    return false;
}

bool peek(link_list_stack_t *stack, char *item)
{
    list_node_t *pnode;
    if (stack == NULL)
        return false;
    if (stack->next == NULL)
        return false;

    pnode = stack->next;
    memcpy(item, pnode->val, strlen(pnode->val) * sizeof(char));
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

typedef struct
{

    link_list_stack_t *back_stack;
    link_list_stack_t *fwd_stack;
    char cur_url[256];

} simple_browser_t;

simple_browser_t *create_browser(void)
{

    simple_browser_t *pbrowser;

    pbrowser = (simple_browser_t *)malloc(sizeof(simple_browser_t));
    if (pbrowser == NULL)
        return NULL;

    pbrowser->back_stack = create_stack();
    if (pbrowser->back_stack == NULL)
    {
        free(pbrowser);
        return NULL;
    }
    pbrowser->fwd_stack = create_stack();
    if (pbrowser->fwd_stack == NULL)
    {
        free(pbrowser->back_stack);
        free(pbrowser);
        return NULL;
    }
    pbrowser->cur_url[0] = '\0';
    return pbrowser;
}

void destroy_browser(simple_browser_t *pbrowser)
{
    if (pbrowser != NULL)
    {
        destory_stack(pbrowser->fwd_stack);
        destory_stack(pbrowser->back_stack);
        free(pbrowser);
    }
}
void show_url(char *purl)
{
    if (purl != NULL)
        printf("%s\r\n", purl);
}
bool open_url(simple_browser_t *pbrowser, char *url)
{
    if (pbrowser->cur_url[0] != '\0')
    {
        push(pbrowser->back_stack, pbrowser->cur_url);
        clear(pbrowser->fwd_stack);
    }
    strcpy(pbrowser->cur_url, url);

    show_url(pbrowser->cur_url);

    return true;
}

bool go_back(simple_browser_t *pbrowser)
{
    if (is_empty(pbrowser->back_stack) != true)
    {
        if (pbrowser->cur_url[0] != '\0')
            push(pbrowser->fwd_stack, pbrowser->cur_url);
        pop(pbrowser->back_stack, pbrowser->cur_url);

        show_url(pbrowser->cur_url);

        return true;
    }
    else
        return false;
}

bool go_fwd(simple_browser_t *pbrowser)
{
    if (is_empty(pbrowser->fwd_stack) != true)
    {
        if (pbrowser->cur_url[0] != '\0')
            push(pbrowser->back_stack, pbrowser->cur_url);
        pop(pbrowser->fwd_stack, pbrowser->cur_url);

        show_url(pbrowser->cur_url);

        return true;
    }
    else
        return false;
}

int main(int argc, char *argv[])
{
    simple_browser_t *pbrowser;

    pbrowser = create_browser();
    if (pbrowser == NULL)
        return 1;

    open_url(pbrowser, "www.baidu.com");
    open_url(pbrowser, "www.google.com");
    open_url(pbrowser, "www.bing.com");
    go_back(pbrowser);
    go_back(pbrowser);
    go_fwd(pbrowser);
    open_url(pbrowser, "www.sina.com");
    go_fwd(pbrowser);
    go_back(pbrowser);
    go_fwd(pbrowser);
    destroy_browser(pbrowser);
    return 0;
}

