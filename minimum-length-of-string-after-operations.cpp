// n => s.size()
// Time Complexity : O(n)
// Space Complexity : O(1)

class Solution {
public:
    int
    minimumLength(string s) {
        // Minimum length of the string is obtained on deleting the maximum number of characters
        // For deleting maximum characters, order of selecting characters is immaterial. All that
        // is required is to select 3 identical valued characters; and delete the 1st and the 3rd.
        // This operation needs to be repeated until it is no longer possible to select such a group
        // So each group of 3 identical characters reduces the string size by 2 and operation is
        // fully dependent on the frequency count of the chars
        
        int minLen = s.size();
        vector<int> freqCntTbl(26, 0);
        for (auto & c : s) {
            auto & charFreqCnt = ++freqCntTbl[int(c - 'a')];
            if (charFreqCnt == 3) {
                minLen -= 2;
                charFreqCnt -= 2;
            }
        }

        return minLen;
    }
};
