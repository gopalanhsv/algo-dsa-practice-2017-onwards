// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    int
    numIdenticalPairs(vector<int>& nums) {
        // Values in 'nums' range is [1, 100]
        // Frequency count table for array elements
        vector<int> freqCntTbl(101, 0);
        
        int nGoodPairs = 0;
        // Iterate over the array from L->R sequentially
        for (auto & num : nums) {
            // Number at current index will form good pairs with all its earlier
            // seen instances (i.e total of old frequency count)
            nGoodPairs += freqCntTbl[num]++;
            // Update frequency count for current number
        }
        
        return nGoodPairs;
    }
};
