// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(n)
class Solution {
public:
    int
    maxFrequencyElements(vector<int>& nums) {
        // Iterate over the array and build frequency count table of array elements
        unordered_map<int, int> freqCntTbl;
        int maxFreqCntSeen = 0;
        int nUniqueElemWithMaxFreq = 0;
        for (auto & num : nums) {
            auto & currElemFreqCnt = ++freqCntTbl[num];
            if (currElemFreqCnt > maxFreqCntSeen) {
                // Current element is the sole element with max frequency
                // count amongst all those seen so far
                maxFreqCntSeen = currElemFreqCnt;
                nUniqueElemWithMaxFreq = 1;
            } else if (currElemFreqCnt == maxFreqCntSeen) {
                // Current element is the one of the several elements with
                // max frequency count amongst all those seen so far
                ++nUniqueElemWithMaxFreq;
            }
        }
        
        return maxFreqCntSeen * nUniqueElemWithMaxFreq;
    }
};
