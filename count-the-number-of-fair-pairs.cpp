// n => nums.size()
// Time complexity : O(nlogn)
// Space complexity : O(logn)

class Solution {
public:
    long long
    countFairPairs(vector<int>& nums, int lower, int upper) {

        // Employ the two pointer approach
        // Condition 'i < j' does not matter as long as numbers at
        // 2 different indices are choosen since nums[i] + nums[j] is
        // identical to nums[j] + nums[i]
        
        // Sort the array to be ascending order
        sort(nums.begin(), nums.end());
        
        // Init 2 pointers at [lo, hi] and move them towards each other
        auto hi = nums.size() - 1;
        auto lo = 0;
        long long nPairsLEUpper = 0;
        while (lo < hi) {
            // Compute the candidate sum 
            long long candidateSum = (long long)nums[lo] + nums[hi];
            if (candidateSum <= (long long)upper) {
                // All nums in the range [lo + 1, hi] form pairs with nums[lo]
                // which are l.e 'upper'
                nPairsLEUpper += hi - lo;
                // Advance 'lo' to check for more fair pairs
                ++lo;
            } else {
                // All nums in the range [lo, hi] form pairs nums[lo] with whose
                // sum is g.t 'upper'. Need to reduce candidate sum which can
                // be done only by smaller vals of nums[hi]
                --hi;
            }
        }
        
        hi = nums.size() - 1;
        lo = 0;
        long long nPairsLTLower = 0;
        while (lo < hi) {
            // Compute the candidate sum 
            long long candidateSum = (long long)nums[lo] + nums[hi];
            if (candidateSum < (long long)lower) {
                // All nums in the range [lo + 1, hi] form pairs with nums[lo]
                // which are l.t 'lower'
                nPairsLTLower += hi - lo;
                // Advance 'lo' to check for more fair pairs
                ++lo;
            } else {
                // All nums in the range [lo, hi] form pairs nums[lo] with whose
                // sum is g.e 'lower'. Need to reduce candidate sum which can
                // be done only by smaller vals of nums[hi]
                --hi;
            }
        }
        
        // Num fair pairs are in pairs with sum in range [lower, upper]
        return nPairsLEUpper - nPairsLTLower;
    }
};
