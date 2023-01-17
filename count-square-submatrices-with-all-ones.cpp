class Solution {
public:
    int
    countSquares(vector<vector<int>>& matrix) {
        // Number of rows/cols
        int nr = matrix.size();
        int nc = matrix[0].size();
        int maxSqSz = min(nr, nc);
        
        int numSrqWithAllOnes = 0;
        
        // Init DP table
        dpTbl.resize(nr);
        for (int r = 0; r < nr; ++r) {
            dpTbl[r].resize(nc);
            for (int c = 0; c < nc; ++c) {
                dpTbl[r][c].resize(maxSqSz + 1, false);
                if (matrix[r][c]) {
                    dpTbl[r][c][1] = true;
                    ++numSrqWithAllOnes;
                }
            }   
        }
        
        // Note that a square submatrix of size 's' has all ones, only if
        // all the 4 square submatrices of size 's - 1' at the four corners
        // of bigger size 's' submatrix have all ones
        // Or in other words; 
        // DP(r, c, s) ==
        // DP(r, c, s - 1) && DP(r, c + 1, s - 1) && DP(r + 1, c, s - 1) && DP(r + 1, c + 1, s - 1)
        
        // Iterate over all possible square submatrix size (other than 1)
        for (int s = 2; s <= maxSqSz; ++s) {
            int endRow = nr - s;
            int endCol = nc - s;
            // Iterate over all possible squares of given size and
            // check if they are all ones
            for (int startRow = 0; startRow <= endRow; ++startRow) {
                for (int startCol = 0; startCol <= endCol; ++startCol) {   
                    
                    if (dpTbl[startRow][startCol][s - 1] &&
                        dpTbl[startRow][startCol + 1][s - 1] &&
                        dpTbl[startRow + 1][startCol][s - 1] &&
                        dpTbl[startRow + 1][startCol + 1][s - 1]) {
                        dpTbl[startRow][startCol][s] = true;
                        ++numSrqWithAllOnes;
                    }
                }    
            }
            
        }
        
        return numSrqWithAllOnes;
    }
    
private:
    
    // DP table with property that 
    // dpTbl[r][c][s] is "true" if the square of size 's' starting
    // at r, c (ending at r + s - 1, c + s - 1) is a square of all 1's;
    // "false" otherwise
    vector<vector<vector<bool> > > dpTbl;
};
