class Solution {
public:
    int
    uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        return uniquePathsWithObstaclesDp(obstacleGrid);
        //return uniquePathsWithObstaclesDpOptimized(obstacleGrid);
    }
    
private:
    
    int
    uniquePathsWithObstaclesDp(vector<vector<int>>& obstacleGrid) {
        // Number of rows/cols in the grid
        int nr = obstacleGrid.size();
        int nc = obstacleGrid[0].size();
        // Table with the min number of unique paths from the (0, 0) cell to each
        // cell in the grid (with movement allowed only to immediate right or
        // immediate down if the respective cells are not blocked by obstacles)
        vector<vector<int> > minNumUniquePathsTbl(nr, vector<int>(nc, 0));
        
        // Base case of there being an obstacle at either source
        // or destination cell; then no path can exist even if remainder
        // of the grid has nil obstacles
        if (1 == obstacleGrid[0][0] ||
            1 == obstacleGrid[nr - 1][nc - 1]) {
            return 0;
        }

        // Since the robot can move from a cell only to the immediate cell on
        // its right or down; the minimum number of unique paths to reach the
        // destination from source reduces to a DP problem. The subproblems
        // being the minimum number of unique paths to reach each
        // cell in the grid from the source cell at (0, 0)

        // For cell at (0, 0), there is only one path to reach it from self
        minNumUniquePathsTbl[0][0] = 1;
        
        // For all cells in the first/0th row, one can reach a cell at (0, c) only
        // from the cell on its immediate left at (0, c - 1) if the cell at (0, c)
        // has no obstacle. So, min number of unique paths to reach a cell (0, c)
        // is same as the min number of unique paths to reach cell on its immediate
        // left (0, c - 1); if cell (0, c) has no obstacle
        for (int c = 1; c != nc; ++c) {
            if (obstacleGrid[0][c] == 1) {
                // Cell has an obstacle. So no path to reach the cell
                minNumUniquePathsTbl[0][c] = 0;
            } else {
                minNumUniquePathsTbl[0][c] = minNumUniquePathsTbl[0][c - 1];
            }
        }
        
        // For all cells in the first/0th column, one can reach a cell at (r, 0) only
        // from the cell immediately above at (r - 1, 0) if the cell at (r, 0)
        // has no obstacle. So, min number of unique paths to reach a cell (r, 0)
        // is same as the min number of unique paths to reach cell immediately
        // above (r - 1, 0); if cell (r, 0) has no obstacle
        for (int r = 1; r != nr; ++r) {
            if (obstacleGrid[r][0] == 1) {
                // Cell has an obstacle. So no path to reach the cell
                minNumUniquePathsTbl[r][0] = 0;
            } else {
                minNumUniquePathsTbl[r][0] = minNumUniquePathsTbl[r - 1][0];
            }
        }
        
        // For all cells not in the the first/0th row/column, one can reach a cell at
        // (r, c) only from the cell immediately above at (r - 1, c) and from the cell
        // on the immediate right (r, c - 1); if the cell at (r, 0) has no obstacle.
        // So, minNumUniquePaths(r, c) = 
        // minNumUniquePaths(r - 1, c) (for cell immediately above) +
        // minNumUniquePaths(r, c - 1) (for cell to immediate left);
        // if cell (r, c) has no obstacle       
        for (int r = 1; r != nr; ++r) {
            for (int c = 1; c != nc; ++c) {
                if (obstacleGrid[r][c] == 1) {
                    // Cell has an obstacle. So no path to reach the cell
                    minNumUniquePathsTbl[r][c] = 0;
                } else {
                    minNumUniquePathsTbl[r][c] =
                        minNumUniquePathsTbl[r][c - 1] + minNumUniquePathsTbl[r - 1][c];
                } 
            }
        }
        
        // Min number of unique paths to reach bottom right cell from (0, 0)
        return minNumUniquePathsTbl[nr - 1][nc - 1];
    }

    
    int
    uniquePathsWithObstaclesDpOptimized(vector<vector<int>>& obstacleGrid) {
        // Number of rows/cols in the grid
        int nr = obstacleGrid.size();
        int nc = obstacleGrid[0].size();
        // Table with the min number of unique paths from the (0, 0) cell to each
        // cell in the grid (with movement allowed only to immediate right or
        // immediate down if the respective cells are not blocked by obstacles)
        vector<vector<int> > minNumUniquePathsTbl(2, vector<int>(nc, 0));
        
        // Base case of there being an obstacle at either source
        // or destination cell; then no path can exist even if remainder
        // of the grid has nil obstacles
        if (1 == obstacleGrid[0][0] ||
            1 == obstacleGrid[nr - 1][nc - 1]) {
            return 0;
        }

        // Since the robot can move from a cell only to the immediate cell on
        // its right or down; the minimum number of unique paths to reach the
        // destination from source reduces to a DP problem. The subproblems
        // being the minimum number of unique paths to reach each
        // cell in the grid from the source cell at (0, 0)

        // For cell at (0, 0), there is only one path to reach it from self
        minNumUniquePathsTbl[0][0] = 1;
        
        // For all cells in the first/0th row, one can reach a cell at (0, c) only
        // from the cell on its immediate left at (0, c - 1) if the cell at (0, c)
        // has no obstacle. So, min number of unique paths to reach a cell (0, c)
        // is same as the min number of unique paths to reach cell on its immediate
        // left (0, c - 1); if cell (0, c) has no obstacle
        for (int c = 1; c != nc; ++c) {
            if (obstacleGrid[0][c] == 1) {
                // Cell has an obstacle. So no path to reach the cell
                minNumUniquePathsTbl[0][c] = 0;
            } else {
                minNumUniquePathsTbl[0][c] = minNumUniquePathsTbl[0][c - 1];
            }
        }
        
        // For all cells in the first/0th column, one can reach a cell at (r, 0) only
        // from the cell immediately above at (r - 1, 0) if the cell at (r, 0)
        // has no obstacle. So, min number of unique paths to reach a cell (r, 0)
        // is same as the min number of unique paths to reach cell immediately
        // above (r - 1, 0); if cell (r, 0) has no obstacle
        for (int r = 1; r != nr; ++r) {
            if (obstacleGrid[r][0] == 1) {
                // Cell has an obstacle. So no path to reach the cell
                minNumUniquePathsTbl[(r & 0x1)][0] = 0;
            } else {
                minNumUniquePathsTbl[(r & 0x1)][0] = 
                    minNumUniquePathsTbl[((r - 1) & 0x1)][0];
            }
        }
        
        // For all cells not in the the first/0th row/column, one can reach a cell at
        // (r, c) only from the cell immediately above at (r - 1, c) and from the cell
        // on the immediate right (r, c - 1); if the cell at (r, 0) has no obstacle.
        // So, minNumUniquePaths(r, c) = 
        // minNumUniquePaths(r - 1, c) (for cell immediately above) +
        // minNumUniquePaths(r, c - 1) (for cell to immediate left);
        // if cell (r, c) has no obstacle       
        for (int r = 1; r != nr; ++r) {
            for (int c = 1; c != nc; ++c) {
                if (obstacleGrid[r][c] == 1) {
                    // Cell has an obstacle. So no path to reach the cell
                    minNumUniquePathsTbl[(r & 0x1)][c] = 0;
                } else {
                    minNumUniquePathsTbl[(r & 0x1)][c] =
                        minNumUniquePathsTbl[(r & 0x1)][c - 1] +
                        minNumUniquePathsTbl[((r - 1) & 0x1)][c];
                } 
            }
        }
        
        // Min number of unique paths to reach bottom right cell from (0, 0)
        return minNumUniquePathsTbl[((nr - 1) & 0x1)][nc - 1];
    }
};
