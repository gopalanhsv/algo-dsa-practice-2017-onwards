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
    deleteDuplicates(ListNode* head) {
#if 0
        // Null/ single node list base case
        if (!head || !head->next) {
            return head;
        }    
        
        // Iterate through the list elements sequentially till
        // tail of the list is hit
        ListNode *prev = head;
        ListNode *curr = head->next;
        while (curr) {
            // Store the next node to current
            ListNode *next = curr->next;
            // Compare current node with previous node
            if (curr->val == prev->val) {
                // Current node has same val as previous node
                // Delete it and unlink current node from list
                prev->next = next;
                delete curr;
            } else {
                // Current node not same as previous, update previous
                // node to current
                prev = curr;
            }
            // Advance to next node
            curr = next;
        }
#else
        // Iterate through the list elements sequentially as long
        // as current node has a node after it (i.e current node is
        // not the tail node)
        ListNode *curr = head;
        while (curr && curr->next) {
            // Compare current node val with that of its successor
            if (curr->val == curr->next->val) {
                // Current node and successor are duplicates, unlink
                // successor from list and delete it
                // No need to advance current
                ListNode *next = curr->next;
                curr->next = next->next;
                delete next;
            } else {
                // Current node and successor are not duplicates
                // Advance current node
                curr = curr->next;
            }
        }
#endif
        return head;
    }
};
