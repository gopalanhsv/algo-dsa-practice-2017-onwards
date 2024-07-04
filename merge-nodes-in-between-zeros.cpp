// n => Num list nodes
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
    mergeNodes(ListNode* head) {
        if (!head) {
            // Null/empty list
            return head;
        }
        
        // Advance through the list node by node. When a node with value
        // 0 is hit : add up all values of all successive till the next node
        // with 0 value; update the current node value to this sum  and delete
        // all nodes with non-zero value in between the 0 nodes
        
        // Placeholder which holds the sum of all non-0 nodes between
        // current 0 node and consecutive 0 node
        ListNode *mergedNode = head;
        ListNode *currNode = head->next;
        // Iterate through nodes in sequence till the tail node
        while (currNode->next != nullptr) {
            ListNode* nextNode = currNode->next;
            if (currNode->val == 0) {
                // Current node is a 0.
                // Link current node to merged node list (i.e. deleting all non-zero
                // nodes prior to current node till the preceeding 0 node)
                mergedNode->next = currNode;
                // Advance the merged node placeholder to current node
                mergedNode = currNode;   
            } else {
                // Current node in non-0. Add its value to the merged node
                // value and delete it
                mergedNode->val += currNode->val;
                //delete currNode;
            }
            
            // Advance to next node in list
            currNode = nextNode;
        }
        
        // Tail node handling
        mergedNode->next = nullptr;
        //delete currNode;
        
        return head;
    }
};
