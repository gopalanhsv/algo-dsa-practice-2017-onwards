// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    longestOnes(vector<int>& nums, int k) {
        
        // Problem reduces to searching for the maximum length subarray
        // consisting of ones with at most 'k' zeroes (these will be toggled).
        // => Sliding window usage 

        auto arrSz = nums.size();
        auto sWinOnesCnt = 0;
        auto sWinStart = 0;
        auto maxWinSize = 0;
        // Iterate over the array from L->R extending the sliding window to
        // the right while tracking the number of 0's in the window
        for (auto sWinEnd = 0; sWinEnd != arrSz; ++sWinEnd) {
            // Advance the window one element to right
            if (nums[sWinEnd] == 1) {
                ++sWinOnesCnt;
            }
    
            auto sWinSize = sWinEnd - sWinStart + 1;
            if (sWinSize - sWinOnesCnt > k) {
                // Number of zeros within the window exceeds max allowed 'k'
                // => Shrink window from left
                if (nums[sWinStart] == 1) {
                    --sWinOnesCnt;
                    
                }
                ++sWinStart;
                --sWinSize;
            }
            
            // Update max window size
            maxWinSize = max(sWinSize, maxWinSize);
        }
        
        return maxWinSize;
    }
};
