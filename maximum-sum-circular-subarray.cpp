class Solution {
public:
    int
    maxSubarraySumCircular(vector<int>& nums) {
        // The subarray with the maximum sum can either lie:-
        // 1. Within the array 
        // 2. Split across the array ends without having the members at the 
        // middle portion of the array
        // The above 2 scenario reduce to :-
        // Case 1: Maximum subarray sum is base case of Kadane algorithm
        // Case 2: Maximum subarray sum can be found by finding the subarray
        // within the array with minimum sum; and subtracting/removing that
        // array from entire array -- remainder would be the split subarray
        // array with maximum sum
        
        // Kadane algorithm to get max subarray sum and min subarray sum
        int minArraySumAtIdx = nums[0];
        int maxArraySumAtIdx = nums[0];
        int maxSum = nums[0];
        int minSum = nums[0];
        int arraySum = nums[0];
        for (int i = 1; i != nums.size(); ++i) {
            auto & currElem = nums[i];
            minArraySumAtIdx = min(currElem, minArraySumAtIdx + currElem);
            minSum = min(minSum, minArraySumAtIdx);
            maxArraySumAtIdx = max(currElem, maxArraySumAtIdx + currElem);
            maxSum = max(maxSum, maxArraySumAtIdx);
            arraySum += currElem;
        }
        
        // Take the maximum of the case 1 and case 2 computed sums
        
        // If min subarray sum is the same as entire array sum, then 
        // case 2 will become null array and hence 0. In such cases,
        // the case 2 should be ignored
        if (minSum != arraySum) {
            maxSum = max(maxSum, arraySum - minSum);
        } else {
            maxSum = max(maxSum, minSum);
        }
        
        return maxSum;
    }
};
