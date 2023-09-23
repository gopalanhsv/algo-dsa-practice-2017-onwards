// Time complexity : O(s.size() + t.size())
// Space complexity : O(1)

class Solution {
public:
    bool
    isSubsequence(string s, string t) {
        // Empty string is subsequence of every string
        if (s.empty()) {
            return true;
        }
        
        typedef string::size_type strSzT;
        // Iterate through subsequence 's' chars sequentially
        strSzT nextSubSeqCharPosInTargetStr = 0;
        for (auto & subSeqChar : s) {
            // Locate current subsequence char in target string to the right of the previously
            // found subsequence char in target string. All subsequence chars should exist in target
            strSzT subSeqPosInTarget = t.find(subSeqChar, nextSubSeqCharPosInTargetStr);
            if (subSeqPosInTarget == string::npos) {
                // Subsequence char not found in target string to right of
                // previous subsequence char position
                return false;
            }
            // Set search start location in target for next subsequence char
            nextSubSeqCharPosInTargetStr = subSeqPosInTarget + 1;
        }
        
        // All subsequence chars found in target in correct sequence
        return true;
    }
};
