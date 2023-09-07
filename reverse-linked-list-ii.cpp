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
    ListNode*
    reverseBetween(ListNode* head, int left, int right) {
        if (!head || !head->next || (left == right)) {
            // Empty/single node list/ position range is single element
            return head;
        }

        // Skip nodes till node marked at position 'left'/list end is reached
        int idx = 1;
        ListNode* prevNode = nullptr;
        ListNode* currNode = head;
        while (currNode && (idx < left)) {
            prevNode = currNode;
            currNode = currNode->next;
            ++idx;
        }
        
        //  Did not hit left
        if (!currNode) {
            return head;
        }

        // Node prior to the range [left, right]
        ListNode* nodePriorToLeft = prevNode;
        // Node at position left. This will go to current 'right'
        // location point post reversal
        ListNode* leftNode = currNode;

        // Reverse nodes starting from node at position 'left'
        // till node at position 'right' is reached
        ListNode * nextNode = currNode->next;
        while (currNode && (idx < right)) {
            ListNode *nextNextNode = (nextNode) ? nextNode->next : nullptr;
            nextNode->next = currNode;
            currNode = nextNode;
            ++idx;
            nextNode = nextNextNode;
        }

        // Link the node at position 'left' to nextNode
        // towards the tail end of list
        leftNode->next = nextNode;

        // Link the head end of list to the original node at
        // position 'right' post reversal
        if (!nodePriorToLeft) {
            // 'left' was head node initially
            head = currNode;
        } else {
            nodePriorToLeft->next = currNode;
        }
        
        return head;
    }
};
