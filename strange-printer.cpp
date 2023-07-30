// n => s.size()
// Time complexity : O(n ^ 3)
// Space complexity : O(n ^ 2)
class Solution {
public:
    int
    strangePrinter(string s) {
        // Preprocess the string to remove adjacent duplicate characters
        // as this will improve the performance and wont affect the final result
        removeAdjacentDupChars(s);
        
        return minTurnsReqdViaBottomUpDp(s);
    }

private:

    void
    removeAdjacentDupChars(string & s) {
        int strSz = s.size();
        int wrIdx = 0;
        for (int rdIdx = 1; rdIdx != strSz; ++rdIdx) {
            if (s[rdIdx] != s[wrIdx]) {
                s[++wrIdx] = s[rdIdx];
            }
        }
        s.resize(wrIdx + 1);
    }

    int
    minTurnsReqdViaBottomUpDp(string & s) {
        int strSz = s.size();
        vector<vector<int> > minTurnsTbl(strSz, vector<int>(strSz, 0));
        
        // Base cases
        // Minimum printing turns required for all possible substrings of size 1 is '1'
        for (int i = 0; i < strSz; ++i) {
            minTurnsTbl[i][i] = 1;
        }
        // Minimum printing turns required for all possible substrings of size 2:-
        // (1) Will be 1 if substring characters are same
        // (2) Will be 2 if substring characters are different
        // Subtring extends over range [sIdx, eIdx]
        for (auto sIdx = 0; sIdx < strSz - 1; ++sIdx) {
            auto eIdx = sIdx + 1;
            if (s[sIdx] == s[eIdx]) {
                minTurnsTbl[sIdx][eIdx] = 1;
            } else {
                minTurnsTbl[sIdx][eIdx] = 2;
            }
        }

        // Minimum printing turns required for substrings of sizes g.t. 2
        for (int subStrSz = 3; subStrSz <= strSz; ++subStrSz) {
            // Iterate over all possible substrings of sizes 'subStrSz'
            // Farthest right possible start location of substring
            auto maxSIdx = strSz - subStrSz;
            for (auto sIdx = 0; sIdx <= maxSIdx; ++sIdx) {
                // Current substring extends over range [sIdx, eIdx]
                // End location of current substring
                auto eIdx = sIdx + subStrSz - 1;
                // Split the current subtring [sIdx, eIdx] into 2 disjoint parts 
                // [sIdx, mIdx] & [mIdx + 1, eIdx]
                // Iterate over all possible locations for 'mIdx' and determine
                // the minimum turns reqd to print substring [sIdx, eIdx]
                int minTurnsForSubStr = numeric_limits<int>::max();
                for (auto mIdx = sIdx; mIdx < eIdx; ++mIdx) {
                    minTurnsForSubStr = 
                        min(minTurnsForSubStr, 
                            minTurnsTbl[sIdx][mIdx] + minTurnsTbl[mIdx + 1][eIdx]);
                }
                minTurnsTbl[sIdx][eIdx] = minTurnsForSubStr;
                if (s[sIdx] == s[eIdx]) {
                    // Start and end chars of string are same, so 1 print from
                    // each split substring can be reduced
                    minTurnsTbl[sIdx][eIdx]--;
                }
            }
        }

        return minTurnsTbl[0][strSz - 1];
    }
};
