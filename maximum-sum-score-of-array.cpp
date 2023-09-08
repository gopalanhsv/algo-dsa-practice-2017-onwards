// n => nums.size()
// Two pass
// Time complexity : O(n)
// Space complexity : O(n)

// Two pass space optimized
// Time complexity : O(n)
// Space complexity : O(1)


class Solution {
public:
    long long
    maximumSumScore(vector<int>& nums) {
        return maximumSumScoreTwoPassSpaceOptimized(nums);
    }
    
    long long
    maximumSumScoreTwoPass(vector<int>& nums) {
        // Sum score at each index is the max of the prefix sum and suffix
        // sum at that index (provided both sums include the index element)
        int arrSz = nums.size();
        // Build the suffix sum array for the input array
        vector<long long> suffixSumV(arrSz, 0);
        suffixSumV[arrSz - 1] = nums[arrSz - 1];
        for (int i = arrSz - 2; i >= 0; --i) {
            auto & currElem = nums[i];
            suffixSumV[i] = currElem + suffixSumV[i + 1];
        }
        
        // Iterate over the array elements from L->R sequentially
        long long prefixSum = 0;
        long long suffixSum = 0;
        long long maxSumScore = numeric_limits<long long>::min();
        for (int i = 0; i < arrSz; ++i) {
            auto & currElem = nums[i];
            // Compute prefix sum at current index
            prefixSum += currElem;
            // Compute the sum score at current index and update the maximum sum score
            long long currIdxSumScore = max(prefixSum, suffixSumV[i]);
            maxSumScore = max(maxSumScore, currIdxSumScore);
        }
        
        return maxSumScore;
    }
    
    long long
    maximumSumScoreTwoPassSpaceOptimized(vector<int>& nums) {
        // Sum score at each index is the max of the prefix sum and suffix
        // sum at that index (provided both sums include the index element)
        int arrSz = nums.size();
        // Sum of all array elements
        long long arrSum = accumulate(nums.begin(), nums.end(), 0LL);
        
        // Iterate over the array elements from L->R sequentially
        long long prefixSum = 0;
        long long suffixSum = 0;
        long long maxSumScore = numeric_limits<long long>::min();
        for (int i = 0; i < arrSz; ++i) {
            auto & currElem = nums[i];
            // Compute prefix and suffix sum at current index
            suffixSum = arrSum - prefixSum;
            prefixSum += currElem;
            // Compute the sum score at current index and update the maximum sum score
            long long currIdxSumScore = max(prefixSum, suffixSum);
            maxSumScore = max(maxSumScore, currIdxSumScore);
        }
        
        return maxSumScore;
    }
};
