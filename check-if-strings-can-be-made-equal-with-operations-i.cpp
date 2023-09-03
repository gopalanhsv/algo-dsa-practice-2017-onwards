// Time complexity : O(1)
// Space complexity : O(1)
class Solution {
public:
    bool
    canBeEqual(string s1, string s2) {
        // Since indices 'i' & 'j' must be choosen s.t. j - i = 2 for swapping,
        // and the string lengths of 2 strings is 2 there are only 2 options
        // for swapping:- indices 0 & 2 AND/OR indices 1 & 3. Swapping for these
        // set of location pairs needs to done only once if required, as swapping
        // twice for a set of location pairs restores back initial placement
        if ((s1[0] != s2[0]) || (s1[2] != s2[2])) {
            // String chars at indices s1/0 AND/OR s2/2 dont match
            // Test if swapping chars at these locations results in a match
            if ((s1[2] != s2[0]) || (s1[0] != s2[2])) {
                // Match fail
                return false;
            }
        }

        if ((s1[1] != s2[1]) || (s1[3] != s2[3])) {
            // String chars at indices s1/1 AND/OR s2/3 dont match
            // Test if swapping chars at these locations results in a match
            if ((s1[3] != s2[1]) || (s1[1] != s2[3])) {
                // Match fail
                return false;
            }
        }
        
        return true;
    }
};
