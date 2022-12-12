/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode*
    removeNthFromEnd(ListNode* head, int n) {
        if (!head || (n <= 0)) {
            // Empty list/invalid n
            return head;
        }
        
        // Solve using two pointers slow and fast
        
        // Initially both pointers point to list head
        ListNode *slowP = head, *fastP = head;
        // Advance the fast pointer by 'n' nodes to nth node from list
        // head, s.t the two pointers are spaced apart by 'n' nodes
        while (--n > 0) {
            fastP = fastP->next;
        }
        // Tracks the previous node to current one pointed by slow pointer
        ListNode *prevToSlowP = nullptr;
        // Advance the two pointers in lock-step one node at a time till
        // the fast pointer hits the list tail. At this juncture, the
        // slow pointer will be at the nth node from list tail
        while (nullptr != fastP->next) {
            fastP = fastP->next;
            prevToSlowP = slowP;
            slowP = slowP->next;
        }
        
        // Remove node pointed by slow pointer from list
        // Unlink slow pointer node from list and remove it
        if (!prevToSlowP) {
            // Slow pointer is list head
            head = slowP->next;
        } else {
            prevToSlowP->next = slowP->next;
        }
        delete slowP;
        
        return head;
    }
};
