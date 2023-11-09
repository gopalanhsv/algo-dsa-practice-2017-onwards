// n => nums.size()
// Time complexity : O(nlogn)
// Space complexity : O(n)

class Solution {
public:
    int
    maximumBeauty(vector<int>& nums, int k) {
        // Subsequence is generated from original array by just excluding some
        // elements while retaining the ordering; and we are only interested in a
        // a particular maximal length subsequence here (which consists of identical
        // elements after applying specified operation on original array elements
        // once); we can reorder/sort the original array without affecting the final
        // result (as we are dealing with only the subsequence length and not contents)
        // Sorting the elements makes the problem easily solvable
        sort(nums.begin(), nums.end());
        
        auto arrSz = nums.size();
        // After applying operation, nums[x] is in the range [nums[x] - k, nums[x] + k]
        // After sorting,  nums[i] <= nums[j] for i < j as array in sorted
        // => After applying the operation on all elements in the range [i, j]
        // the elements will range between [nums[i] - k, nums[i] + k] TO [nums[j] - k, nums[j] + k]
        
        // All the elements in the range [i, j] can become same after operation iff
        // max(nums[i] - k, nums[i] + k) >= min(nums[j] - k, nums[j] + k) for i < j
        // i.e. nums[i] + k >= nums[j] - k for i < j
        // i.e. nums[j] - nums[i] <= 2k for i < j
        
        // Once all elements are same in [i, j] after sorting & +/-k operation; nums[i, j]
        // becomes a subsequence with equal elements
        
        // Max beauty is the length of the longest subsequence
        // => we need to look for the longest subarray in sorted nums s.t
        // nums[j] - nums[i] <= 2k for i < j
        // Use a sliding window for finding the range [i, j] satisfying above condition

        auto maxLen = 0;
        auto sWinStart = 0;
        // Slide the right side of window one step to the right at each time 
        for (auto sWinEnd = 0; sWinEnd < arrSz; ++sWinEnd) {
            while ((sWinStart <= sWinEnd) && (nums[sWinEnd] - nums[sWinStart] > (k << 1))) {
                //  Shrink the window from the left s.t. it always satisfies invariant 
                // nums[sWinEnd] - nums[sWinStart] <= 2k
                ++sWinStart;
            }
            auto sWinSz = sWinEnd - sWinStart + 1;
            // Update the max length of the window/max beauty
            maxLen = max(maxLen, sWinSz);
        }
        
        return maxLen;
    }
};
