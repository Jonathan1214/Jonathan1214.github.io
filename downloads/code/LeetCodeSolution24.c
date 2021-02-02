// 链表节点定义
typedef struct ListNode{
    int val;
    struct ListNode *next;
} ListNode;

ListNode *swapPairs(ListNode *head)
{
    if (head == NULL || head->next == NULL)
        return head;
    ListNode *p1, *p2;
    p1 = head;
    p2 = p1->next;
    // 第一次交换
    p1->next = p2->next;
    p2->next = p1;
    head = p2;
    // 其他
    while (p1->next && p1->next->next)
    {
        exch(p1, p1->next);
        p1 = p1->next->next;
    }
    return head;
}

void exch(ListNode *p1, ListNode *p2)
{
    p1->next = p2->next;
    p2->next = p2->next->next;
    p1->next->next = p2;
}