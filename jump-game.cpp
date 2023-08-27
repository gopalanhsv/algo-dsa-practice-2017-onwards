// n => arr.size();
// Time complexity : O(n)
// Space complexity : O(1)

class Solution {
public:
    bool
    canJump(vector<int>& nums) {
        if (nums.size() < 2) {
            // Base case of empty/single element array
            return true;
        }
        
        int arrSz = nums.size();
        // Tracks the leftmost index from where it is possible to reach last index
        int leftmostIdx = arrSz - 1;
        // Iterate over array index locations from R to L sequentially
        for (auto currIdx = arrSz - 2; currIdx >= 0; --currIdx) {
            // Determine rightmost array index reachable from current position
            int rightmostReachableIdx = currIdx + nums[currIdx];
            if (rightmostReachableIdx >= leftmostIdx) {
                // Possible to reach the last index from current location
                leftmostIdx = currIdx;
            }
        }
        
        // Return true if possible to reach array end from array start
        return 0 == leftmostIdx;
    }
};
