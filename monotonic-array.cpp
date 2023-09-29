// Time complexity : O(nums.size())
// Space complexity : O(1)
class Solution {
public:
    bool
    isMonotonic(vector<int>& nums) {
        auto arrSz = nums.size();
        if (arrSz <= 1) {
            // Base case : Single/empty array => monotonic by default
            return true;
        }
        
        // Determine if the array is monotonically increasing/decreasing by iterating over
        // it sequentially from L->R till a pair of unequal adjacent elements are hit
        auto i = 1;
        while ((i < arrSz) && (nums[i] == nums[i - 1])) {
            ++i;
        }
        
        if (i == arrSz) {
            // Equal elements array => monotonic
            return true;
        }

        // Unequal adjacent elements found; fixate array type
        bool increasing = (nums[i] > nums[i - i]);
        // Iterate over rest of array 
        for (; i < arrSz; ++i) {
            // For monotonicity, each adjacent element pair should be either be equal or if
            // unequal, follow the same relationship as the first pair of unequal elements
            if (increasing) {
                if (nums[i] < nums[i - 1]) {
                    return false;
                }
            } else {
                if (nums[i] > nums[i - 1]) {
                    return false;
                }
            }
        }
        
        return true;
    }
};
