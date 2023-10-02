// Time complexity : O(nums.size())
// Space complexity : O(1)

class Solution {
public:
    int
    longestSubarray(vector<int>& nums) {
        int arrSz = nums.size();
        if (arrSz <= 1) {
            return arrSz;
        }

        // Maximum possible bitwise AND of 2 numbers will always be l.e the maximum of two numbers
        // (due to different bits being set in the two numbers (if different)). If the two numbers
        // are same, one get the max possible bitwise AND which would the number in itself
        
        // So the max possible bitwise AND of any subarray would have the value of the
        // maximum element of the subarray; and the longest such subarray would be the
        // one with the longest adjacent series of maximum array element
        int maxElem = nums[0];
        int longestSubArrSz = 1;
        int currMaxElemSubArrSz = 1;
        // Iterate over the array sequentially from L->R
        for (auto i = 1; i < arrSz; ++i) {
            auto & currElem = nums[i];
            if (currElem > maxElem) {
                // Current element is a new max element
                // Commence a new subarray which consists of the max element
                currMaxElemSubArrSz = 1;
                maxElem = currElem;
                // Update the length on longest subarray with max element AND
                longestSubArrSz = 1;
            } else if (currElem == maxElem) {
                // Current element is a max element
                // Update the length of either new subarray/running subarray with max element
                ++currMaxElemSubArrSz;
                // Update the length on longest subarray with max element AND
                longestSubArrSz = max(longestSubArrSz, currMaxElemSubArrSz);
            } else {
                // currElem < maxElem
                // Reset length of any contiguous maximum valued element subarray seen so far
                currMaxElemSubArrSz = 0;
            }
        }
        
        return longestSubArrSz;
    }
};
