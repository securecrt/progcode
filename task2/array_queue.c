/*
用数组实现一个顺序队列
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{

    int idx_w, idx_r;
    int qsize;
    int *q;
} queue_t;

bool is_full(queue_t *q)
{
    return ((q->idx_w + 1) % q->qsize) == q->idx_r;
}

bool is_empty(queue_t *q)
{
    return q->idx_w == q->idx_r;
}
bool enqueue(queue_t *q, int item)
{
    if (is_full(q))
        return false;

    q->q[q->idx_w] = item;
    q->idx_w = (q->idx_w + 1) % q->qsize;
    return true;
}
bool dequeue(queue_t *q, int *item)
{
    if (is_empty(q))
        return false;
    *item = q->q[q->idx_r];
    q->idx_r = (q->idx_r + 1) % q->qsize;
    return true;
}

queue_t *create_queue(int qsize)
{
    queue_t *q;
    q = (queue_t *)malloc(sizeof(queue_t));
    if (q == NULL)
        return NULL;
    q->q = (int *)malloc(sizeof(int) * qsize);
    if (q->q == NULL)
        return NULL;
    q->idx_w = 0;
    q->idx_r = 0;
    q->qsize = qsize;       //the max queue depenth is qsize - 1

    return q;
}
void destory_queue(queue_t *q)
{
    if (q != NULL)
    {
        if (q->q != NULL)
            free(q->q);
        free(q);
    }
}

int main(int argc, char *argv[])
{
    queue_t *q;
    int qsize = 8;
    int i = 0;
    q = create_queue(qsize);

    while (!is_full(q))
    {
         printf("%d \r\n", i);
        enqueue(q, i++);
    }

    while (!is_empty(q))
    {
        dequeue(q, &i);
        printf("%d \r\n", i);
    }

    while (!is_full(q))
    {
         printf("%d \r\n", i);
        enqueue(q, i++);
    }

    while (!is_empty(q))
    {
        dequeue(q, &i);
        printf("%d \r\n", i);
    }

    destory_queue(q);
    return 0;
}