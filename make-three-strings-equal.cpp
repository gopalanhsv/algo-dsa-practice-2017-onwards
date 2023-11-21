// n1 => s1.size(), n2 => s2.size(), n3 => s3.size()
// Time complexity : O(min(n1, n2, n3))
// Space complexity : O(1)

class Solution {
public:
    int
    findMinimumOperations(string s1, string s2, string s3) {
        auto s1Sz = s1.size();
        auto s2Sz = s2.size();
        auto s3Sz = s3.size();
        // Max possible equal length string between s1, s2, s3 would
        // be of min length amongst the 3
        auto maxEqualStrLen = min(min(s1Sz, s2Sz), s3Sz);
        // Init the equal string length to max possible value
        int equalStrLen = maxEqualStrLen;
        // Iterate over the 3 strings in tandem from L->R sequqntially
        for (int idx = 0; idx < maxEqualStrLen; ++idx) {
            // Check for identical chars amongst the 3 strings at current position
            if ((s1[idx] != s2[idx]) || (s1[idx] != s3[idx])) {
                // The 3 strings are no more the same at index
                // The 3 string are at most the same till 'idx - 1'
                if (idx > 0) {
                    equalStrLen = idx;
                } else {
                    // Equal strings impossible as all dont have same first char
                    // => equal null string
                    return -1;
                }
                break;
            }
        }
        
        // All chars to right of 'equalStrLen' char in the 3 string
        // have to be deleted to make them equal
        return s1Sz + s2Sz + s3Sz - (3 * equalStrLen);
    }
};
