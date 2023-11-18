// n => nums.size()
// Time complexity : O(nlogn)
// Space complexity : O(logn)

class Solution {
public:
    int
    maxFrequency(vector<int>& nums, int k) {
        
        // Sort the array so that numbers with the minimum
        // difference are lined up next to each other
        sort(nums.begin(), nums.end());
        
        int winStart = 0;
        int arrSz = nums.size();
        
        // Apply increment operations to a series of consecutive elements to make each
        // identical to the maximum element of the series; which leads to max element in
        // the series having a frequency count identical to the number of series elements.
        
        // So the problem reduces to finding the longest contiguous subarray of elements
        // s.t. the number of increment operations to make all elements in the subarray
        // equal (i.e the maximum subarray element) does not exceed 'k'.
        
        // The candidate series of consecutive elements is selected using a variable sized
        // sliding window on the sorted array elements

        // Invariant : Maintain window s.t. the number of increment ops to make all 
        // elements in the subarray window [winStart, winEnd] identical to nums[winEnd]
        // is at most 'k'
        int maxWinSize = 1;
        long nOpsForIdenticalElemsInWindow = 0;
        // Increment window from right by one element in each iteration
        for (int winEnd = 1; winEnd < arrSz; ++winEnd) {
            auto currElem = nums[winEnd];
            int winSize = winEnd - winStart + 1;
            if (winSize > 1) {
                auto prevElem = nums[winEnd - 1];
                nOpsForIdenticalElemsInWindow += ((long)(currElem - prevElem) * (winSize - 1));
                while (nOpsForIdenticalElemsInWindow > k) {
                    // Shrink window from left s.t the number of increment ops to make all 
                    // elements in the window [winStart, winEnd] identical to nums[winEnd]
                    // is at most 'k'
                    nOpsForIdenticalElemsInWindow -= (currElem - nums[winStart]);
                    ++winStart;
                    --winSize;
                }
                maxWinSize = max(maxWinSize, winSize);
            }
        }
        
        return maxWinSize;
    }
};
