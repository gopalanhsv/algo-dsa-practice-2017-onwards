// Time complexity : O(num list nodes)
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
    int
    pairSum(ListNode* head) {
        if (!head || !head->next) {
            return 0;
        }

        return maxPairSumViaListReversal(head);
    }
    
private:
    
    int
    maxPairSumViaListReversal(ListNode* head) {
        
        // The node pairs for determining the twin sum can be selected one
        // pair at a time by either one of the following 2 approaches :-
        // 1. Two ends of the list to the middle of the list, OR
        // 2. Middle of the list to the two ends of the list
        
        // Approach 1 requires reversal of the 2nd half of the list
        
        // Find the middle node of the list by using two pointers (a fast
        // pointer moving at 2x the speed of slow pointer)
        auto slowPtr = head;
        auto fastPtr = head;
        while (fastPtr && fastPtr->next) {
            slowPtr = slowPtr->next;
            fastPtr = fastPtr->next->next;
        }
        
        // Reverse the 2nd half of the linked list
        auto secondHalfReversedListHead = reverseList(slowPtr);
        
        // Have 2 pointers, one at head of first half of initial list
        // and second at head of second half of initial list reversed
        auto list1Ptr = head;
        auto list2Ptr = secondHalfReversedListHead;
        int maxTwinSum = 0;
        // Move pointers in lockstep, computing the pair sum for
        // every valid pair of nodes
        // (Using 2 list tail node as marker for ending the iteration
        // as that is the only one set to null)
        while (list2Ptr) {
            maxTwinSum = max(maxTwinSum, list1Ptr->val + list2Ptr->val);
            list1Ptr = list1Ptr->next;
            list2Ptr = list2Ptr->next;
        }
        
        return maxTwinSum;
    }
    
private:
    
    ListNode*
    reverseList(ListNode *head) {
        
        ListNode* prevNode = nullptr;
        auto currNode = head;
        while (currNode) {
            // Reverse the link between current node and previous node
            auto nextNode = currNode->next;
            currNode->next = prevNode;
            // Advance to the next node for repeating reversal
            prevNode = currNode;
            currNode = nextNode;
        }
        // Head of reversed list
        return prevNode;
    }
};
