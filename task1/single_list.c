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
    single_list_t *p_head;
} single_list_head_t;

bool single_list_is_empty(single_list_head_t *head)
{
    return (head->p_head == NULL);
}

void single_list_dump(single_list_head_t *head)
{
    single_list_t *p_temp = head->p_head;
    int idx = 0;

    while(p_temp)
    {
        printf("[%02d] %08d:%-8d",idx++,p_temp->node_val);
        p_temp= p_temp->p_next_node;
    }
}

void single_list_insert(single_list_t **prev, single_list_t* elem)
{
    if(prev == NULL)
        return;
    if(*prev == NULL)
        elem->p_next_node = *prev;
    *prev = elem;
}

void singel_list_insert_head(single_list_head_t *head,single_list_t* elem)
{
    single_list_insert(&head->p_head,elem);
}

int main(int argc, char *argv[])
{

    return 0;
}