ListNode *addTwoNumbers(ListNode *num1, ListNode *num2)
{
    ListNode *theSum, *p = NULL;
    int tmp = 0;   // 保存值
    int carry = 0; // 进位
    while (num1 && num2) {
        tmp = (num1->val + num2->val + carry) % 10;
        carry = (num1->val + num2->val + carry) / 10;
        theSum = (ListNode *)malloc(sizeof(ListNode));
        theSum->val = tmp;
        theSum->next = p;
        p = theSum;
        num1 = num1->next;
        num2 = num2->next;
    }
    // 链表长度不同
    while (num1) {
        tmp = (num1->val + carry) % 10;
        carry = (num1->val + carry) / 10;
        theSum = (ListNode *)malloc(sizeof(ListNode));
        theSum->val = tmp;
        theSum->next = p;
        p = theSum;
        num1 = num1->next;
    }
    while (num2) {
        tmp = (num2->val + carry) % 10;
        carry = (num2->val + carry) / 10;
        theSum = (ListNode *)malloc(sizeof(ListNode));
        theSum->val = tmp;
        theSum->next = p;
        p = theSum;
        num2 = num2->next;
    }
    // 最后进位值不为 0
    if (carry) {
        theSum = (ListNode *)malloc(sizeof(ListNode));
        theSum->val = carry;
        theSum->next = p;
    }
    theSum = reverseLinkedList(theSum);
}
// 反转链表
ListNode *reverseLinkedList(ListNode *head)
{
    ListNode *p = NULL, *q;
    while (head) {
        q = head->next;
        head->next = p;
        p = head;
        head = q;
    }
    return p;
}