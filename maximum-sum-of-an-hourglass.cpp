// r => num rows, c => nums cols
// Time complexity : O(nr x nc)
// Space complexity : O(1)

class Solution {
public:
    int
    maxSum(vector<vector<int>>& grid) {
        auto nr = grid.size();
        auto nc = grid[0].size();
        if (nr < 3 || nc < 3) {
            // Hourglass not possible in grid
            return 0;
        }
        
        int maxSumVal = 0;
        // Iterate over the top rows of the candidate hourglass sequentially
        for (auto topRowId = 0; topRowId < nr - 2; ++topRowId) {
            
            // Hour glass rows
            auto & topRowV = grid[topRowId];
            auto & midRowV = grid[topRowId + 1];
            auto & bottomRowV = grid[topRowId + 2];
            
            // Compute the row sum vals for hourglass with top left cell at (topRowId, 0)
            auto topRowElemsSum = topRowV[0] + topRowV[1] + topRowV[2];
            auto midRowElemsSum = midRowV[1];
            auto bottomRowElemsSum = bottomRowV[0] + bottomRowV[1] + bottomRowV[2];
            // Hourglass sum
            auto currHrGlassSum = topRowElemsSum + midRowElemsSum + bottomRowElemsSum;
            maxSumVal = max(maxSumVal, currHrGlassSum);
            
            // Iterate over candidate leftmost cols of the hourglass
            for (auto leftMostCol = 1; leftMostCol < nc - 2; ++leftMostCol) {
                // Compute the row sum vals for hourglass with top
                // left cell at (topRowId, leftMostCol + 2)
                topRowElemsSum += topRowV[leftMostCol + 2] - topRowV[leftMostCol - 1];
                midRowElemsSum = midRowV[leftMostCol + 1];
                bottomRowElemsSum += bottomRowV[leftMostCol + 2] - bottomRowV[leftMostCol - 1];
                // Hourglass sum
                currHrGlassSum = topRowElemsSum + midRowElemsSum + bottomRowElemsSum;
                maxSumVal = max(maxSumVal, currHrGlassSum);
            }
        }
        
        return maxSumVal;
    }
};
