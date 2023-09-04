// n = nums.size(), m = max val in nums
// Time complexity : O(nlogm)
// Space complexity : O(1)
class Solution {
public:
    int
    minimumSize(vector<int>& nums, int maxOperations) {
        
        // Since penalty is the max number of balls in a bag, one needs
        // to find the minimum possible bag size (in terms of the number balls which
        // it can hold) which is able to accomodate the balls at each array location of the
        // array post splitting/dividing the original bag at every location within
        // the specified number of operations
        
        // Since each bag must have +ve number of balls, min possible penalty/bag size is 1
        int minBagSize = 1;
        // Max bag size would be the array location/bag with max balls
        int maxBagSize = *max_element(nums.begin(), nums.end());
        
        // Exec a binary search in the range [minBagSize, maxBagSize] for the minimum
        // possible penalty/bag size which will end up holding all balls within at most
        // 'maxOperations' splits across the entire arrayi
        int lo = minBagSize;
        int hi = maxBagSize;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (possibleToHoldBallsPostSplit(nums, mid, maxOperations)) {
                // 'mid' will now be an upper limit on the penalty/bag size
                hi = mid;
            } else {
                // 'mid' bag size/penalty is insufficient to hold all balls. Need to
                // look in the upper half of the range for a suitable penalty/bag size
                lo = mid + 1;
            }
        }
        
        // Search range converges to a single element [lo, lo] in a pincer like movement
        return lo;
    }
    
private:
    
    bool
    possibleToHoldBallsPostSplit(vector<int>& bagsV, int maxBagSize, int maxSplits) {
        // Iterate over each bag in sequence
        int totalDivisons = 0;
        for (auto & nBalls : bagsV) {
            // Determine number of divisons required to split the current bag with
            // 'nBalls' into bags with given max size/penalty 
            auto nDivisionsReqdForBag = ceil(double(nBalls) / maxBagSize) - 1;
            totalDivisons += nDivisionsReqdForBag;
        }
        
        // Return true if the total number of operations/divisons are l.e the
        // max allowed, false otherwise
        return (totalDivisons <= maxSplits);
    }
};
