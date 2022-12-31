class Solution {
public:
    int
    uniquePaths(int m, int n) {
        
        //return uniquePathsDP(m, n);
        return uniquePathsDPSpaceOptimized(m, n);
    }
    
private:

    int
    uniquePathsDP(int m, int n) {
        // Each cell has 2 paths leading to it from adjacent cells
        // A cell (r, c) can be reached by the robot only from the
        // cell on its immediate left (r, c - 1) and from the cell
        // immediately above (r - 1, c). 
        // uniquePaths(r, c) = number of unique paths to cell (r, c) from cell(0, 0)
        // => minUniquePaths(r, c) = minUniquePaths(r, c - 1) + minUniquePaths(r - 1, c)
        
        // numPathsTbl(r, c) gives the number of unique paths
        // to cell(r, c) from top left cell (0, 0)
        vector<vector<int> > numPathsTbl(m, vector<int>(n, 0));
        
        // Each cell in the topmost row can be reached only in
        // one direction from (0, 0); from the cell on its immediate left
        // So number of unique paths for each cell in topmost row is 1
        for (int c = 0; c < n; ++c) {
            numPathsTbl[0][c] = 1;
        }
        // Each cell in the leftmost col can be reached only in
        // one direction from (0, 0); from the cell immediately above.
        // So number of unique paths for each cell in leftmost col is 1
        for (int r = 0; r < m; ++r) {
            numPathsTbl[r][0] = 1;
        }
        
        // All other cells can be reached from the cell immediately above and
        // to the left. So compute the number of unique paths to each cell 
        // from top to down row; and within each row from left to right 
        // (following robot movements)
        for (int r = 1; r < m; ++r) {
            for (int c = 1; c < n; ++c) {
                numPathsTbl[r][c] = numPathsTbl[r - 1][c] + numPathsTbl[r][c - 1];
            }
        }
        
        return numPathsTbl[m - 1][n - 1];
    }  

    int
    uniquePathsDPSpaceOptimized(int m, int n) {
        // Each cell has 2 paths leading to it from adjacent cells
        // A cell (r, c) can be reached by the robot only from the
        // cell on its immediate left (r, c - 1) and from the cell
        // immediately above (r - 1, c). 
        // uniquePaths(r, c) = number of unique paths to cell (r, c) from cell(0, 0)
        // => minUniquePaths(r, c) = minUniquePaths(r, c - 1) + minUniquePaths(r - 1, c)
        
        // numPathsTbl(r, c) gives the number of unique paths
        // to cell(r, c) from top left cell (0, 0)
        vector<vector<int> > numPathsTbl(2, vector<int>(n, 0));
        
        // Each cell in the topmost row can be reached only in
        // one direction from (0, 0); from the cell on its immediate left
        // So number of unique paths for each cell in topmost row is 1
        for (int c = 0; c < n; ++c) {
            numPathsTbl[0][c] = 1;
        }
        // Each cell in the leftmost col can be reached only in
        // one direction from (0, 0); from the cell immediately above.
        // So number of unique paths for each cell in leftmost col is 1
        for (int r = 0; r < 2; ++r) {
            numPathsTbl[r][0] = 1;
        }
        
        // All other cells can be reached from the cell immediately above and
        // to the left. So compute the number of unique paths to each cell 
        // from top to down row; and within each row from left to right 
        // (following robot movements)
        for (int r = 1; r < m; ++r) {
            for (int c = 1; c < n; ++c) {
                numPathsTbl[r & 0x1][c] =
                    numPathsTbl[(r - 1) & 0x1][c] + numPathsTbl[r & 0x1][c - 1];
            }
        }
        
        return numPathsTbl[(m - 1) & 0x1][n - 1];
    }
    
    
    int
    uniquePathsDP1(int m, int n) {
        // From a cell, the robot can move only right or down
        // So problem reduces to a simple DP problem wherein
        // the subproblem is calculation of the number of unique
        // paths from every cell to bottom right corner cell
        // min unique paths to destination from cell at finish
        // point (m, n) = 1;
        // Since, the only way to reach finish point from a cell
        // is to move to the right (same row, +1 col) OR 
        // move down (+1 row, same col) 
        // min unique paths from a cell location at point (r, c)
        // minUniquePaths(r, c) = 
        // num unique paths after moving down one cell +
        // num unique paths after moving one cell to right
        // = minUniquePaths(r + 1, c) + minUniquePaths(r, c + 1)
        
        // Using 1 based indexing for row and col
        vector<vector<int> > minUniquePaths(m + 1, vector<int>(n + 1, 0));
        
        // Min number of unique paths to finish point for all cells
        // in the last row is 1 as the robot can only move to the right to
        // finish point after reaching last row
        for (int c = 1; c <= n; ++c) {
            minUniquePaths[m][c] = 1;
        }
         
        // Min number of unique paths to finish point for all cells
        // in the last col is 1 as the robot can only move down to
        // finish point after reaching last column
        // Determine the number of unique path from each cell to finish
        // point in opposite direction of robot movement
        // i.e. from 2nd last row to 1st row and within each row from
        // rightmost column to leftmost column
        for (int r = m - 1; r >= 1; --r) {
            minUniquePaths[r][n] = 1; // last column is always 1
            for (int c = n - 1; c >= 1; --c) {
                minUniquePaths[r][c] = 
                    minUniquePaths[r + 1][c] + minUniquePaths[r][c + 1];
            }
        }
        
        return minUniquePaths[1][1];
    }
};
