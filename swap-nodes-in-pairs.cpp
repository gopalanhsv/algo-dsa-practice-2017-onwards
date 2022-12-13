/**
 * Definition for singly-linked list
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
    swapPairs(ListNode* head) {
        //return swapPairsRecursive(head);
        return swapPairsIterative(head);
    }
    
private:
    
    ListNode*
    swapPairsRecursive(ListNode* head) {
        // Recursion Termination condition (single node/empty list)
        if (!head || !head->next) {
            return head;
        }
        
        // Now swap adjacent nodes for remainder of list post 1st 2 elements
        ListNode *remainingList = swapPairsRecursive(head->next->next);

        // Swap the head and head->next node
        // (1st 2 elements of list starting at head)
        ListNode *headNxt = head->next;
        headNxt->next = head;
        head = headNxt;

        // Attach remainder swapped list after 1st 2 elements
        head->next->next = remainingList;
        
        return head;
    }
    
    ListNode*
    swapPairsIterative(ListNode *head) {
        // Single element, empty list case
        if (!head || !head->next) {
            return head;
        }
        
        // Dummy head to prevent if checks
        ListNode *dummyHead = new ListNode(-1, head);
        ListNode *prevPairSecondNode = dummyHead;
        ListNode *currNode = head;
        
        while (currNode && currNode->next) {
            ListNode *firstNode = currNode;
            ListNode *secondNode = currNode->next;
            ListNode *nextPairFirstNode = secondNode->next;

            // Reverse the links between 1st and 2 nodes
            // Also setup external pointers to/from this pair properly
            secondNode->next = firstNode;
            firstNode->next = nextPairFirstNode;
            prevPairSecondNode->next = secondNode;
            
            // Update pointers to process next set of 2 elements
            prevPairSecondNode = firstNode;
            currNode = nextPairFirstNode;
        }
    
        return dummyHead->next;
    }
    
};
