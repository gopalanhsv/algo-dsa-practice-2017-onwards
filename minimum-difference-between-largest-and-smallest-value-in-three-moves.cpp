// n => nums.size()
// Time complexity : O(nlogn)
// Space complexity : O(logn)

class Solution {
public:
    int
    minDifference(vector<int>& nums) {
        
        int arrSz = nums.size();
        if (nums.size() < 4) {
            // Base case of array having less than 4 elements
            // All can be made equal in 3 or less moves
            return 0;
        }
        
        // Sort the elements
        sort(nums.begin(), nums.end());
        
#if 0
        // Find the max and min
        int maxElem = nums[arrSz - 1];
        int minElem = nums[0];
        
        // Idea is to minimize the difference between the max and min element
        // post the 3 moves. Minimization of difference between the max
        // and minimum element can be done in one of the following 4 ways
        // in a greedy fashion
        
        // Option 1
        // Make smallest 3 elements (indices 0, 1, 2) same as 4th element(index 3)
        // Max element stays same while min element is at location index 3
        int diff1 = maxElem - nums[min(3, arrSz - 1)];
        
        // Option 2
        // Make largest 3 elements (indices n - 3, n - 2, n - 1) same as 4th last 
        // element(index n - 4)
        // Min element stays same while max element is at location index n - 4
        int diff2 = nums[max(0, arrSz - 4)] - minElem;
        
        // Option 3
        // Make smallest 2 elements (indices 0, 1) same as 3rd element(index 2)
        // Make largest element (indices n - 1) same as 2nd last element(index n - 2)
        int diff3 = nums[max(0, arrSz - 2)] - nums[min(2, arrSz - 1)];
        
        // Option 4
        // Make smallest element (indices 0) same as 2nd element(index 1)
        // Make largest 2 elements (indices n -2 , n - 1) same as 3rd last element(index n - 3)
        int diff4 = nums[max(0, arrSz - 3)] - nums[min(1, arrSz - 1)];
 
        return min(min(diff1, diff2), min(diff3, diff4));
     
#else
      
        // Above code can be rewritten in loop form
        int minDiff = numeric_limits<int>::max();
        for (int i = 0; i <= 3; ++i) {
            int maxMinDiff = nums[max(0, arrSz - 4 + i)] - nums[min(i, arrSz - 1)];
            minDiff = min(minDiff, maxMinDiff);
        }
        
#endif

        return minDiff;
    }
};
