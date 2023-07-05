// Time complexity : O(nums.size()) / O(n)
// Space complexity : O(1)
class Solution {
public:
    int
    longestSubarray(vector<int>& nums) {
        
        // Problem reduces to finding the longest subarray of contiguous 1's with
        // at most single 0; which allows for deletion of 0 leaving only 1's
        // Size of the biggest such subarray reduced by one element would be
        // the longest subarray of 1's after deleting one element
        typedef vector<int>::size_type vecSzT;
        // Form a sliding window, adding one element to right of the window
        // in each iteration. Ensure that the sliding window has a maximum of
        // one 0 element always (slated for deletion)
        vecSzT maxSubArrayLen = 0;
        vecSzT sWinOnesCnt = 0; // Number of 1's in window
        vecSzT sWinStart = 0; // Current window start
        // Window extends in the range [sWinStart, sWinEnd]
        for (vecSzT sWinEnd = 0; sWinEnd != nums.size(); ++sWinEnd) {
            // Add element at 'sWinEnd' to current window
            // Num of ones in current window
            if (nums[sWinEnd] == 1) {
                ++sWinOnesCnt;
            }
            // Current window length
            vecSzT sWinLen = sWinEnd - sWinStart + 1;
            
            while (sWinLen - sWinOnesCnt > 1) {
                // Number of zeroes in window exceeds max allowed
                // Shrink window from left
                if (nums[sWinStart++] == 1) {
                    // Update the count of 1's in window if window start was a 1
                    --sWinOnesCnt;
                }
                --sWinLen;
            }

            // Update max sub array size
            maxSubArrayLen = max(maxSubArrayLen, sWinEnd - sWinStart + 1);  
        }
        
        // Max binary subarray size with at most one 0 
        // (-1 is for deletion)
        return maxSubArrayLen - 1;
    }
};
