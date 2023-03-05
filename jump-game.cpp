class Solution {
public:
    bool
    canJump(vector<int>& nums) {
        if (nums.size() < 2) {
            // Base case of empty/single element array
            return true;
        }
        
        int arrSz = nums.size();
        // Tracks the leftmost from where it is possible to reach last index
        int leftmostIdx = arrSz - 1;
        // Iterate over each of the index locations from R to L sequentially
        for (int currIdx = arrSz - 2; currIdx >= 0; --currIdx) {
            // Compute the position of the rightmost allowable array index
            // which can be reached via jumping from current position
            int maxReachableIdxToRight = currIdx + nums[currIdx];
            if (maxReachableIdxToRight >= leftmostIdx) {
                // Possible to reach the array index from current location
                leftmostIdx = currIdx;
            }
        }
        
        // Return true if possible to reach array end from array start
        return 0 == leftmostIdx;
    }
};
