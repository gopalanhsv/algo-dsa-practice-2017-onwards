// Time complexity : O(log(array size))
// Space complexity : O(1)

class Solution {
public:
    int
    maximumCount(vector<int>& nums) {
        int arrSz = nums.size();
        if (0 == arrSz) {
            // No elements
            return 0;
        }
        if (1 == arrSz) {
            // Single element array
            return (nums[0] == 0) ? 0 : 1;
        }
        
        // Array is sorted in non-decreasing order
        // Determine the location of leftmost +ve integer via binary search
        int lo = 0; int hi = arrSz - 1;
        while (lo < hi) {
            int mid = lo + ((hi - lo) >> 1);
            if (nums[mid] > 0) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        int leftMostPositiveIdx = (nums[lo] > 0) ? lo : arrSz;
        int nPositiveNums = arrSz - 1 - leftMostPositiveIdx + 1;
        
        // Array is sorted in non-decreasing order
        // Determine the location of rightmost -ve integer via binary search
        lo = 0; hi = arrSz - 1;
        while (lo < hi) {
            int mid = lo + ((hi - lo) >> 1) + 1;
            if (nums[mid] < 0) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        int rightMostNegativeIdx = (nums[lo] < 0) ? lo : -1;
        int nNegativeNums = rightMostNegativeIdx + 1;
        
        return max(nNegativeNums, nPositiveNums);
    }
};
