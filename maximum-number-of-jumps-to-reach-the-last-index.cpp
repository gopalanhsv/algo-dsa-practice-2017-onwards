// n => nums.size()
// Time complexity : O(n^2)
// Space complexity : O(n)

class Solution {
public:
    int
    maximumJumps(vector<int>& nums, int target) {
        int arrSz = nums.size();
        // Need to adopt DP approach here as all candidate indices for
        // reaching a particular index have to be explored
        // maxJumpsTbl[i] is the max number of jumps to reach index 'i' from index '0'
        vector<int> maxJumpsTbl(arrSz, -1);
        // Initialize : start position commencement at 0 index
        maxJumpsTbl[0] = 0;
        // Iterate over each of the index locations sequentially
        for (auto currIdx = 1; currIdx < arrSz; ++currIdx) {
            // Init max jumps to reach current location as 'unreachable'
            auto maxJumps = -1;
            // Iterate over each of the candidate locations for
            // reaching the current location
            for (auto prevIdx = 0; prevIdx < currIdx; ++prevIdx) {
                if ((maxJumpsTbl[prevIdx] != -1) &&
                    (abs(nums[currIdx] - nums[prevIdx]) <= target)) {
                    
                    // Possible to reach current location from candidate
                    // location 'prevIdx' in one jump AND
                    // Candidate location 'prevIdx' is also reachable from '0'
                    // Update the max number of jumps to reach current location
                    maxJumps = max(maxJumps, 1 + maxJumpsTbl[prevIdx]);
                }
            }

            maxJumpsTbl[currIdx] = maxJumps;
        }
        
        return maxJumpsTbl[arrSz - 1];
    }
};
