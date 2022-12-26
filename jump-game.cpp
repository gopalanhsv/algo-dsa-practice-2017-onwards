class Solution {
public:
    bool
    canJump(vector<int>& nums) {
        if (nums.size() < 2) {
            // Base case of empty/single element array
            return true;
        }
        
        int arrSz = nums.size();
        // Tracks the nearest index to right from current position
        // fromt where it is possible to reach last index
        int closestReachableRightIdx = arrSz - 1;
        // Iterate over each of the index locations from R to L sequentially
        for (int currIdx = arrSz - 2; currIdx >= 0; --currIdx) {
            // Compute the position of the maximum allowable array index
            // which can be reached via jumping from current position
            int maxReachableIdxToRight = currIdx + nums[currIdx];
            if (maxReachableIdxToRight >= closestReachableRightIdx) {
                // Possible to reach the array index from current location
                closestReachableRightIdx = currIdx;
            }
        }
        
        // Return true if possible to reach array end from array start
        return 0 == closestReachableRightIdx;
    }
};
