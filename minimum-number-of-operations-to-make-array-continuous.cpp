// n => nums.size()

// Binary search Approach
// Time complexity : O(nlogn)
// Space complexity : O(n)

// Sliding Window Approach
// Time complexity : O(n)
// Space complexity : O(n)
class Solution {
public:
    int
    minOperations(vector<int>& nums) {
        if (nums.size() <= 1) {
            // Base case of empty/single element array requires nil ops
            return 0;
        }
        
        // Post all operations, all elements should be unique & 
        // arrMax - arrMin = arrSz - 1 => arrMax = arrMin + arrSz - 1,
        // the array will consists of all elements in the range [arrMax, arrMin]
        // So the problem reduces to doing the min number of replacements s.t. the
        // array post replacements satisfies the above condition.

        // Max number of replacements would be all array elements getting replaced
        // which is a non-optimal option
        // Other option is to select choose each unique element of the array as
        // the min element/arrMin and determine the number of replacements required
        // to transform the array to [arrMin, arrMin + arrSz - 1]
        //return minOperationsViaBinarySearch(nums);
        return minOperationsViaSlidingWindow(nums);
    }
    
private:

    int
    minOperationsViaBinarySearch(vector<int>& nums) {

        // Choose each unique element of the array as the min element/arrMin and
        // determine the number of replacements required to transform the array to
        // have elements in the range [arrMin, arrMin + arrSz - 1]. Select the
        // iteration which results in min replacements
        
        // Sort the array and modify it to have only unique elements
        set<int> sortedUniqueSet(nums.begin(), nums.end());
        vector<int> arrV(sortedUniqueSet.begin(), sortedUniqueSet.end());
        
        // Tracks the required continuous array size and min replacements
        // required in original array for the same
        auto reqdArrSz = nums.size();
        auto minReplacements = (int)reqdArrSz;
        // Iterate over the sorted+unique array from L->R
        for (auto i = 0; i != arrV.size(); ++i) {
            // Select current element as the minimum element for new continuous array
            auto & arrMin = arrV[i];
            // Max element for continuous array with current element as minimum
            auto arrMax = arrMin + reqdArrSz - 1;
            // Compute index location of insertion for the above maximum element in
            // current array via binary search
            auto maxPos = upper_bound(arrV.begin(), arrV.end(), arrMax) - arrV.begin();
            // Number of unique elements already available for the continuous array [arrMin, arrMax]
            auto nUniqueAvailable = maxPos - i;
            // Num replacements required in original array to get continuous array [arrMin, arrMax]
            auto nReplacements = reqdArrSz - nUniqueAvailable;
            minReplacements = min(minReplacements, (int)nReplacements);
        }
        
        return minReplacements;
    }
    
    int
    minOperationsViaSlidingWindow(vector<int>& nums) {

        // Choose each unique element of the array as the min element/arrMin and
        // determine the number of replacements required to transform the array to
        // have elements in the range [arrMin, arrMin + arrSz - 1]. Select the
        // iteration which results in min replacements
        
        // Sort the array and modify it to have only unique elements
        set<int> sortedUniqueSet(nums.begin(), nums.end());
        vector<int> arrV(sortedUniqueSet.begin(), sortedUniqueSet.end());
        
        // Tracks the required continuous array size and min replacements
        // required in original array for the same
        auto reqdArrSz = nums.size();
        auto minReplacements = (int)reqdArrSz;
        // Window [minPos, maxPos) represents the set of unique elements which form the
        // continuous array from 'nums' imput with min element as arrV[minPos]
        int maxPos = 0;
        // Iterate over the sorted+unique array from L->R
        for (auto minPos = 0; minPos != arrV.size(); ++minPos) {
            // Select current element as the minimum element for new continuous array
            auto & arrMin = arrV[minPos];
            // Max element for continuous array with current element as minimum
            auto arrMax = arrMin + reqdArrSz - 1;
            // Determine the end location of updated window of unique elements
            // in input 'nums' array forming the continuous array i.e. Compute index
            // location of insertion for the above maximum element in current array
            while ((maxPos < arrV.size()) && (arrV[maxPos] <= arrMax)) {
                ++maxPos;
            }
            // Number of unique elements already available for the continuous array [arrMin, arrMax]
            auto nUniqueAvailable = maxPos - minPos;
            // Num replacements required in original array to get continuous array [arrMin, arrMax]
            auto nReplacements = reqdArrSz - nUniqueAvailable;
            minReplacements = min(minReplacements, (int)nReplacements);
        }
        
        return minReplacements;
    }
};
