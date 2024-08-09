// m, n => num rows, cols in grid
// Time Complexity : O(mn)
// Space Complexity : O(1)

class Solution {
public:
    int
    numMagicSquaresInside(vector<vector<int>>& grid) {
        
        // Num rows and columns
        int nr = grid.size();
        int nc = grid[0].size();
        
        // Xor all numbers from 1 to 9 in order to use this constant to check
        // for presence of all these numbers in every possible 3 x 3 grid
        int allNumsXor1to9 = 0;
        for (int i = 1; i <= 9; ++i) {
            allNumsXor1to9 ^= i;
        }
        
        // Iterate over all possible 3 x 3 grid of numbers in the given grid
        int count = 0;
        for (int r = 0; r <= nr - 3; ++r) {
            for (int c = 0; c <= nc - 3; ++c) {
                // Increment count if the 3 x 3 grid with top left corner cell at
                // (r, c) is a magic square  
                if (isMagicSquare(grid, r, c, allNumsXor1to9)) {
                    ++count;
                }
            }
        }
        
        return count;
    }
    
private:
    
    bool
    isMagicSquare(vector<vector<int>>& grid, int sr, int sc, int allNumsXor1to9) {
        
        // Row 0 entries
        auto & a00 = grid[sr][sc];
        auto & a01 = grid[sr][sc + 1];
        auto & a02 = grid[sr][sc + 2];
        // Row 1 entries
        auto & a10 = grid[sr + 1][sc];
        auto & a11 = grid[sr + 1][sc + 1];
        auto & a12 = grid[sr + 1][sc + 2];
        // Row 2 entries
        auto & a20 = grid[sr + 2][sc];
        auto & a21 = grid[sr + 2][sc + 1];
        auto & a22 = grid[sr + 2][sc + 2];
        
        // All numbers from 1 to 9 would be present in the 3 x 3 grid with top left cell
        // at (sr, sc) if XOR of all the grid elements equals the XOR of all nums in [1, 9]
        if (a00 ^ a01 ^ a02 ^ a10 ^ a11 ^ a12 ^ a20 ^ a21 ^ a22 ^ allNumsXor1to9 != 0) {
            return false;
        }
        
        // Sum of all rows, cols and diagonals should be 15 (since all cols and rows and
        // diagonals add up to same number, so number should be ( 9 x (1 + 9) /2 )/ 3 = 15 )
        return ( a00 + a01 + a02 == 15 && a10 + a11 + a12 == 15 && a20 + a21 + a22 == 15 && // rows sum
                 a00 + a10 + a20 == 15 && a01 + a11 + a21 == 15 && a02 + a12 + a22 == 15 && // cols sum
                 a00 + a11 + a22 == 15 && a02 + a11 + a20 == 15 ); // diagonals sum
    }         
};
