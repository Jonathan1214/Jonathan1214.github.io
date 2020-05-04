// 链表节点定义
typedef struct {
    int val;
    ListNode *next;
} ListNode;

ListNode *delete(ListNode *head, int n) {
    if (head == NULL) return;
    ListNode *p1 = head, *p2 = head;
    // 滑动指针 p1
    for (; n > 0; n--)
        p1 = p1->next;
    // 同时滑动 p1 和 p2 直到 p1 指向最后一个节点
    while (p1->next != NULL) {
        p1 = p1->next;
        p2 = p2->next;
    }
    // 删除节点
    ListNode *tmp = p2->next;
    p2->next = tmp->next;
    free(tmp); // 释放
    return head;
}

