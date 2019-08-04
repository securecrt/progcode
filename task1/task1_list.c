#include <stdlib.h>
#include <stdbool.h>
/*
实现单链表、循环链表、双向链表，支持增删操作
list 
 */


/*
    signle list
 */
typedef struct _single_list_t{
    struct _single_list_t *p_next_node;
    int node_val;
} single_list_t;

typedef struct _single_list_head_t{
    struct _single_list_head_t *p_head;
} single_list_head_t;

bool single_list_is_empty(single_list_head_t *head)
{
    return (head->p_head == NULL);
}

