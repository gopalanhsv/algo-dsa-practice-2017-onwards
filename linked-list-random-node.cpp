// Time complexity
// init() : O(1)
// getRandom : O(num list nodes)

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
    Solution(ListNode* head) {
        
        // Set the seed for random number generator
        _gen.seed(time(0));
        // Init linked list head
        _lstHead = head;
    }
    
    int
    getRandom() {
        return getRandomApproach1();
        //return getRandomApproach2();
    }

private:

    int
    getRandomApproach1() {    
        // Reservoir sampling technique algorithm-R is used to 
        // sample a random node from the list with each node having
        // the same probability of getting selected
        
        // Count of nodes traversed so far
        unsigned nSeenNodes = 0;
        ListNode* cn = _lstHead;
        // Reservoir of size '1'
        int selectedNodeVal = cn->val;
        while (cn) {
            // Traverse current node and check if it can be included
            // in the reservoir of size '1'
            ++nSeenNodes;
            // Generate a random number in the range [1, nSeenNodes]
            uniform_int_distribution<unsigned> ud(1, nSeenNodes);
            unsigned randNum = ud(_gen);
            if (randNum <= 1) {
                // Generated number is l.e reservoir size => it
                // replaces the value stored in the reservoir
                selectedNodeVal = cn->val;
            }
            
            // Advance to next node 
            cn = cn->next;
        }
        
        return selectedNodeVal;
    }
    
    int
    getRandomApproach2() {    
        // Reservoir sampling technique algorithm-R is used to 
        // sample a random node from the list with each node having
        // the same probability of getting selected
        
        // Count of nodes traversed so far
        unsigned nSeenNodes = 0;
        
        // Generates an equiprobable random number in the range [0.0, 1.0)
        uniform_real_distribution<double> ud(0.0, 1.0);
        
        ListNode* cn = _lstHead;
        // Reservoir of size '1'
        int selectedNodeVal = cn->val;
        while (cn) {
            // Traverse current node and check if it can be included
            // in the reservoir of size '1'
            ++nSeenNodes;
            // Generate a random number in the range [0.0, 1.0]
            double randNum = ud(_gen);
            if (randNum < (1.0 / nSeenNodes)) {
                // Generated number is l.e reservoir size => it
                // replaces the value stored in the reservoir
                selectedNodeVal = cn->val;
            }
            
            // Advance to next node 
            cn = cn->next;
        }
        
        return selectedNodeVal;
    }
    // Data members

    // Random number generator for reservoir sampling
    default_random_engine _gen;
    // Head of input list
    ListNode* _lstHead;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */
