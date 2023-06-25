#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head)
{
    /* your code here */
    node *tortoise = head;
    node *hare = head;
    // 如果快指针.next是null，说明已经到达末尾，即no cycle
    while (tortoise != NULL && hare != NULL && hare->next != NULL)
    {
        // 1. 前进指针
        tortoise = tortoise->next; // 不需要地址&
        hare = hare->next->next;
        // 2. 判断是否会相遇
        if (tortoise == hare)
        {
            return 1;
        }
    }
    return 0;
}