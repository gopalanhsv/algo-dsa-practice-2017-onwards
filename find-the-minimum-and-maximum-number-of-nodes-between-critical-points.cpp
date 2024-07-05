// n => num list nodes
// Time complexity : O(n)
// Time complexity : O(1)

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
    vector<int>
    nodesBetweenCriticalPoints(ListNode* head) {
        if (!head || !head->next || !head->next->next) {
            // Base case of list having l.t 3 nodes
            return {-1, -1};    
        } 

        int firstCriticalPt = -1;
        int prevCriticalPt = -1;
        bool twoCriticalPtsSeen = false;
        
        int minDist = numeric_limits<int>::max();
        int maxDist = numeric_limits<int>::min();
        // Iterate over the list from L->R sequentially
        int currLocIdx = 1;
        auto prevNode = head;
        auto currNode = head->next;
        while (currNode->next) {
        
            auto prevVal = prevNode->val;
            auto currVal = currNode->val;
            auto nextVal = currNode->next->val;
            
            if ((currVal > prevVal && currVal > nextVal) ||
                (currVal < prevVal && currVal < nextVal)) {
                
                // Curr node is a critical point (local minima/maxima)
                if (-1 == firstCriticalPt) {
                    // First critical point from head
                    firstCriticalPt = currLocIdx;
                } else {                    
                    // A critical point has been seen earlier during list traversal
                    twoCriticalPtsSeen = true;

                    // Update the min distance to account for distance between
                    // current critical point and preceeding critical point
                    minDist = min(minDist, currLocIdx - prevCriticalPt);
                    // Update the max distance to account for distance between
                    // current critical point and first critical point
                    maxDist = max(minDist, currLocIdx - firstCriticalPt);
                }
                
                // Update the preceeding seen critical point to current node location
                prevCriticalPt = currLocIdx;
            }
            
            // Advance to next node
            ++currLocIdx;
            prevNode = currNode;
            currNode = currNode->next;
        }
        
        if (twoCriticalPtsSeen) {
            return {minDist, maxDist};
        }
        
        return {-1, -1};
    }
};
