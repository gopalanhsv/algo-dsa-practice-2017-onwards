// Time complexity : O(list size)
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
    partition(ListNode* head, int x) {
        // Base case of single element/empty list
        if (!head || !head->next) {
            return head;    
        }
        
        // x => pivot element
        init();
        
        ListNode* prevNode = nullptr;
        // Iterate through the list sequentially looking for
        // elements l.t. pivot. Move them to the 'lesser' list
        ListNode* currNode = head;
        while (currNode) {
            // Next node
            ListNode * nextNode = currNode->next;
            if (currNode->val < x) {
                // Node l.t pivot element found
                // Remove current node from this list
                if (prevNode) {
                    // Current node is not list head
                    prevNode->next = nextNode;
                } else {
                    // Current node is list head => Update list head
                    head = nextNode;
                }
                currNode->next = nullptr;
                // Append current node to list having solely l.t. pivot elements
                appendToLesserList(currNode);
            } else {
                prevNode = currNode;
            }
            
            // Advance to next node
            currNode = nextNode;
        }
        
        // Now the original list contains element g.e. pivot; while lesser
        // list contains elements l.t. pivot
        // Append the original list to the lesser list; so that the elements
        // l.t. pivot precede the elements g.e. pivot
        appendToLesserList(head);
        
        // Return lesser list head
        return lesserHead();
    }
    
private:
    
    void
    init() {
        _lesserHeadP = nullptr;
        _lesserTailP = nullptr;    
    }
    
    inline ListNode*
    lesserHead() {
        return _lesserHeadP;
    }
    
    void
    appendToLesserList(ListNode* node) {
        
        if (!_lesserHeadP) {
            _lesserHeadP = node;
        } else {
            _lesserTailP->next = node;
        }
        _lesserTailP = node;
    }
    
    // Data members
    ListNode* _lesserHeadP;
    ListNode* _lesserTailP;
};
