// nr => num rows, nc => num cols
// Dp Approach
// Time complexity : O(nr x (nc)^ 2)
// Space complexity : O(nr x nc)

// Dp Approach space optimized
// Time complexity : O(nr x (nc)^ 2)
// Space complexity : O(nc)

class Solution {
public:
    int
    minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        //return minPathCostViaDP(grid, moveCost);
        return minPathCostViaDPSpaceOptimized(grid, moveCost);
    }
    
private:
    int
    minPathCostViaDP(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        // Num grid rows/cols and cells
        int nr = grid.size();
        int nc = grid[0].size();
        
        // minPathCostTbl[r][c] is the minimum path cost to reach
        // cell(r, c) from any cell in top row. Initialized to +infinity
        vector<vector<long> > minPathCostTbl(
            nr, vector<long>(nc, numeric_limits<long>::max()));
        // For 1st row, init the cost to hit reach the top of each cell
        // (note :- the cell is not included in path here)
        for (auto c = 0; c != nc; ++c) {
            minPathCostTbl[0][c] = 0;
        }
        
        // Iterate over each row sequentially from the 1st to last but one row
        for (auto currRow = 0; currRow < nr - 1; ++currRow) { 
            auto nextRow = currRow + 1;
            // Iterate over each cell/column in the current row from L->R sequentially
            for (auto currCol = 0; currCol != nc; ++currCol) {
                // Update the min path cost terminating at the current cell to
                // include the cell value
                auto & currCellVal = grid[currRow][currCol];
                minPathCostTbl[currRow][currCol] += currCellVal;

                // Compute the min path cost to reach the cell top for each cell/column
                // in the next row from the current cell
                for (auto nextRowCol = 0; nextRowCol != nc; ++nextRowCol) {
                    auto & hopCost = moveCost[currCellVal][nextRowCol];
                    
                    minPathCostTbl[nextRow][nextRowCol]
                        = min(minPathCostTbl[nextRow][nextRowCol],
                              hopCost + minPathCostTbl[currRow][currCol]);
                }
            }
        }
        
        // Tracks the min path cost to reach any cell from top row
        auto minPathCostToLastRow = numeric_limits<long>::max();
        auto lastRow = nr - 1;
        // Iterate over each cell/col in the last row
        for (auto c = 0; c != nc; ++c) {
            // Update the min path cost terminating at current last row cell to
            // include the cell value
            auto & currCellVal = grid[lastRow][c];
            minPathCostTbl[lastRow][c] += currCellVal;
            // Update the min path cost over all paths
            minPathCostToLastRow = min(minPathCostToLastRow, minPathCostTbl[lastRow][c]);
        }

        return minPathCostToLastRow;
    }
    
    int
    minPathCostViaDPSpaceOptimized(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        // Num grid rows/cols and cells
        int nr = grid.size();
        int nc = grid[0].size();
        
        // minPathCostTbl[r][c] is the minimum path cost to reach
        // cell(r, c) from any cell in top row. Initialized to +infinity
        // As computation for each row depends only on the previous row computations,
        // use only 2 rows along with modulo-2 divison to switch between the rows
        vector<vector<long> > minPathCostTbl(2, vector<long>(nc, numeric_limits<long>::max()));
        // For 1st row, init the cost to hit reach the top of each cell
        // (note :- the cell is not included in path here)
        for (auto c = 0; c != nc; ++c) {
            minPathCostTbl[0][c] = 0;
        }
        
        // Iterate over each row sequentially from the 1st to last but one row
        for (auto currRow = 0; currRow < nr - 1; ++currRow) { 
            auto nextRow = currRow + 1;
            // Initialize for the next row as space optimization involves
            // switching between just 2 rows
            for (auto nextRowCol = 0; nextRowCol != nc; ++nextRowCol) {
                minPathCostTbl[(nextRow & 0x1)][nextRowCol] = numeric_limits<long>::max();
            }
            // Iterate over each cell/column in the current row from L->R sequentially
            for (auto currCol = 0; currCol != nc; ++currCol) {
                // Update the min path cost terminating at the current cell to
                // include the cell value
                auto & currCellVal = grid[currRow][currCol];
                minPathCostTbl[(currRow & 0x1)][currCol] += currCellVal;

                // Compute the min path cost to reach the cell top for each cell/column
                // in the next row from the current cell
                for (auto nextRowCol = 0; nextRowCol != nc; ++nextRowCol) {
                    auto & hopCost = moveCost[currCellVal][nextRowCol];
                    
                    minPathCostTbl[(nextRow & 0x1)][nextRowCol]
                        = min(minPathCostTbl[(nextRow & 0x1)][nextRowCol],
                              hopCost + minPathCostTbl[(currRow & 0x1)][currCol]);
                }
            }
        }
        
        // Tracks the min path cost to reach any cell from top row
        auto minPathCostToLastRow = numeric_limits<long>::max();
        auto lastRow = nr - 1;
        // Iterate over each cell/col in the last row
        for (auto c = 0; c != nc; ++c) {
            // Update the min path cost terminating at current last row cell to
            // include the cell value
            auto & currCellVal = grid[lastRow][c];
            minPathCostTbl[(lastRow & 0x1)][c] += currCellVal;
            // Update the min path cost over all paths
            minPathCostToLastRow = min(minPathCostToLastRow, minPathCostTbl[(lastRow & 0x1)][c]);
        }

        return minPathCostToLastRow;
    }
};
