class Solution {
public:
    int
    threeSumClosest(vector<int>& nums, int target) {
        // Sort the array in ascending order
        sort(nums.begin(), nums.end());
        
        // Need x + y + z s.t. abs((x + y + z) - target) is minimum
        // => abs((y + z) - (target - x)) is minimum
        // => Problem reduces to finding sum of two numbers y & z in subarray to
        // right of x, s.t. their sum is closest to 'target - x' 
        // Iterate though the sorted array sequentially from L->R and fix the 'x'
        // => fixing 'target - x'. Then use two pointers on the remainder of the  array
        // to the right of 'x' to find 'x' & 'y' s.t. their value of
        // abs((x + y + z) - target) is minimum
        int arrSz = nums.size();
        int closestSum;
        int minDiff = numeric_limits<int>::max();
        for (int i = 0; i < arrSz - 2; ++i) {
            int targetSum = target - nums[i];
            // Find two sum of numbers in subarray nums[i, arrSz - 1] closest to targetSum
            int lo = i + 1;
            int hi = arrSz - 1;
            while (lo < hi) {
                int twoSum = nums[lo] + nums[hi];
                int diff = abs(twoSum - targetSum);
                if (diff <= minDiff) {
                    closestSum = nums[i] + twoSum;
                    diff = minDiff;
                }
                
                if (twoSum == targetSum) {
                    // Closest sum to target found
                    break;
                } else if (twoSum < targetSum) {
                    ++lo;
                } else { // twoSum > targetSum
                    --hi;
                }
            }
        }
        
        return closestSum;
    }
};
