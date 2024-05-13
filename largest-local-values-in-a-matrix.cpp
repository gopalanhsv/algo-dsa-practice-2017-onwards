// m => grid.size(), n => grid[0].size()
// Time complexity : O(mn)
// Space complexity : O(1)

class Solution {
public:
    vector<vector<int>>
    largestLocal(vector<vector<int>>& grid) {
        auto n = grid.size();
        // Matrix for holding max local values
        auto maxLocalSz = n - 2;
        vector<vector<int> > maxLocalV(maxLocalSz, vector<int>(maxLocalSz, 0));
        
        // Iterate over the original matrix in row major order 
        for (auto r = 0; r != maxLocalSz; ++r) {
            for (auto c = 0; c != maxLocalSz; ++c) {
                // Compute the max local value for (r, c)
                // This will be maximum value in 3x3 grid with top
                // left corner at (r, c)
                
                // Max value in row 'r' cols [c, c + 2]
                int maxLocalVal1 = 
                    max(grid[r][c], max(grid[r][c + 1], grid[r][c + 2]));
                // Max value in row 'r + 1' cols [c, c + 2]
                int maxLocalVal2 =
                    max(grid[r + 1][c], max(grid[r + 1][c + 1], grid[r + 1][c + 2]));
                // Max value in row 'r + 2' cols [c, c + 2]
                int maxLocalVal3 =
                    max(grid[r + 2][c], max(grid[r + 2][c + 1], grid[r + 2][c + 2]));
                
                // Max local value for (r, c) is the max value in 3 x 3 matrix 
                // with top left at (r, c)
                maxLocalV[r][c] =
                    max(maxLocalVal1, max(maxLocalVal2, maxLocalVal3));
            }
        }
        return maxLocalV;
    }
};
