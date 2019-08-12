/*
  一、关于链式队列的约定(目的是在C语言中描述方便)
  1.定义：
  （1） 队列是一种先进先出的线性表；
  （2） 它只允许在表的一端进行入队，在另一端进行出队操作。在队列中，允许插入的一端
        叫队尾，允许删除的一端较队头，即入队只能从队尾入，出队只能从队头出；
  （3） 运算受限的非循环单链表，头尾结点都有，链表中的插入删除操作在这里只能在队头
        队尾进行。
  （4）  对头指针指向有效数据，并且可移动；队尾指针指向的结点不存有效数据，指针域指
        向空NULL，永不移动。
  
  2.创建链式队列时：需定义两个结构，一个用于描述结点（此结构跟链表结点对应的结构类
    似），一个用于描述式哪个队列（此结构包括队头和队尾指针）；与创建一个空链表类似。
    队头指针和队尾指针都指向不存放有效数据的头结点，此头结点的指针域指向NULL。
  3.入队，出队，遍历，判断是否为空（链式队列不存在满问题），清空队列等操作。
  
  4.在C语言中不能使用动态分配的一维数组来实现循环队列。如果用户程序中有循环队列，则必须
    为它设定一个最大队列长度，若用户无法预估所用队列最大长度，则宜采用链队列。
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct _linked_queue_node_t
{
    int data;
    struct _linked_queue_node_t *next;
} linked_queue_node_t;

typedef struct
{
    linked_queue_node_t *head;
    linked_queue_node_t *tail;
} linked_queue_t;

void linked_queue_create(linked_queue_t *q);
void linked_queue_in(linked_queue_t *q, int val);
int linked_queue_is_empty(linked_queue_t *q);
void linked_queue_out(linked_queue_t *q, int *pval);
void linked_queue_traverse(linked_queue_t *q, int *qlen);
int linked_queue_clear(linked_queue_t *q);

void linked_queue_create(linked_queue_t *q)
{
    q->head = (linked_queue_node_t *)malloc(sizeof(linked_queue_node_t));
    if (NULL == q->head)
    {
        printf("linked_queue_create(): malloc failed!\n");
        exit(-1);
    }
    q->tail = q->head;
    q->tail->next = NULL;
    return;
}

void linked_queue_in(linked_queue_t *q, int val)
{
    linked_queue_node_t *ptemp = (linked_queue_node_t *)malloc(sizeof(linked_queue_node_t));
    if (NULL == ptemp)
    {
        printf("linked_queue_in(): malloc failed!\n");
        exit(-1);
    }

    ptemp->data = val;
    q->tail->next = ptemp;
    ptemp->next = NULL;
    q->tail = ptemp;

    return;
}

int linked_queue_is_empty(linked_queue_t *q)
{
    if (q->head == q->tail)
        return 1;
    else
        return 0;
}

void linked_queue_out(linked_queue_t *q, int *pval)
{
    if (linked_queue_is_empty(q))
    {
        printf("linkedQueue is Empty!\n");
        return;
    }

    linked_queue_node_t *ptemp = q->head->next;
    *pval = ptemp->data;
    q->head->next = ptemp->next;
    free(ptemp);

    if (NULL == q->head->next)
    {
        q->head = q->tail;
    }

    return;
}

//遍历队列，并返回队列的长度
void linked_queue_traverse(linked_queue_t *q, int *qlen)
{
    int i = 0;
    linked_queue_node_t *ptemp = q->head->next;

    while (ptemp != NULL)
    {
        i++;
        printf("data-%d is %d\n", i, ptemp->data);
        ptemp = ptemp->next;
    }

    *qlen = i;

    return;
}

int linked_queue_clear(linked_queue_t *q)
{
    int pval = 0;

    while (!(linked_queue_is_empty(q)))
        linked_queue_out(q, &pval);

    return;
}
