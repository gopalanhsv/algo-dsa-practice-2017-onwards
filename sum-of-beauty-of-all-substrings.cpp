// n => s.size()
// Time complexity : O(n ^ 2)
// Space complexity : O(26)

class Solution {
public:
    int
    beautySum(string s) {
        
        // Form all possible substrings and add up their beauty
        auto strSz = s.size();
        int totalBeautySum = 0;
        // Iterate sequentially over all possible substring start indices(exclude
        // last char as beauty would be 0)
        for (auto start = 0; start < strSz - 1; ++start) {
            // Occurence count table for all chars in the substring commencing at 'start'
            vector<int> chrFreqCntTbl(26, 0);
            int maxFreqCnt = 1;
            chrFreqCntTbl[s[start] - 'a'] = 1;
            // Iterate sequentially over all possible substring end indices for
            // the substring commencing at 'start'
            for (auto end = start + 1; end < strSz; ++end) {
                auto & currChr = s[end];
                auto currChrFreqCnt = ++chrFreqCntTbl[currChr - 'a'];
                // Determine the min frequency count for the substring s[start, end]
                maxFreqCnt = max(maxFreqCnt, currChrFreqCnt);
                // Determine the min frequency count for the substring s[start, end]
                int minFreqCnt = maxFreqCnt;
                for (auto & freqCnt : chrFreqCntTbl) {
                    if ((0 != freqCnt) && (freqCnt < minFreqCnt)) {
                        minFreqCnt = freqCnt;
                    }
                }
                // Determine the beauty for the substring s[start, end] and add it to total beauty
                totalBeautySum += maxFreqCnt - minFreqCnt;
            }
        }

        return totalBeautySum;
    }
};
