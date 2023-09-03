// Bottom up DP
// Time complexity : O(n x m)
// Space complexity : O(n x m

// DP optimized
// Time complexity : O(n x m)
// Space complexity : O(min(m, n))

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
        // Each cell has 2 paths leading to it from adjacent cells.
        // A cell (r, c) can be reached by the robot only from the cell on its
        // immediate left (r, c - 1) and from the cell immediately above (r - 1, c). 
        // uniquePaths(r, c) = number of unique paths to cell (r, c) from cell(0, 0)
        // => minUniquePaths(r, c) = minUniquePaths(r, c - 1) + minUniquePaths(r - 1, c)
        
        // numPathsTbl(r, c) is the min number of unique paths
        // to cell(r, c) from cell (0, 0)
        vector<vector<int> > numPathsTbl(m, vector<int>(n, 0));
        
        // From (0,0), each cell in topmost row can only be reached from the cell on immediate left
        // So number of unique paths for each cell in topmost row is 1
        for (int c = 0; c < n; ++c) {
            numPathsTbl[0][c] = 1;
        }
        // From (0,0), each cell in leftmost col can only be reached only from the cell immediately above
        // So number of unique paths for each cell in leftmost col is 1
        for (int r = 0; r < m; ++r) {
            numPathsTbl[r][0] = 1;
        }
        
        // All other cells can be reached from the cells immediately above and to the left.
        // Compute the number of unique paths to each cell in row major fashion
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
        // Each cell has 2 paths leading to it from adjacent cells.
        // A cell (r, c) can be reached by the robot only from the cell on its
        // immediate left (r, c - 1) and from the cell immediately above (r - 1, c). 
        // uniquePaths(r, c) = number of unique paths to cell (r, c) from cell(0, 0)
        // => minUniquePaths(r, c) = minUniquePaths(r, c - 1) + minUniquePaths(r - 1, c)
        
        // Since the computation for each row/iteration depends only on the computations made in
        // the prior row/iteration, the computation storage history is optimized by only using
        // 2 rows and modulo-2 divison to switch between the rows for each new computation
        if (m > n) {
            swap(m, n);
        }
        
        // numPathsTbl(r, c) is the min number of unique paths
        // to cell(r, c) from cell (0, 0)
        vector<vector<int> > numPathsTbl(2, vector<int>(n, 0));
        
        // From (0,0), each cell in topmost row can only be reached from the cell on immediate left
        // So number of unique paths for each cell in topmost row is 1
        for (int c = 0; c < n; ++c) {
            numPathsTbl[0][c] = 1;
        }
        // From (0,0), each cell in leftmost col can only be reached only from the cell immediately above
        // So number of unique paths for each cell in leftmost col is 1
        for (int r = 0; r < 2; ++r) {
            numPathsTbl[r][0] = 1;
        }
        
        // All other cells can be reached from the cells immediately above and to the left.
        // Compute the number of unique paths to each cell in row major fashion
        // (following robot movements)
        for (int r = 1; r < m; ++r) {
            for (int c = 1; c < n; ++c) {
                numPathsTbl[r & 0x1][c] =
                    numPathsTbl[(r - 1) & 0x1][c] + numPathsTbl[r & 0x1][c - 1];
            }
        }
        
        return numPathsTbl[(m - 1) & 0x1][n - 1];
    }
};
