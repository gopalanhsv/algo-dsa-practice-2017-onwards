// n => num list nodes
// Time Complexity : O(n)
// Space Complexity : O(1)

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
    insertGreatestCommonDivisors(ListNode* head) {
        if (!head || !head->next) {
            // Bae case of null/single node list => no GCDs and no insertion reqd
            return head;
        }

        // Iterate over the list nodes sequentially from L->R 
        auto currNode = head;
        while (currNode->next) {
            auto nextNode = currNode->next;
            // Compute the value of new node to be inserted between current and next node
            int newNodeVal = __gcd(currNode->val, nextNode->val);
            // Link the new node between current and next node
            currNode->next = new ListNode(newNodeVal, nextNode);
            // Advance to next node
            currNode = nextNode;
        }
        
        return head;
    }
};
