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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        // traverse two lists, get lengths of lists, minus them,
        if ( headA == headB ) return headA;
        ListNode *pA = headA;
        ListNode *pB = headB;
        ListNode *pp = nullptr;
        int lenDiff = 0;
        while ( pA && pB ) {
            pA = pA->next;
            pB = pB->next;
        }
        
        if ( pB ) { // listB is longer
            pp = headB;
            pA = headA;
            while ( pB ) {
                pp = pp->next;
                pB = pB->next;
            }
            while ( pp && pA ) {
                if ( pp == pA )
                    return pp;
                pp = pp->next;
                pA = pA->next;
            }
        }
        
        if ( pA ) { // listA is longer
            pp = headA;
            pB = headB;
            while ( pA ) {
                pp = pp->next;
                pA = pA->next;
            }
            while ( pp && pB ) {
                if ( pp == pB )
                    return pp;
                pp = pp->next;
                pB = pB->next;
            }
        }
        
        // length equally
        pA = headA;
        pB = headB;
        while ( pA && pB ) {
            if ( pA == pB )
                return pA;
            pA = pA->next;
            pB = pB->next;
        }
        return nullptr;
    }
};