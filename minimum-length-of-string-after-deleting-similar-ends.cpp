// O(string length) time
// O(1) space

class Solution {
public:
    int
    minimumLength(string s) {
        int strSz = s.size();
        if (strSz <= 1) {
            // String has at most a single char => no char removal possible
            return strSz;
        }
        
        // Init two pointers to the string extremities
        int lo = 0;
        int hi = strSz - 1;
        // Length of the string which is retained
        int remainingLen = hi - lo + 1;
        // Move the two pointers at the string ends towards each other; as
        // long ends of remaining portion of string s[lo, hi] are similar
        // and disjoint
        while ((lo < hi) && (s[lo] == s[hi])) {
            // Char which marks the current similar portion of string
            // which should be removed
            auto charBeingRemoved = s[lo];
            // Prefix block of similar chars s[0, lo] gets removed
            while ((lo + 1 < hi) && s[lo + 1] == charBeingRemoved) {
                ++lo;
            }
            
            // Suffix block of similar chars s[hi, strSz - 1] gets removed
            while ((hi - 1 > lo) && s[hi - 1] == charBeingRemoved) {
                --hi;
            }
            
            // Remaining string portion extends from [lo + 1, hi - 1]
            remainingLen = hi - 1 - (lo + 1) + 1;
            
            // Advance the pointers towards each other
            ++lo;
            --hi;
        }
        
        return remainingLen;
    }
};
