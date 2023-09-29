// n => nums.size()

// DP Approach
// Time complexity : O(n)
// Space complexity : O(n)

// DP Approach Space Optimized
// Time complexity : O(n)
// Space complexity : O(n)
class Solution {
public:
    long long
    countSubarrays(vector<int>& nums) {
        return countSubarraysDPBottomUpSpaceOptimized(nums);
        //return countSubarraysDPBottomUp(nums);
    }
    
private:
    
    long long
    countSubarraysDPBottomUp(vector<int>& nums) {
        // SE => Strictly increasing
        auto arrSz = nums.size();
        // dpTbl[i] is the number of SE subarrays terminating at index 'i'
        // which commenc either at index 'i' or to its left
        vector<long long> dpTbl(arrSz, 0);
        // Number of SE subarrays terminating at index-0 is 1 (first element subarray)
        dpTbl[0] = 1;
        // Iterate over each of the array indices from L->R sequentially
        for (auto i = 1; i < arrSz; ++i) {
            // Compute the number of SE subarrays ending at index 'i'
            
            // SE subarrays ending at index i =
            //  subarray [i, i] + all the SE subarrays which end at previous
            //  index 'i - 1' and get extended to current index 'i'
            // Subarray [i, i]
            dpTbl[i] = 1;
            if (nums[i] > nums[i - 1]) {
                // All SE subarrays terminating at 'i - 1' get extended to 'i'
                dpTbl[i] += dpTbl[i - 1];
            }
        }
        
        // Add up the SE subarray count terminating at each of the indices
        long long nSubArrays = 0;
        for (auto i = 0; i != arrSz; ++i) {
            nSubArrays += dpTbl[i];
        }
        return nSubArrays;
    }

    long long
    countSubarraysDPBottomUpSpaceOptimized(vector<int>& nums) {
        // SE => Strictly increasing
        auto arrSz = nums.size();
        // Tracks the total number of SE subarrays seen so far
        long long nTotalSESubArrays = 0;
        // Tracks the number of SE subarrays terminating at previous element
        // at index 'i - 1' while one is at current index 'i'
        long long nSESubArraysEndingAtPrevIdx = 0;
        
        // Number of SE subarrays terminating at index-0 is 1 (first element subarray)
        nSESubArraysEndingAtPrevIdx = 1;
        nTotalSESubArrays += nSESubArraysEndingAtPrevIdx;
        
        // Iterate over each of the array indices from L->R sequentially
        for (auto i = 1; i < arrSz; ++i) {
            // Compute the number of SE subarrays ending at current index 'i'
            long long nSESubArraysEndingAtCurrIdx = 0;
            // SE subarrays ending at index i =
            //  subarray [i, i] + all the SE subarrays which end at previous
            //  index 'i - 1' and get extended to current index 'i'
            // Subarray [i, i]
            nSESubArraysEndingAtCurrIdx = 1;
            if (nums[i] > nums[i - 1]) {
                // All SE subarrays terminating at 'i - 1' get extended to 'i'
                nSESubArraysEndingAtCurrIdx += nSESubArraysEndingAtPrevIdx;
            }
            
            nTotalSESubArrays += nSESubArraysEndingAtCurrIdx;
            
            // Current index 'i' becomes previous index for next iteration at index 'i + 1'
            nSESubArraysEndingAtPrevIdx = nSESubArraysEndingAtCurrIdx;
        }
        return nTotalSESubArrays;
    }
};
