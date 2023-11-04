// n => nums.size()
// Time complexity : O(nlogn)
// Space complexity : O(logn)
class Solution {
public:
    int
    countPairs(vector<int>& nums, int target) {
        // Employ the two pointer approach
        // Condition 'i < j' does not matter as long as numbers at
        // 2 different indices are choosen
        
        // Sort the array
        sort(nums.begin(), nums.end());
        // Init 2 pointers at array ends and move them towards each other
        auto lo = 0;
        auto hi = nums.size() - 1;
        auto nPairs = 0;
        while (lo < hi) {
            // Compute the candidate sum 
            auto candidateSum = nums[lo] + nums[hi];
            if (candidateSum < target) {
                // All nums in the range [lo + 1, hi] form pairs with nums[lo]
                // whose sum is l.t target. Update the pair count
                nPairs += hi - (lo + 1) + 1;
                // Advance 'lo' to check for more pairs
                ++lo;
            } else {
                // All nums in the range [lo, hi] form pairs with whose sum is
                // g.e. target. Need to reduce candidate sum which can be done only
                // by smaller vals of nums[hi]
                --hi;
            }
        }
        
        return nPairs;
    }
};
