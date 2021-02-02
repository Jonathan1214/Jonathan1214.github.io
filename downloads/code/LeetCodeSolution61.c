ListNode *rotateRight(ListNode *head, int k)
{
    if (head == NULL || k <= 0)
        return head;
    ListNode *pre, *last, *p;
    ListNode tmpNode;
    tmpNode.next = head;
    last = &tmpNode;
    p = head;
    int ak = k;
    while (k > 0){
        // 滑动指针来代替循环
        if (p == NULL) {
            int tmp = ak - k;
            pre = &tmpNode;
            p = head;
            k = ak % tmp;
            if (k == 0) break;
        }
        pre = p;
        p = p->next;
        k--;
    }
    while (p != NULL) {
        last = last->next;
        pre = p;
        p = p->next;
    }
    if (last != &tmpNode) {
        pre->next = head;
        tmpNode.next = last->next;
        last->next = NULL;
    }
    return tmpNode.next;
}