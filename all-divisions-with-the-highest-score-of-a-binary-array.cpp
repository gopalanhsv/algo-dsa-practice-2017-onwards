// n => nums.size()
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    vector<int>
    maxScoreIndices(vector<int>& nums) {        
        // Array sum is sum of all 1's as array is binary
        auto arrSum = accumulate(nums.begin(), nums.end(), 0);
        
        auto arrSz = nums.size();
        auto maxDivisonScore = -1;
        vector<int> maxDivisonScoreIdxV;
        auto leftSubArrSum = 0;
        // Iterate over the array sequentially from L->R, dividing the 
        // array at all possible locations
        for (auto divIdx = 0; divIdx <= arrSz; ++divIdx) {
            
            // Left partition subarray range is [0, diviIdx - 1]
            // Sum of all elements in left partition
            if (divIdx - 1 >= 0) {
                leftSubArrSum += nums[divIdx - 1];
            }
            // Number of zeroes in left partition subarray
            auto nLeftSubArrSz = divIdx;
            auto nLeftSubArrZeros = nLeftSubArrSz - leftSubArrSum;

            // Right partition subarray range is [diviIdx, arrSz - 1]
            // Number of ones in right partition subarray
            auto nRightSubArrOnes = arrSum - leftSubArrSum;
            
            // Compute divison score at index 'divIdx'
            auto divScore = nLeftSubArrZeros + nRightSubArrOnes;
            
            // Update the max divison score and indices list if reqd
            if (divScore > maxDivisonScore) {
                maxDivisonScore = divScore;
                maxDivisonScoreIdxV = vector<int>({divIdx});
            } else if (divScore == maxDivisonScore) {
                maxDivisonScoreIdxV.emplace_back(divIdx);
            }
        }

        return maxDivisonScoreIdxV;
    }
};
