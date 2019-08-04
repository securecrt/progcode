#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
    signle list
 */

typedef struct _single_list_t
{
    struct _single_list_t *next;
    int val;
} single_list_t;

typedef struct _single_list_head_t
{
    single_list_t *head;
} single_list_head_t;

bool single_list_is_empty(single_list_head_t *head)
{
    return (head->head == NULL);
}

void single_list_dump(single_list_head_t *head)
{
    single_list_t *tmp = head->head;
    int idx = 0;

    while (tmp)
    {
        printf("[%02d] %08X:%-8d \r\n", idx++, (int)tmp, tmp->val);
        tmp = tmp->next;
    }
}

void single_list_insert(single_list_t **prev, single_list_t *elem)
{
    if (prev == NULL)
        return;
    if (*prev)
        elem->next = *prev;
    *prev = elem;
}

void singel_list_insert_head(single_list_head_t *head, single_list_t *elem)
{
    single_list_insert(&head->head, elem);
}

single_list_t *single_list_delete(single_list_head_t *head, single_list_t **elem)
{
    single_list_t *tmp;
    single_list_t *prev;

    if (elem == NULL || head->head == NULL)
        return NULL;
    if (*elem == NULL)
        return NULL;
    tmp = head->head;
    if (tmp == *elem)
    {
        head->head = (*elem)->next;
        tmp->next = NULL;
        return tmp;
    }
    else
    {
        tmp = tmp->next;
    }

    prev = head->head;
    while (tmp != *elem)
    {
        prev = prev->next;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return NULL;

    //printf("the value to be deleted is %08x:%d \r\n", (int)tmp, tmp->val);
    prev->next = (*elem)->next;
    tmp->next = NULL;
    return tmp;
}

void single_list_reverse(single_list_head_t *head)
{
    single_list_head_t tmp;
    single_list_t *elem;
    tmp.head = NULL;
    while (!single_list_is_empty(head))
    {
        elem = single_list_delete(head, &head->head);
        singel_list_insert_head(&tmp, elem);
    }
    head->head = tmp.head;
}

single_list_t *single_list_middle(single_list_head_t *head)
{
    single_list_t *s1, *s2;
    single_list_t pseudo_head;
    pseudo_head.next = head->head;
    s1 = &pseudo_head;
    s2 = &pseudo_head;
    while (true)
    {
        if (!s2 || !s2->next)
            return s1;
        s1 = s1->next;
        s2 = s2->next->next;
    }
    return NULL;
}
int main(int argc, char *argv[])
{
    single_list_head_t head;
    single_list_t nodes[10];
    single_list_t *p;
    int i;
    for (i = 0; i < 10; i++)
    {
        nodes[i].val = i;
        nodes[i].next = NULL;
    }
    head.head = NULL;

    for (i = 9; i >= 0; i--)
        singel_list_insert_head(&head, &nodes[i]);

    printf("init the list:\r\n");
    single_list_dump(&head);

    p = head.head;
    single_list_delete(&head, &p);
    printf("after delete head:\r\n");
    single_list_dump(&head);
    p = head.head;
    p = p->next;
    p = p->next;
    single_list_delete(&head, &p);
    printf("after delete the 3 elem:\r\n");
    single_list_dump(&head);

    p = single_list_middle(&head);
    if (p != NULL)
        printf("middle is %d\r\n", p->val);
    else
    {
        printf("error!\r\n");
    }

    single_list_reverse(&head);
    printf("after reverse \r\n");
    single_list_dump(&head);

    return 0;
}