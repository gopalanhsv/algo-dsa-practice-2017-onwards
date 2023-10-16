// n => nums.size()

// Time complexity : O(n ^ 2)
// Space complexity : O(n)

// Space optimized
// Time complexity : O(n ^ 2)
// Space complexity : O(1)


class Solution {
public:
    int
    triangularSum(vector<int>& nums) {
        // Employ simulation 
        return triangularSumSpaceOptimizedSimulation(nums);
    }
    
private:

    int
    triangularSumSimulation(vector<int>& nums) {
        // Tracks the decrementing array size in each iteration
        auto arrSz = nums.size() - 1;
        // New array to hold original array values to prevent old vals being clobbered
        vector<int> newNumsV(nums);
        // Decrement the array size being considered in each iteration by 1
        for (auto newArrSz = nums.size() - 1; newArrSz > 0; --newArrSz) {
            // Compute the values for all of new array entries sequentially
            // from L->R using the values from previous iteration
            for (auto i = 0; i < newArrSz; ++i) {
                newNumsV[i] = (newNumsV[i] + newNumsV[i + 1]) % 10;
            }
        }
        
        return newNumsV[0];
    }
    
    int
    triangularSumSpaceOptimizedSimulation(vector<int>& nums) {
        // Tracks the decrementing array size in each iteration
        auto arrSz = nums.size() - 1;
        // Decrement the array size being considered in each iteration by 1
        for (auto newArrSz = nums.size() - 1; newArrSz > 0; --newArrSz) {
            // Compute the values for all of new array entries sequentially
            // from L->R using the values from previous iteration
            for (auto i = 0; i < newArrSz; ++i) {
                nums[i] = (nums[i] + nums[i + 1]) % 10;
            }
        }
        
        return nums[0];
    }
};
