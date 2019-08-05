/*


Given a linked list, determine if it has a cycle in it.

To represent a cycle in the given linked list, we use an integer pos which represents the position (0-indexed) in the linked list where tail connects to. If pos is -1, then there is no cycle in the linked list.

 

Example 1:

Input: head = [3,2,0,-4], pos = 1
Output: true
Explanation: There is a cycle in the linked list, where tail connects to the second node.

    3 ---> 2 ----> 0 -----> -4 -
           ^                    \
           |                    /
            -------------------
Example 2:

Input: head = [1,2], pos = 0
Output: true
Explanation: There is a cycle in the linked list, where tail connects to the first node.

    1 ---> 2 -
    ^         \
    |         /
    ----------

Example 3:

Input: head = [1], pos = -1
Output: false
Explanation: There is no cycle in the linked list.

    1

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

bool hasCycle(struct ListNode *head)
{
    struct ListNode *s1, *s2;

    s1 = head->next;
    s2 = head->next;
    while (s1 && s2)
    {
        s1 = s1->next;
        s2 = s2->next ? s2->next->next : s2->next;

        if (s1 == s2)
            return true;
    }
    return false;
}
int main(int argc, char *argv[])
{
    struct ListNode Nodes[8];
    struct ListNode head;
    int i;
    for (i = 0; i < 8; i++)
    {
        Nodes[i].val = i;
        Nodes[i].next = NULL;
    }

    head.next = &Nodes[0];

    for (i = 0; i < 7; i++)
        Nodes[i].next = &Nodes[i + 1];

    printf("list is%s cyclic\r\n", hasCycle(&head) ? "" : " not");
    Nodes[7].next = &Nodes[2];
    printf("list is%s cyclic\r\n", hasCycle(&head) ? "" : " not");

    return 0;
}