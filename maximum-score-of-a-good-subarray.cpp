// n => nums.size()
// Greedy Approach
// Time complexity : O(n)
// Space complexity :O(1)

class Solution {
public:
    int
    maximumScore(vector<int>& nums, int k) {
        return maxScoreViaGreedyApproach(nums, k);    
    }
    
private:

    int
    maxScoreViaGreedyApproach(vector<int>& nums, int k) {

        auto arrSz = nums.size();
        if ((k >= arrSz) || (k < 0)) {
            // Base case of 'k' beyond array bounds => no subarray possible
            return 0;
        }
        
        // Max score between any two indices 'lo' & 'hi' is determined solely by the min
        // value of nums over the range [lo, hi] and the distance between the indices
        
        // Index 'k' has to present in the good subarray always
        
        // Have two pointers 'lo' & 'hi' representing the range indices of good subarray
        // Init the two pointers to be at index 'k' and move them away from each other
        // on step at a time.
        // At any time instance after computing score of subarray nums[lo, hi]; adopt the
        // greedy approach of fixing/not advancing the pointer (lo/hi) leading to smaller
        // value (as it may reduce the min value of nums[lo, hi]); and advance the pointer
        // leading to larger value away from index 'k' (as it wont reduce min value of
        // nums[lo, hi]) as expanding subarray size [lo, hi] leads to a larger score
        int lo = k, hi = k;
        auto subArrMin = nums[k];
        auto maxScore = subArrMin * (hi - lo + 1);
        while ((lo > 0) || (hi < arrSz - 1)) {
            
            // Advance subarray ends towards either left/right one step
            auto candidateLo = lo - 1;
            auto candidateHi = hi + 1;
            
            // Value of subarray at candidate extremities
            auto loVal = (candidateLo >= 0) ? nums[candidateLo] : 0;
            auto hiVal = (candidateHi < arrSz) ? nums[candidateHi] : 0;
            if (hiVal < loVal) {
                // Expanding subarray towards right may lead to a lower value of
                // min(nums[lo, hi]) leading to a lower score
                // Employ greedy strategy of expanding in the direction of 'lo'
                lo = candidateLo;
                subArrMin = min(nums[lo], subArrMin);
            } else {
                // Expanding subarray towards left may lead to a lower value of
                // min(nums[lo, hi]) leading to a lower score
                // Employ greedy strategy of expanding in the direction of 'hi'
                hi = candidateHi;
                subArrMin = min(nums[hi], subArrMin);
            }
            
            // Compute the score of the new good subarray & update max score
            auto newScore = (hi - lo + 1) * subArrMin;
            maxScore = max(maxScore, newScore);
        }
        return maxScore; 
    }
};
