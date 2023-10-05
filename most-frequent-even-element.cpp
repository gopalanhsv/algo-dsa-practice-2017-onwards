// m => nums.size()
// Time complexity : O(n)
// Space complexity : O(n)
class Solution {
public:
    int
    mostFrequentEven(vector<int>& nums) {
        int maxFreq = 0;
        int elemWithMaxFreq = numeric_limits<int>::max();
        // Iterate over each element and construct frequency count table for all even elements
        unordered_map<int, int> elemFreqCntTbl;
        for (auto & num : nums) {
            if (0 == (num & 0x1)) {
                // Even element  => Update frequency count
                auto & elemFreqCnt = ++elemFreqCntTbl[num];
                // Select the smallest element with max frequency
                if (elemFreqCnt > maxFreq) {
                    // Select current elem as it has highest occurence seen so far
                    elemWithMaxFreq = num;
                    maxFreq = elemFreqCnt;
                } else if (elemFreqCnt == maxFreq) {
                    // Current element has identical occurence count to highest seen
                    // Select the smallest one
                    elemWithMaxFreq = min(elemWithMaxFreq, num);
                }
            }
        }
        
        return elemWithMaxFreq == numeric_limits<int>::max() ? -1 : elemWithMaxFreq;
    }
};
