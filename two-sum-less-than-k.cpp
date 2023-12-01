// n => nums.size()
// Time complexity : O(nlogn)
// Space complexity : O(logn)

class Solution {
public:
    int
    twoSumLessThanK(vector<int>& nums, int k) {
        int maxSum = numeric_limits<int>::min();

        // Problem is reduced to finding two distinct elements in array
        // s.t. their sum is l.t k and sum should be max
        // Sort the vector and use two pointers to get the max sum
        
        // Sort the vector
        sort(nums.begin(), nums.end());
            
        // Init two pointers at array extremities and move them towards each
        // other, based on thesum of the current elements pointed by them
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            long sum = nums[l] + nums[r];
            if (sum >= k) {
                // Look for smaller sum => Advance right pointer to left
                --r;
            } else {
                // Current sum fits the criteria
                maxSum = max((int)sum, maxSum);
                // Check for larger sums. Advance left pointer to increase sum
                ++l;
            }
        }
        
        return maxSum == numeric_limits<int>::min() ? -1 : maxSum;
    }
};
