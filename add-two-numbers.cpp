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
    addTwoNumbers(ListNode* l1, ListNode* l2) {
        
        ListNode *sumListHead = nullptr, *sumListTail = nullptr;
        ListNode *l1ListIter = l1;
        ListNode *l2ListIter = l2;
        int carry = 0;
        
        // Add numbers from one/both/none lists in tandem (till list elements from both
        // fully examined and carry exhausted) with running carry value and store
        // result as a new tail element to the sum list
        while (l1ListIter || l2ListIter || carry) {
            // Compute sum of current l1, l2 list elements and carry
            int sum = carry;
            
            if (l1ListIter) {
                sum += l1ListIter->val;
                l1ListIter = l1ListIter->next;
            }
            
            if (l2ListIter) {
                sum += l2ListIter->val;
                l2ListIter = l2ListIter->next;
            }
            
            // Add units part of sum at tail of new list
            if (sumListTail) {
                sumListTail->next = new ListNode(sum % 10);
                sumListTail = sumListTail->next;
            } else {
                sumListTail = new ListNode(sum % 10);
                sumListHead = sumListTail;
            }
            // Update carry to account to for above
            carry = sum / 10;
            
        }
        
        
        return sumListHead;
        
    }
};
