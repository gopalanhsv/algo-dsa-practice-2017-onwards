// n => num list nodes
// Time complexity : O(n)
// Space complexity : O(1)
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
    swapNodes(ListNode* head, int k) {
        if (!head || !head->next || (0 == k)) {
            // Base case of empty/single node list or k being '0'
            // => no change to list
            return head;
        }
        
        // Find the 'k'th node from list start
        ListNode* currNode = head;
        for (int i = 1; i != k; ++i) {
            currNode = currNode->next;
        }
        auto kthNodeFromStart = currNode;
        
        // Find the 'k'th node from list end
        // Currently, the head node (slowPtr) is 'k'th node to left from
        // the 'kthNodeFromStart'(fastPtr)
        ListNode* slowPtr = head;
        ListNode* fastPtr = kthNodeFromStart;
        // Advance both fast and slow pointers in lockstep till the 'fastPtr'
        // reaches the list tail
        while (fastPtr->next) {
            slowPtr = slowPtr->next;
            fastPtr = fastPtr->next;
        }
        // Since distance between 'fastPtr' and 'slowPtr' is fixed at 'k - 1',
        // when 'fastPtr' is at list tail, 'slowPtr' would be the 'k'th node
        // from list tail
        auto& kthNodeFromEnd = slowPtr;
        
        // Swap the values of the nodes at 'k'th distance from head and tail of list
        swap(kthNodeFromStart->val, kthNodeFromEnd->val);
        
        return head;
    }
};
