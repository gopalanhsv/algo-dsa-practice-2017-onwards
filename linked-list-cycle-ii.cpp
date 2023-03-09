// Time Complexity : O(num list nodes)
// Space Complexity : O(1)

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
    ListNode *
    detectCycle(ListNode *head) {
        // No cycle in case of single node or empty list
        if (nullptr == head || nullptr == head->next) {
            return nullptr;
        }
        
        // Have a slow and fast pointer initialized to head of list
        // Advance the fast pointer at 2X the speed of slow pointer
        // Cycle present is indicated by fast pointer meeting slow
        // pointer in the cycle
        ListNode* slowPtr = head;
        ListNode* fastPtr = head;
        while (nullptr != fastPtr && nullptr != fastPtr->next) {
            // Advance slow pointer by one step
            slowPtr = slowPtr->next;
            // Advance fastPtr pointer by two steps
            fastPtr = fastPtr->next->next;
            
            // If fast pointer meets up with slow pointer, cycle is
            // present
            if (slowPtr == fastPtr) {
                // Determine number of nodes in the cycle
                unsigned ncn = numCycleNodes(slowPtr);
                // Determine cycle start node
                return cycleStartNode(head, ncn);
            }
        }
        
        // No cycle detected and hence null cycle start node
        return nullptr;
    }
    
private:
    
    unsigned
    numCycleNodes(ListNode *cycleNodeP) {
        ListNode *currNode = cycleNodeP;
        unsigned n = 0;
        // Go round the cycle once keeping track of the number of nodes
        // till we get back to point where cycle traversal commenced
        do {
            ++n;
            // Advance to next node in cycle
            currNode = currNode->next;
        } while (currNode != cycleNodeP);
        
        return n;
    }
    
    ListNode*
    cycleStartNode(ListNode *head, unsigned numCycleNodes) {
        // Initialize slow and fast pointers to list head
        // Advance fast pointer ahead of slow pointer by the number
        // of cycle nodes
        ListNode *slowPtr = head;
        ListNode *fastPtr = head;
        while (numCycleNodes) {
            fastPtr = fastPtr->next;
            --numCycleNodes;
        }
        
        // Now move both pointers one step at a time till they meet.
        // At meet point fast pointer would be ahead of slow pointer
        // by the number of cycle nodes (i.e. it is in cycle and has
        // completed one traversal of cycle). Hence they would be meeting
        // at cycle start point
        while (slowPtr != fastPtr) {
            fastPtr = fastPtr->next;
            slowPtr = slowPtr->next;
        }
        
        return slowPtr;
    }
};
