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
    modifiedList(vector<int>& nums, ListNode* head) {
        // Build hash table of entries in 'nums'
        unordered_set<int> numsTbl(nums.begin(), nums.end());
        
        // Head and tail nodes of the modified list
        ListNode* modListHead = nullptr;
        ListNode* modListTail = nullptr;
        // Iterate over the original sequentially from L->R
        auto currNode = head;
        while (currNode) {
            // Check for presence of current node val in 'nums'
            auto it = numsTbl.find(currNode->val);
            if (it == numsTbl.end()) {
                // Current node is retained in modified list
                if (!modListHead) {
                    modListHead = currNode;
                } else {
                    modListTail->next = currNode;
                }
                modListTail = currNode;
            } else {
                // Current node is dropped from modified list
            }
            
            // Advance to next node
            currNode = currNode->next;
        }
        
        // Update tail node of modified list
        if (modListTail) {
            modListTail->next = nullptr;
        }
        
        return modListHead;
    }
};
