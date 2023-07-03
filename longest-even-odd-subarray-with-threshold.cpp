// Time complexity : O(nums.size()) / O(n)
// Space complexity : O(1)
class Solution {
public:
    int
    longestAlternatingSubarray(vector<int>& nums, int threshold) {
        
        int arrSz = nums.size();
        
        int maxSubArrLen = 0;
        // Iterate over the array elements sequentially from L->R
        for (int subArrLeftIdx = 0; subArrLeftIdx < arrSz;) {
            auto val = nums[subArrLeftIdx];
            if ((val <= threshold) && (0 == (val & 1))) {
                // A new even-odd subarray commences at current element
                
                // Advance to the right sequentially from the current index and
                // determine the right/ending of current even-odd subarray
                auto subArrRightIdx = subArrLeftIdx + 1;
                auto prevVal = val;
                while (subArrRightIdx < arrSz) {
                    val = nums[subArrRightIdx];
                    if ((val > threshold) ||
                        ((val & 1) == (prevVal & 1))) {
                        // Reached an element which cannot be a part of current
                        // even odd subarray (subarray ends at previous element)
                        break;
                    }
                    
                    prevVal = val;
                    ++subArrRightIdx;
                }
                
                // Compute the subarray length and update the max subarray length seen
                auto subArrLen = subArrRightIdx - subArrLeftIdx;
                maxSubArrLen = max(maxSubArrLen, subArrLen);
                // Continue the search to the right for a new subarray
                subArrLeftIdx = subArrRightIdx;
            } else {
                ++subArrLeftIdx;
            }
        }
        
        return maxSubArrLen;
    }
};
