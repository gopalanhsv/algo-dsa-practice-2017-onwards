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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        // Base case of one or both lists being empty
        if (nullptr == l1) {
            return l2;
        }
        if (nullptr == l2) {
            return l1;
        }
        
        // Create a new merged list 
        ListNode *mergedListHead = nullptr;
        ListNode *mergedListTail = nullptr;
        // Iterate over both the list elements sequentially. At each step,
        // compare the element values at the head of the two lists, move the
        // element which is smaller of 2 list elements to the tail of 
        // merged list and advance to next element in list from which
        // head has been moved to merged list
        // Do this till either of the lists are completely examined
        while (l1 != nullptr && l2 != nullptr) {
            
            if (l1->val < l2->val) {
                
                if (nullptr == mergedListHead) {
                    mergedListHead = l1;
                } else {
                    mergedListTail->next = l1;
                }
                mergedListTail = l1;
                l1 = l1->next;
                
            } else {
                
                if (nullptr == mergedListHead) {
                    mergedListHead = l2;
                } else {
                    mergedListTail->next = l2;
                }
                mergedListTail = l2;
                l2 = l2->next;

            }
        }
        
        // Attach the list with unexamined elements to the end of
        // merged list
        if (l1) {
            mergedListTail->next = l1;
        } else {
            mergedListTail->next = l2;   
        }
            
        return mergedListHead;
        
    }
};
