// Time complexity : O(1)
// Space complexity : O(1)

class Solution {
public:
    bool
    isStrictlyPalindromic(int n) {
        // Since input is always g.e. 4,
        // Start working with nos g.e. 4
        

        // Consider n = 4 in all bases of interest [2, n - 2] i.e. [2, 4 - 2] =>
        // base in range [2, 2] => leads to representation as 100 which is non palindromic
        
        // For n > 4
        // n in base n - 1 is 11 which is non-palindromic
        // i.e (n in base 11 is represented as  [1 * {(n - 1) ^ 1} + 1 * {(n - 1) ^ 0}]
        
        // n in base n - 2 is 12 which is non-palindromic
        // i.e (n in base 12 is represented as [1 * {(n - 2) ^ 1} + 2 * {(n - 2) ^ 0}]
        // ..... and so on
        
        // So all numbers g.t. 4 are not strictly palindromic. And 4 lies in same cat
        return false;
    }
};
