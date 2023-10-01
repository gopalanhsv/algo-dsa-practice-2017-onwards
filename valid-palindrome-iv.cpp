// Time complexity : O(s.size())
// Space complexity : O(1)

class Solution {
public:
    bool
    makePalindrome(string s) {
        
        auto strSz = s.size();
        if (strSz <= 3) {
            // Base case of string having :-
            // 1 char => already palindromic
            // 2 char => needs at most 1 char change to make it palindromic
            // 3 char => needs at most 2 char changes (at string ends) to make it palindromic
            return true;
        }
        
        // Init two pointers at string ends. Move them towards each other one step at time
        // comparing string chars equidistant from string ends. If the chars are no equal,
        // to make the string palindromic, use 1 replacement operation to make the chars equal
        int nOperations = 0;
        int lo = 0;
        int hi = s.size() - 1;
        while (lo < hi) {
            if (s[lo] != s[hi]) {
                // Chars equidistant from string ends require 1 replacement operation
                // in order to make the equal and the substring from either end equal
                ++nOperations;
            }
            // Advance the two pointers
            ++lo, --hi;
        }
        // Valid palindrome in # replacements is l.e 2
        return (nOperations <= 2);
    }
};
