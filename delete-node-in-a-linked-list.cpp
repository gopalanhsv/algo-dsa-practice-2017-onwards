// n => num list nodes
// Time complexity : O(n)
// Time complexity : O(1)

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
    void
    deleteNode(ListNode* node) {
    
        // Since the 'next' pointer of node prior to node being deleted as previous/head
        // node is unavailable, the only option is to copy the subsequent node value to
        // current/prior node value commencing from node to be deleted. This has to be done
        // for all nodes down to list tail. Then delete the list tail node
        while (node->next->next != nullptr) {
            // Copy next node value to current node
            node->val = node->next->val;
            // Advance to next node
            node = node->next;
        }
        
        // Do the copy operation for 2nd last node (it will be new tail)
        // and delete the old tail node
        node->val = node->next->val;
        delete node->next;
        node->next = nullptr;
    }
};
