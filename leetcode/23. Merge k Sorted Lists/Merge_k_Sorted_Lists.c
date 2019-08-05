/*
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

Example:

Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6

 */

#include <stdbool.h>
#include <stdio.h>

/**
 * Definition for singly-linked list.
*/
struct ListNode
{
    int val;
    struct ListNode *next;
};

struct ListNode *single_list_merge(struct ListNode **a, struct ListNode **b)
{
    struct ListNode c;
    struct ListNode *s1, *s2, *s3, *tmp;
    s1 = *a;
    s2 = *b;
    c.next = NULL;
    s3 = &c;

    while (1)
    {
        if (!s1)
        {
            s3->next = s2;
            break;
        }
        else if (!s2)
        {
            s3->next = s1;
            break;
        }
        if (s1->val <= s2->val)
        {
            tmp = s1;
            s1 = s1->next;
            tmp->next = s3->next;
            s3->next = tmp;
        }
        else
        {
            tmp = s2;
            s2 = s2->next;
            tmp->next = s3->next;
            s3->next = tmp;
        }
        s3 = s3->next;
    }

    return c.next;
}

struct ListNode *mergeKLists(struct ListNode **lists, int listsSize)
{

    int i;
    struct ListNode *new = NULL;
    for (i = 0; i < listsSize; i++)
    {
        new = single_list_merge(&new, &lists[i]);
    }
    return new;
}

void single_list_dump(struct ListNode *head)
{
    struct ListNode *tmp = head->next;
    int idx = 0;

    while (tmp)
    {
        printf("[%02d] %08X:%-8d \r\n", idx++, (int)tmp, tmp->val);
        tmp = tmp->next;
    }
}

int main(int argc, char *argv[])
{
    struct ListNode Nodes[10];
    int i;
    struct ListNode head;

    struct ListNode *lists[3];

    for (i = 0; i < 10; i++)
    {
        Nodes[i].val = i;
        Nodes[i].next = NULL;
    }

    lists[0] = &Nodes[0];
    lists[1] = &Nodes[3];
    lists[2] = &Nodes[5];

    Nodes[2].val = 7;
    Nodes[0].next = &Nodes[1];
    Nodes[1].next = &Nodes[2];

    Nodes[3].next = &Nodes[4];

    Nodes[5].val = 3;

    Nodes[5].next = &Nodes[6];
    Nodes[6].next = &Nodes[7];
    Nodes[7].next = &Nodes[8];
    Nodes[8].next = &Nodes[9];

    for (i = 0; i < 3; i++)
    {
        printf("List %d : \r\n", i + 1);
        head.next = lists[i];
        single_list_dump(&head);
    }

    head.next = mergeKLists(lists, 3);
    printf("Merged result: \r\n");
    single_list_dump(&head);

    return 0;
}