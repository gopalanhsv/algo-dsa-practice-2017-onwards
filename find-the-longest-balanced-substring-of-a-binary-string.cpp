// Time complexity : O(string size)
// Space complexity : O(1)

class Solution {
public:
    int
    findTheLongestBalancedSubstring(string s) {
        int maxHalfLen = 0;
        int nZeroes = 0;
        int nOnes = 0;
        // Iterate over the characters of the string sequentially
        for (auto & c : s) {
            if ('1' == c) {
                // Current char is '1'
                // Increment the number of '1's seen in current block
                ++nOnes;
                // Compute the (half) length of balanced substring which is either
                // ending at the current '1' OR commencing at the first '0' seen after
                // the end of the previous block of '1''s
                int balancedSubstrHalfLen = min(nOnes, nZeroes);
                // Update the max (half) length of balanced substrings seen so far
                maxHalfLen = max(maxHalfLen, balancedSubstrHalfLen);
            } else {
                // Current char is '0'
                if (nOnes > 0) {
                    // New block of '0's followed by '1's commences here
                    nZeroes = 0;
                    nOnes = 0;
                }
                // Increment the number of '0's in current block
                ++nZeroes;
            }
        }
        
        // Double the max half-length of balanced substring seen
        return maxHalfLen << 1;
    }
};
