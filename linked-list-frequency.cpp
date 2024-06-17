// n => num list elements
// Time complexity : O(n)
// Space complexity : O(n)

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
    frequenciesOfElements(ListNode* head) {
        // Build frequency count table for each unique element in the linked list
        unordered_map<int, int> freqCntTbl;
        auto curr = head;
        while (curr) {
            freqCntTbl[curr->val]++;
            curr = curr->next;
        }
        
        // Iterate over the frequency count table entries and build a new list
        // with only the frequency counts of each unique element
        ListNode *newListHead = nullptr;
        for (auto & ent : freqCntTbl) {
            // Append frequency count of element 'ent.first' to list front
            auto & freq  = ent.second;
            newListHead = new ListNode(freq, newListHead);
        }
        
        return newListHead;
    }
};
