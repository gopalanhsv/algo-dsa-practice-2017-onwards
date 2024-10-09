// n => s.size()
// Time Complexity : O(n)
// Space Complexity : O(1)

class Solution {
public:
    int
    minAddToMakeValid(string s) {
        // The string 's' is made valid as follows:-
        // (1) Adding an open paranthesis to balance out each unbalanced closed
        // parathesis ocurring to its right
        // (2) Adding a closed paranthesis to balance out each unbalanced open
        // parathesis ocurring to its left
        // => min addition operations would be the number of unbalanced paranthesis
        // chars in the string
        
        // Tracks the number of respective unbalanced paranthesis
        int nUnbalancedOpenParanSeenSoFar = 0;
        int nUnbalancedClosedParanSeenSoFar = 0;    
        // Iterate over the string from L->R sequentially
        for (auto & c : s) {
            if (')' == c) {
                // Encountered a 'closed' paranthesis. Use it to balance out any 
                // unbalanced 'open' paranthesis seen if any, else store it 
                if (nUnbalancedOpenParanSeenSoFar > 0) {
                    --nUnbalancedOpenParanSeenSoFar;
                } else {
                    ++nUnbalancedClosedParanSeenSoFar;
                }
            } else {
                // Encountered an 'open' paranthesis. Store it
                ++nUnbalancedOpenParanSeenSoFar;
            }
        }
        
        return nUnbalancedOpenParanSeenSoFar + nUnbalancedClosedParanSeenSoFar;
    }
};
