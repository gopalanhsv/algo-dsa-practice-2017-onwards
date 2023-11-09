// n => s.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    countHomogenous(string s) {
        auto strSz = s.size();
        const int moduloFactor = 1000000000 + 7;
        // Tracks count of homogenous substrings seen so far
        long nTotalSubStrs = 0;
        
        // Iterate over the string from L->R sequentially
        // Tracks the length of the contiguous sequence of same
        // chars which ends at the current index
        int contSeqLen = 0;
        for (auto currIdx = 0; currIdx < strSz; ++currIdx) {
            // Update the length of contiguous sequence of same chars ending at 'currIdx'
            if ((0 == currIdx) || (s[currIdx] != s[currIdx - 1])) {
                contSeqLen = 1;
            } else {
                ++contSeqLen;
            }
            // Compute the number of homogeneous substrings which are terminated
            // at the current char at 'currIdx'
            auto nSubStrs = contSeqLen;
            // Update the count of homogenous substrings seen so far
            nTotalSubStrs += nSubStrs;
            nTotalSubStrs %= moduloFactor;
        }
        
        return nTotalSubStrs;
    }
};
