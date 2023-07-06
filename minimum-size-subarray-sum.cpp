// Time complexity : O(nums.size()) / O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    minSubArrayLen(int target, vector<int>& nums) {
    
        // Need to find the minimum length contiguous subarray whose 
        // elems add up to the target or more. 
        
        // Easily solved by using a sliding window 
        return minSubArrayLenViaSlidingWindow(target, nums);
    }
    
private:
    
    int
    minSubArrayLenViaSlidingWindow(int target, vector<int>& nums) {

        // Key idea is to maintain a sliding window over the array whose member sum
        // is >= 'target'. All that needs to be done is to find minimal window length
        int arrSz = nums.size();
        int minSubArrayLen = numeric_limits<int>::max();
        // Window is extends over the array range [sWinStart, sWinEnd]
        int sWinStart = 0;
        int sWinSum = 0;
        // Extend the window to the right by one element in each iteration
        // Iterate over the array elements sequentially from L->R, 
        for (int sWinEnd = 0; sWinEnd < arrSz; ++sWinEnd) {
            // Extend the window to the right by one element updating the window sum
            sWinSum += nums[sWinEnd];
            
            // Shrink the start of window from the left as long at the
            // current window sum exceeds 'target'
            while (sWinSum >= target) {
                // Update the minimum window length with the current window length
                minSubArrayLen = min(minSubArrayLen, sWinEnd - sWinStart + 1);
                sWinSum -= nums[sWinStart++];
            }
        }
        
        return (minSubArrayLen == numeric_limits<int>::max()) ? 0 : minSubArrayLen;
    }
};
