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

typedef struct 
{
    single_list_t *head;
} single_list_head_t;

bool single_list_is_empty(single_list_head_t *head)
{
    return (head->head == NULL);
}

//显示 list 的内容

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
// 在list中插入一个元素
void single_list_insert(single_list_t **prev, single_list_t *elem)
{
    if (prev == NULL)
        return;
    if (*prev)
        elem->next = *prev;
    *prev = elem;
}
// 从list 的头部插入元素
void singel_list_insert_head(single_list_head_t *head, single_list_t *elem)
{
    single_list_insert(&head->head, elem);
}
// 从list 中删除一个元素
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
//list 反转
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
//计算 list 的中间节点
single_list_t *single_list_middle(single_list_head_t *head)
{
    single_list_t *s1, *s2;

    s1 = head->head;
    s2 = head->head;
    while (true)
    {
        if (!s2 || !s2->next)
            return s1;
        s1 = s1->next;
        s2 = s2->next->next;
    }
    return NULL;
}
//判断list是否是 循环list
bool single_list_is_cyclic(single_list_head_t *head)
{
    single_list_t *s1, *s2;

    s1 = head->head;
    s2 = head->head;
    while (s1 && s2)
    {
        s1 = s1->next;
        s2 = s2->next ? s2->next->next : s2->next;

        if (s1 == s2)
            return true;
    }
    return false;
}

void exchange_node(single_list_t **a, single_list_t **b)
{
    if(*b == NULL) return;
    single_list_t* p = *b;
    *b = p->next;
    p->next = *a;
    *a = p;
}

//合并两个有序的list  list 都是按照 从小到大排列。
single_list_t *single_list_merge(single_list_t **a, single_list_t **b)
{
    single_list_t c;
    single_list_t *s1, *s2, *s3;
    s1 = *a;
    s2 = *b;
    s3 = &c;

    while (1)
    {
        if(!s1)
        {
            s3->next = s2;
            break;
        }
        else if(!s2)
        {
            s3->next = s1;
            break;
        }
        if(s1->val <=s2->val)
        {
            exchange_node(&(s3->next),&s1);
        }
        else
        {
            exchange_node(&(s3->next),&s2);
        }
        s3=s3->next;
        
    }

    return c.next;
}

int main(int argc, char *argv[])
{
    single_list_head_t head;
    single_list_t nodes[10];
    single_list_t *p;
    int i;

    //used for list merge test
    single_list_t nodes_a[10];
    single_list_t nodes_b[10];
    single_list_head_t a, b, c;

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

    printf("list is%s cyclic\r\n", single_list_is_cyclic(&head) ? "" : " not");
    nodes[2].next = &nodes[8];
    printf("list is%s cyclic\r\n", single_list_is_cyclic(&head) ? "" : " not");

    for (i = 0; i < 10; i++)
    {
        nodes_a[i].val = i;
        nodes_a[i].next = NULL;
        nodes_b[i].val = i + 5;
        nodes_b[i].next = NULL;
    }
    a.head = NULL;
    b.head = NULL;
    for (i = 9; i >= 0; i--)
    {
        singel_list_insert_head(&a, &nodes_a[i]);
        singel_list_insert_head(&b, &nodes_b[i]);
    }
    printf("list a:\r\n");
    single_list_dump(&a);
    printf("list b:\r\n");
    single_list_dump(&b);

    c.head = single_list_merge(&a.head, &b.head);
    printf("list after merge:\r\n");
    single_list_dump(&c);
    return 0;
}