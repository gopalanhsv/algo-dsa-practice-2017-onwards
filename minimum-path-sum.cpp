// Time Complexity
// O(num rows * num cols)
// Space Complexity
// O(1)

class Solution {
public:
    int
    minPathSum(vector<vector<int>>& grid) {
        // Since path movement can be only from a cell to its immediate right
        // or immediate bottom, the minimum path sum to the bottom right corner
        // for a cell located at index r, c is 
        // minPath(r, c) = grid(r, c) + min(minPath(r + 1, c), minPath(r, c + 1));
        // wherein minPath(x, y) is the min path sum from cell (x, y) to
        // bottom right
        // minPathSum for for first cell can be computed by progressively computing
        // the minPaths for all cells from right bottom corner to top left corner
        // one cell at a time moving in a zig-zag fashion from bottom to top with
        // a right to left movement in each row
        int nRows = grid.size();
        int nCols = grid[0].size();
        
        // The grid itself is used to store the min path sum for each cell
        
        // Compute min path sum for all cells of last row
        for (int c = nCols - 2; c >= 0; --c) {
            // Min path sum from a cell in last row is
            // cell value + min path sum from immediate right cell 
            grid[nRows - 1][c] += grid[nRows - 1][c + 1];
        }
        
        // Compute the min path sum for each cell in a zigzag fashion commencing
        // from rightmost col of 2nd last row to leftmost col; then rightmost col
        // of 3rd last row to leftmost col; and so on. For each cell at r, c use
        // minPath(r, c) = grid(r, c) + min(minPath(r, c + 1), minPath(r + 1, c))
        for (int r = nRows - 2; r >= 0; --r) {
            // Min path sum from cell in rightmost col is
            // cell value + min path from cell immediately below
            grid[r][nCols - 1] += grid[r + 1][nCols - 1];
            // Compute min path for other cols of this row
            for (int c = nCols - 2; c >= 0; --c) {
                grid[r][c] += min(grid[r][c + 1], grid[r + 1][c]);
            }    
        }

        return grid[0][0];
    }
};
