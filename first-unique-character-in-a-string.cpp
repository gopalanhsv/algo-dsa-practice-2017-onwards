// n => s.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    firstUniqChar(string s) {
        // Build the string character frequency count table
        vector<int> charFreqTbl(26, 0);
        for (auto & c : s) {
            charFreqTbl[c - 'a']++;
        }

        // Iterate through string sequentially from L->R
        auto pos = 0;
        for (auto & c : s) {
            if (charFreqTbl[c - 'a'] == 1) {
            // First char from L with a frequency count of 1
                return pos;
            }
            ++pos;
        }
        return -1;
    }
};
