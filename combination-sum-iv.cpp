// n => nums.size(); t => target
// Time complexity : O(nT)
// Space complexity : O(T)

class Solution {
public:

    int
    combinationSum4(vector<int>& nums, int target) {
        // NOTE:- This is just a variant of coin change problem.
        
        // Use top-down/bottom-up DP to determine the number of combinations
        // using 'nums' which add upto the given 'target'
        return combinationSum4TopDownMemoization(nums, target);
        return combinationSum4BottomUpDP(nums, target);
    }
    
private:

    int
    combinationSum4BottomUpDP(vector<int>& nums, int target) {
        
        // dpTbl[x] represents the possible number of combinations using numbers
        // in 'nums' which add upto target 'x'. Using 'unsigned long long' to
        // avoid integer overflow while computing for some of the intermediate
        // targets between 0 and 'target' 
        vector<unsigned long long> dpTbl(target + 1, 0);
        
        // Sort the numbers in ascending order. This allows to halt the computation
        // of number of combinations for intermediate targets 'x' in [0, target];
        // whenever a number in sorted array exceeds the intermediate target 'x'
        // NOTE : Problem can be done without sorting step too
        sort(nums.begin(), nums.end());
        
        // Number of combinations for target '0' is nil as 'nums' array has +ve ints
        dpTbl[0] = 0;
        // Iterate over each possible target sum incrementally
        for (int x = 1; x <= target; ++x) {
            // Compute the number of combinations for each of the intermediate targets
            // from '1' to 'target' sequentially which can be build using 'nums' contents
            // Iterate over the elements in 'nums' array in ascending order
            for (auto num : nums) {
                // Attempt to sum up to intermediate target 'x' using current number
                if (num > x) {
                    // Current number and succeeding numbers in 'nums' exceed target 'x'
                    // => they cannot be used to combo sum upto 'x'
                    break;
                } else if (num < x) {
                    // Use current number 'x' and the remainder 'x - num' to build target 'x'
                    dpTbl[x] += dpTbl[x - num];
                } else {
                    // Only current number can be used once for building target 'x'
                    dpTbl[x] += 1;
                }
            }
        }
        
        return dpTbl[target];
    }
    
    int
    combinationSumViaMemoizationRec(vector<int>& nums, int target) {
        
        if (_memoTbl[target] != -1) {
            // Number of combinations which add upto 'target' has been precomputed earlier
            return _memoTbl[target];
        }
        
        // Coompute number of combinations which add upto 'target'
        int nCombinations = 0;
        // Iterate sequentially over each number of array 'nums'
        for (auto & num : nums) {
            // Attempt to form a combination adding upto 'target' using 'num'
            if (target > num) {
                // Number of combinations using the current number 'num' adding upto 'target' will
                // be same as the number of combinations which add upto the remainder 'target - num'
                // Increment number of combinations by the computed amount
                nCombinations +=
                    combinationSumViaMemoizationRec(nums, target - num);
            } else if (target == num) {
                // Number of combinations using the current number 'num' would be 1
                nCombinations += 1;
            }
        }

        // Update memo table with the computed number of combinations for 'target'
        _memoTbl[target] = nCombinations;

        return _memoTbl[target];
    }
    
    int
    combinationSum4TopDownMemoization(vector<int>& nums, int target) {
        // Initialize
        _memoTbl.resize(target + 1, -1);
        // Number of combinations which add upto 0 is nil
        _memoTbl[0] = 0;
        
        // Use top down DP to determine the number of combinations using 'nums'
        // which add upto the given target
        return combinationSumViaMemoizationRec(nums, target);
    }
    
    // Data members
    
    // _memoTbl[x] is the number of combinations which add upto the target 'x'
    // using the numbers in 'nums'; 
    vector<int> _memoTbl;
};
