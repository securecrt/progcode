/*

double link list implemtation

 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int node_data_t; // 数据类型

typedef struct _list_node_t
{
    struct _list_node_t *next;
    struct _list_node_t *prev;
    node_data_t data;
} list_node_t;

typedef struct _dlink_list_t
{

    list_node_t *head;
    list_node_t *tail;
    unsigned int size;

    //pointers;
    bool (*add_to_head)(struct _dlink_list_t *plist, node_data_t data);
    bool (*add_to_tail)(struct _dlink_list_t *plist, node_data_t data);
    bool (*del_first)(struct _dlink_list_t *plist);
    bool (*del_last)(struct _dlink_list_t *plist);
    bool (*show_all)(struct _dlink_list_t *plist);
} dlink_list_t;

void init(struct _dlink_list_t *plist);

bool _add_to_head(struct _dlink_list_t *plist, node_data_t data)
{
    list_node_t *pnew_node = (list_node_t *)malloc(sizeof(list_node_t));
    if (pnew_node == NULL)
        return false;
    pnew_node->data = data;
    pnew_node->next = NULL;
    pnew_node->prev = NULL;

    if (plist->head == NULL)
    {
        plist->head = pnew_node;
        plist->tail = pnew_node;
        plist->size++;
    }
    else
    {
        pnew_node->next = plist->head;
        plist->head->prev = pnew_node;
        plist->head = pnew_node;
        plist->size++;
    }
    return true;
}
bool _add_to_tail(struct _dlink_list_t *plist, node_data_t data)
{
    list_node_t *pnew_node = (list_node_t *)malloc(sizeof(list_node_t));
    if (pnew_node == NULL)
        return false;
    pnew_node->data = data;
    pnew_node->next = NULL;
    pnew_node->prev = NULL;

    if (plist->head == NULL)
    {
        plist->head = pnew_node;
        plist->tail = pnew_node;
        plist->size++;
    }
    else
    {
        pnew_node->prev = plist->tail;
        plist->tail->next = pnew_node;
        plist->tail = pnew_node;
        plist->size++;
    }
    return true;
}
bool _del_first(struct _dlink_list_t *plist)
{
    list_node_t *pnode;
    if (plist->head == NULL)
        return false;
    else
    {
        pnode = plist->head;
        if (plist->size == 1)
        {
            plist->head = NULL;
            plist->tail = NULL;
        }
        else
        {
            plist->head = pnode->next;
            plist->head->prev = NULL;
        }
        plist->size--;
        free(pnode);
    }
    return true;
}
bool _del_last(struct _dlink_list_t *plist)
{
    list_node_t *pnode;
    if (plist->head == NULL)
        return false;
    else
    {
        pnode = plist->tail;
        if (plist->size == 1)
        {
            plist->head = NULL;
            plist->tail = NULL;
        }
        else
        {
            plist->tail = pnode->prev;
            plist->tail->next = NULL;
        }
        plist->size--;
        free(pnode);
    }
}
bool _show_all(struct _dlink_list_t *plist)
{

    list_node_t *pnode;
    int i = 0;
    if (plist->size == 0)
        return false;
    pnode = plist->head;

    while (pnode)
    {
        printf("%2d: [%08x] %-8d \r\n", i++, pnode, pnode->data);
        pnode = pnode->next;
    }
}

dlink_list_t *_create_list(void);
void _distory_list(dlink_list_t *plist);

dlink_list_t *create_list(void)
{
    dlink_list_t *plist = (dlink_list_t *)malloc(sizeof(dlink_list_t));
    plist->head = NULL;
    plist->tail = NULL;
    plist->size = 0;

    plist->add_to_head = _add_to_head;
    plist->add_to_tail = _add_to_tail;
    plist->del_first = _del_first;
    plist->del_last = _del_last;
    plist->show_all = _show_all;
}

void distory_list(dlink_list_t *plist)
{
    while (plist->head)
        plist->del_last(plist);

    free(plist);
}

int main(int argc, char *argv[])
{
    dlink_list_t *plist;

    plist = create_list();

    plist->add_to_head(plist, 1);
    plist->add_to_head(plist, 2);

    plist->del_last(plist);

    plist->add_to_tail(plist, 9);
    plist->add_to_tail(plist, 8);
    plist->add_to_tail(plist, 7);
    plist->add_to_tail(plist, 7);
    plist->add_to_tail(plist, 4);
    plist->add_to_tail(plist, 2);

    plist->del_first(plist);

    plist->show_all(plist);

    distory_list(plist);

    return 0;
}