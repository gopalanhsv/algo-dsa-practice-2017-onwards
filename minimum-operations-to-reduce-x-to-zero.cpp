// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    int
    minOperations(vector<int>& nums, int x) {
        // The problem requires the determination of the minimum number of elements from the beginning
        // and end of the array which add upto 'x' => finding the minimum number of prefix & suffix
        // elements which add upto 'x'
        // Now Array sum = prefix elems sum + mid contiguous subarray elems sum + suffix elems sum
        // => mid contiguous subarray elems sum = 
        //    array sum - (sum of prefix & suffix elems) = array sum - x
        // So the problem reduces to finding the max size contiguous subarray with a sum of 'array sum' - x
        
        // The max size subarray is easily obtained using a variable sized sliding window
        
        // Add up the array elements and compute the target sum for subarray
        int arrSz = nums.size();
        int arrSum = accumulate(nums.begin(), nums.end(), 0);
        if (arrSum == x) {
            // Base case of all elements adding upto required sum => entire array is to purged
            return arrSz;
        }
        int tSum = arrSum - x;
        
        // Determin the maximal length subarray adding up to target sum
        auto sWinStart = 0;
        auto maxSubArrLen = 0;
        auto subArrSum = 0;
        // Subarray consists of all elements in the closed range [sWinStart, sWinEnd]
        // Add elements to the right of subarray/window sequentially from the original array
        for (auto sWinEnd = 0; sWinEnd < arrSz; ++sWinEnd) {
            subArrSum += nums[sWinEnd];
            
            // If subarray sum exceeds target sum, shrink it from left
            // till it drops to at/below the target sum 
            while ((sWinStart < arrSz) && (subArrSum > tSum)) {
                // Shrink the subarray/window from the left
                subArrSum -= nums[sWinStart++];
            }
            
            if (subArrSum == tSum) {
                // Subarray adds up to target sum. Update the max subarray size.
                maxSubArrLen = max(maxSubArrLen, sWinEnd - sWinStart + 1);
            }
        }

        return (maxSubArrLen == 0) ? -1 : arrSz - maxSubArrLen;
    }
};
