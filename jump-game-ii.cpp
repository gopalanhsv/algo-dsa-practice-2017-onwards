class Solution {
public:
    int
    jump(vector<int>& nums) {

        
        int arrSz = nums.size();
        if (arrSz < 2) {
            // Base case of empty/single element array
            return 0;
        }
        
        // Tracks the farthest reachable index to the right
        // from start location at any point in time
        int nJumps = 0;
        int nxtJumpClosestIdxToRight = 0;
        int nxtJumpFarthestIdxToRight = 0;
        
        while (nxtJumpFarthestIdxToRight != arrSz - 1) {
            
            int minNextJumpIdxToRight = nxtJumpFarthestIdxToRight + 1;
            int maxNextJumpIdxToRight = nxtJumpFarthestIdxToRight + 1;
            
            for (int currIdx = nxtJumpClosestIdxToRight; 
                 currIdx <= nxtJumpFarthestIdxToRight;
                 ++currIdx) {
            
                maxNextJumpIdxToRight
                    = max(maxNextJumpIdxToRight, currIdx + nums[currIdx]);
            }
            
            ++nJumps;
            nxtJumpClosestIdxToRight = 
                min(arrSz - 1, minNextJumpIdxToRight);
            nxtJumpFarthestIdxToRight = 
                min(arrSz - 1, maxNextJumpIdxToRight);
            
        }
        
        return nJumps;
    }
};
