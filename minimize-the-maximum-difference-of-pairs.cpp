// n => nums.size()
// M => diff between max and min element in nums
// Time complexity : O(nlogn) + O(nlogM) 
// Space complexity : O(logn) [sorting ops]
class Solution {
public:
    int
    minimizeMax(vector<int>& nums, int p) {
        
        if (0 == p) {
            // Nil pairs required which leads to an empty list;
            // and consequentially to a difference of 0
            return 0;
        }
        
        auto arrSz = nums.size();
        if (p > (arrSz / 2)) {
            // Number of reqd pairs exceeds max possible => error
            return -1;
        }
        
        // Objective is to minimize the max difference between the pairs
        // => Numbers in a pair should be as close together as possible to minimize the
        // max diff between the numbers i.e. Form the pairs using adjacent numbers after
        // sorting the array
        sort(nums.begin(), nums.end());
        
        // Determine the min possible difference with which 'p' paris can be
        // formed via binary search
        // Min diff between 2 numbers in a pair would be 0 (same numbers)
        auto minDiffVal = 0;
        // Max diff pair would be formed by the max and min valued number
        auto maxDiffVal = nums[arrSz - 1] - nums[0];
        
        // Binary search for min possible diff in range [minDiffVal, maxDiffVal]
        int lo = minDiffVal;
        int hi = maxDiffVal;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (reqdNumOfPairsAvailable(nums, p, mid)) {
                // 'p' pairs possible with a max diff of 'mid'
                // This becomes the upper bound of search range and also
                // the min possible diff
                hi = mid;
            } else {
                // 'p' pairs not possible with a max diff of 'mid'
                // This becomes the lower bound of search range. Attempt
                // to get 'p' pairs with higher diff values
                lo = mid + 1;
            }
        }
        
        // The search range converges in a pincer movement to a single value
        // which would be the minimum diff possible for 'p' pairs
        return lo;
    }
    
private:
    
    bool
    reqdNumOfPairsAvailable(vector<int>& numsV, int numReqdPairs, int pairDiff) {
        // Numbers are sorted => pairs with min diff are formed between adjacent nums greedily
        // Iterate over the sorted numbers in sequence
        int arrSz = numsV.size();
        for (int i = 1; i < arrSz; ++i) {
            // Attempt to form a pair between current number and previous number
            // if the diff between them is l.e. max allowed val of 'pairDiff'
            if (numsV[i] - numsV[i - 1] <= pairDiff) {
                // Pair possible. Form a pair and exclude the current number
                // from new pairs
                ++i;
                if (--numReqdPairs == 0) {
                    // Found the required number of pairs
                    return true;
                }
            }
        }
        // Didn't get the required number of pairs
        return false;
    }
};
