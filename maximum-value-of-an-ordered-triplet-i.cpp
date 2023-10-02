// n => nums.size()
// Two pass
// Time complexity : O(n)
// Space complexity : O(n)

// One pass
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    long long
    maximumTripletValue(vector<int>& nums) {
        //return maximumTripletValueTwoPass(nums);
        return maximumTripletValueOnePass(nums);
    }
    
private:
    
    long long
    maximumTripletValueTwoPass(vector<int>& nums) {
        auto arrSz = nums.size();
        if (arrSz < 3) {
            // Base case of triplet absence
            return 0;
        }
        
        // Triplet value for indices i, j, k is (nums[i] - nums[j]) * nums[k], i < j < k
        // Max triplest value would the maximum of one of the two:-
        // 1. max value of diff (nums[i] - nums[j]) * max value of nums[k], i < j < k
        // max value of diff at any index 'j' is max value of (maxElem[0, j - 1] - nums[j])
        // max value of nums[k] at any index 'j' is maxElem[j + 1, ...]
        // OR
        // 2. min value of diff (nums[i] - nums[j]) * min value of nums[k], i < j < k
        // min value of diff at any index 'j' is min value of (minElem[0, j - 1] - nums[j])
        // min value of nums[k] at any index 'j' is minElem[j + 1, ...]

        // Iterate over the array from R->L sequentially
        // Compute the min and max values to the right i.e max and min values for nums[k]
        // maxToRightV[i] = max element value[i, arrSz - 1]
        vector<int> maxToRightV(arrSz);
        // minToRightV[i] = min element value[i, arrSz - 1]
        vector<int> minToRightV(arrSz);
        maxToRightV[arrSz - 1] = nums[arrSz - 1];
        minToRightV[arrSz - 1] = nums[arrSz - 1];
        for (auto k = arrSz - 2; k >= 2; --k) {
            maxToRightV[k] = max(maxToRightV[k + 1], nums[k]);
            minToRightV[k] = min(minToRightV[k + 1], nums[k]);
        }
        
        // Iterate over the array from L->R sequentially (middle element 'j')
        long long maxTripletVal = 0;
        long long maxDiff = numeric_limits<int>::min();
        long long minDiff = numeric_limits<int>::max();
        long long minElemToLeft = nums[0];
        long long maxElemToLeft = nums[0];
        for (auto j = 1; j < arrSz - 1; ++j) {
            // Compute max value of diff (nums[i] - nums[j]) seen so far
            maxDiff = max(maxElemToLeft - (long long)nums[j], maxDiff);
            // Compute min value of diff (nums[i] - nums[j]) seen so far
            minDiff = min(minElemToLeft - (long long)nums[j], minDiff);
            // Update max value of triplet
            maxTripletVal = max(maxTripletVal, maxDiff * maxToRightV[j + 1]);
            maxTripletVal = max(maxTripletVal, minDiff * minToRightV[j + 1]);
            // Update min and max element seen in [0, j]
            maxElemToLeft = max((long long)nums[j], maxElemToLeft);
            minElemToLeft = min((long long)nums[j], minElemToLeft);
        }
        
        return maxTripletVal;
    }
    
    long long
    maximumTripletValueOnePass(vector<int>& nums) {
        auto arrSz = nums.size();
        if (arrSz < 3) {
            // Base case of triplet absence
            return 0;
        }
        
        // Triplet value for indices i, j, k is (nums[i] - nums[j]) * nums[k], i < j < k
        // Max triplest value would the maximum of one of the two:-
        // 1. max value of diff (nums[i] - nums[j]) * max value of nums[k], i < j < k
        // max value of diff at any index 'j' is max value of (maxElem[0, j - 1] - nums[j])
        // max value of nums[k] at any index 'j' is maxElem[j + 1, ...]
        // OR
        // 2. min value of diff (nums[i] - nums[j]) * min value of nums[k], i < j < k
        // min value of diff at any index 'j' is min value of (minElem[0, j - 1] - nums[j])
        // min value of nums[k] at any index 'j' is minElem[j + 1, ...]

        // Instead of multiplying by max value of nums[k] i.e maxElem[j + 1, arrSz - 1]
        // in case(1) above, one can multiply max value of diff at index j
        // i.e. max value of diff over [0, j] by nums[j + 1] for each of the possible mid indices
        // and take the max of all such computed triplet values
        // Same applies for case (2) too.

        // Iterate over the array from L->R sequentially (middle element 'j')
        long long maxTripletVal = 0;
        long long maxDiff = numeric_limits<int>::min();
        long long minDiff = numeric_limits<int>::max();
        long long minElemToLeft = nums[0];
        long long maxElemToLeft = nums[0];
        for (auto j = 1; j < arrSz - 1; ++j) {
            // Compute max value of diff (nums[i] - nums[j]) seen so far
            maxDiff = max(maxElemToLeft - (long long)nums[j], maxDiff);
            // Compute min value of diff (nums[i] - nums[j]) seen so far
            minDiff = min(minElemToLeft - (long long)nums[j], minDiff);
            // Update max value of triplet seen so far
            maxTripletVal = max(maxTripletVal, maxDiff * nums[j + 1]);
            maxTripletVal = max(maxTripletVal, minDiff * nums[j + 1]);
            // Update min and max element seen in [0, j]
            maxElemToLeft = max((long long)nums[j], maxElemToLeft);
            minElemToLeft = min((long long)nums[j], minElemToLeft);
        }
        
        return maxTripletVal;
    }
};
