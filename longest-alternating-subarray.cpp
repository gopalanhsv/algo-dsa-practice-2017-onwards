// Time complexity : O(nums.size())
// Space complexity : O(1)

class Solution {
public:
    int
    alternatingSubarray(vector<int>& nums) {
        auto maxLen = 0;
        auto arrSz = nums.size();
        
        // Iterate over the array sequentially from L->R
        auto idx = 1;
        auto currAlternatingSubArrLen = 0;
        while (idx < arrSz) {
            if (nums[idx] - nums[idx - 1] == 1) {
                // [idx - 1, idx] form an alterating sub array
                if (0 == currAlternatingSubArrLen) {
                    // New alternatng subarray commencement at 'idx - 1'
                    // So length includes [idx - 1, idx]
                    currAlternatingSubArrLen = 2;
                } else {
                    // Continuation of running alternating subarray
                    ++currAlternatingSubArrLen;
                }
                // Advance to next element
                ++idx;
                if ((idx < arrSz) && (nums[idx] - nums[idx - 1] == -1)) {
                    // [idx - 1, idx] continue the running alterating sub array
                    ++currAlternatingSubArrLen;
                    // Advance to next element
                    ++idx;
                } else {
                    // 'idx' terminates the running alterating sub array
                    // Update max alternating subarray len seen so far
                    maxLen = max(maxLen, currAlternatingSubArrLen);
                    // Reset alternating subarray length
                    currAlternatingSubArrLen = 0;
                }
            } else {
                // 'idx' terminates the running alterating sub array if any
                // Update max alternating subarray len seen so far
                maxLen = max(maxLen, currAlternatingSubArrLen);
                    // Reset alternating subarray length
                currAlternatingSubArrLen = 0;
                // Advance to next element
                ++idx;
            }
        }
        
        // Update the max length to include alternating subarray terminating at last element (if any)
        maxLen = max(maxLen, currAlternatingSubArrLen);
        return (maxLen <= 1) ? -1 : maxLen;
    }
};
