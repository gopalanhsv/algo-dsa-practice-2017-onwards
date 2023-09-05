// n => nums.size()
// Time complexity : O(nlogn)
// Space complexity : O(n - x)

class Solution {
public:
    int
    minAbsoluteDifference(vector<int>& nums, int x) {
        int arrSz = nums.size();
        if (arrSz < x) {
            // Error as the distance between any 2 array indices will be l.t. 'x' apart
            return -1;
        }

        // Since the two numbers choosen must be at least 'x' indices apart, the problem is
        // symmetric w.r.t indices, i.e for each index 'pos', examine the numbers which are
        // located at indices [0, pos - x] for the closest number to nums[pos] so that the
        // difference between the two numbers is minimized. We do not have to look at numbers
        // in the range [pos + x, ..] at the problem is symmetric
        
        // Use a sliding window to exclude numbers which are l.t 'x' indices apart
        // Iterate over each number from L->R sequentially
        int minAbsDiff = numeric_limits<int>::max();
        set<int> candidateNums;
        for (int pos = x; pos < arrSz; ++pos) {
            // Add nearest located number which should be considered (outside the 'x - 1' sized window)
            auto & nearestNum = nums[pos - x];
            candidateNums.insert(nearestNum);
            
            auto & currNum = nums[pos];
            // Search for the closest numbers to current number via binary search amongst candidates
            auto iter = candidateNums.upper_bound(currNum);
            if (iter != candidateNums.end()) {
                // Closest number g.t current number
                auto closestNumHi = *iter;
                minAbsDiff = min(minAbsDiff, closestNumHi - currNum);
            }
            if (iter != candidateNums.begin()) {
                // Closest number l.e current number
                auto closestNumLo = *(--iter);
                minAbsDiff = min(minAbsDiff, currNum - closestNumLo);
            }
        }
        
        return minAbsDiff;
    }
};
