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
            
            // Iterate over candidate leftmost cols of the hourglass
            for (auto leftMostCol = 0; leftMostCol < nc - 2; ++leftMostCol) {
                // Compute the row sum vals for hourglass with top
                // left cell at (topRowId, leftMostCol)
                auto topRowElemsSum =
                    topRowV[leftMostCol] + topRowV[leftMostCol + 1] + topRowV[leftMostCol + 2];
                auto midRowElemsSum = midRowV[leftMostCol + 1];
                auto bottomRowElemsSum =
                    bottomRowV[leftMostCol] + bottomRowV[leftMostCol + 1] + bottomRowV[leftMostCol + 2];
                // Hourglass sum
                auto currHrGlassSum = topRowElemsSum + midRowElemsSum + bottomRowElemsSum;
                maxSumVal = max(maxSumVal, currHrGlassSum);
            }
        }
        
        return maxSumVal;
    }
};
