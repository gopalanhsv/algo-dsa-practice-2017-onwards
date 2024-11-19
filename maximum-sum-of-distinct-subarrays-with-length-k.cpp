// n => nums.size()
// Time Complexity : O(n)
// Space Complexity : O(k)

class Solution {
public:
    long long
    maximumSubarraySum(vector<int>& nums, int k) {
        // The subarray is simulated using a fixed length k-sized sliding window
        // which moves over the array from L->R. A hash table is used to track the
        // elements present in the subarray (frequency count table)
        
        auto arrSz = nums.size();
        unordered_map<int, int> freqCntTbl;
        auto subArrStart = 0;
        long long maxSubArrSum = 0;
        long long currSubArrSum = 0;
        // Iterate over the array sequentially from L->R
        for (auto subArrEnd = 0; subArrEnd < arrSz; ++subArrEnd) {
            
            // Add current element to subarray
            auto & e = nums[subArrEnd];
            currSubArrSum += e;
            ++freqCntTbl[e];

            if (subArrEnd >= k - 1) {
                // Window/subarray size is 'k' now
                if (k == freqCntTbl.size()) {
                    // Subarray/window has 'k' unique elements and 'k' size
                    // => all elements are distinct
                    // Update the max distinct element subarray sun
                    maxSubArrSum = max(maxSubArrSum, currSubArrSum);
                }
            
                // Shift the start of the subarray/window one element to R, 
                // removing the element at subarray start
                auto se = nums[subArrStart++];
                currSubArrSum -= se;
                if (--freqCntTbl[se] == 0) {
                    freqCntTbl.erase(se);
                }
            }
        }
        
        return maxSubArrSum;
    }
};
