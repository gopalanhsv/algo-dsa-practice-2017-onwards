// Time complexity : O(max(a, b))
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
    mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        
        // Error check
        if (a > b) {
            return nullptr;
        }
        if (!list2 || !list1) {
            return nullptr;
        }
        
        // Determine tail node of list#2
        auto list2Head = list2;
        auto list2Tail = list2;
        while (list2Tail->next) {
            list2Tail = list2Tail->next;
        }
        
        // Determine node prior to 'a'th node of list#1, i.e. 'a - 1'th node
        ListNode* prevNode = nullptr;
        auto currNode = list1;
        for (auto i = 0; i < a; ++i) {
            prevNode = currNode;
            currNode = currNode->next;
        }
        auto nodePriorToNodeA = prevNode;
        
        // Determine node next to 'b'th node of list#1, i.e. 'b + 1' th node
        for (auto i = a; i <= b; ++i) {
            currNode = currNode->next;
        }
        auto nodeNextToNodeB = currNode;
        
        // Append list#2 after node prior to list#1 'a' th node
        ListNode* newListHead = list1;
        if (!nodePriorToNodeA) {
            newListHead = list2;
        } else {
            nodePriorToNodeA->next = list2;
        }
        
        // Append list#1 portion after bth node to end of list#2
        list2Tail->next = nodeNextToNodeB;
        
        return newListHead;
    }
};
