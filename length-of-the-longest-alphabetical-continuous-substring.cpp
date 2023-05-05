// Time complexity : O(s.size())
// Space complexity : O(1)

class Solution {
public:
    int
    longestContinuousSubstring(string s) {
        int strLen = s.size();
        if (strLen <= 1) {
            // Base case of null/single char string
            return strLen;
        }

        // Tracks the max continuous string length seen so far
        // Initialized to a single char len string
        int maxContStrLen = 1;
        // Tracks the start of the current continous string
        int strStart = 0;
        auto prevChr = s[0];
        // Tracks the current continuous string length
        int contStrLen = 1;
        // Iterate over the string chars sequentially from L->R
        for (auto & currChr : s) {
            
            if (int(currChr - prevChr) != 1) {
                // A new continuous string commences from the current char
                // and the continuous string uptill the previous char terminates
                // Update the maximum continuous string length to account for
                // the one terminated at the previous char
                maxContStrLen = max(maxContStrLen, contStrLen);
                // Commence a new continuous string from current char
                contStrLen = 1;
            } else {
                // Continuous string uptill the previous char continues to
                // current char
                ++contStrLen;
            }
            prevChr = currChr;
        }
        // Update the maximum continuous string length to account for
        // the one terminated at the last string char
        maxContStrLen = max(maxContStrLen, contStrLen);
        return maxContStrLen;
    }
};
