/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow_p = head;
        ListNode *fast_p = head;
        bool hasCircle = false;
        while ( fast_p && fast_p->next ) { // detect circle
            slow_p = slow_p->next;
            fast_p = fast_p->next->next;
            if ( slow_p == fast_p ) {
                hasCircle = true;
                break;
            }
        }
        if ( hasCircle ) { // find circle start
            fast_p = head;
            while ( fast_p != slow_p ) {
                fast_p = fast_p->next;
                slow_p = slow_p->next;
            }
            return slow_p;
        } else
            return nullptr;
    }
};