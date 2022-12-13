class Solution {
public:
    int
    minFallingPathSum(vector<vector<int>>& matrix) {
        // Iterate over the matrix cells in row major (top to bottom)
        // fashion; scanning elements from left to right in each row.
        
        // For each cell, track the minimum value of path required
        // to reach the cell
        // i.e. minPathVal(r, c) = minPathVal(r - 1, c - 1) +
        // minPathVal(r - 1, c) + minPathVal(r - 1, c + 1)
        // The min value of path in the last row would the minimum
        // falling path sum
        // The matrix itself is used as the DP/memo table store
        
        int nr = matrix.size();
        int nc = matrix[0].size();
        if (nc == 1) {
            // Single col matrix. Falling path sum would be
            // the sum of all elements
            int minFallPSum = 0;
            for (int r = 0; r != nr; ++r) {
                minFallPSum += matrix[r][0];
            }
            
            return minFallPSum;
        }
        
        // First row has non rows above, so each cell value has
        // the min path value to it
        for (int r = 1; r != nr; ++r) {
            int prevRow = r - 1;
            // Compute min falling path sum for col '0'
            int c = 0;
            int prevRowMin = min(matrix[prevRow][c], matrix[prevRow][c + 1]);
            matrix[r][c] += prevRowMin;
            // Compute min falling path sum for cols [1, nc - 2]
            for (c = 1; c < nc - 1; ++c) {
                prevRowMin = min(matrix[prevRow][c - 1],
                    min(matrix[prevRow][c], matrix[prevRow][c + 1]));
                matrix[r][c] += prevRowMin;
            }
            // Compute min falling path sum for last col
            matrix[r][nc - 1] += min(matrix[prevRow][nc - 2], matrix[prevRow][nc - 1]);
        }
        
        // Iterate over last row elements and get the min
        int minFallPSum = matrix[nr - 1][0];
        for (int c = 1; c != nc; ++c) {
            minFallPSum = min(minFallPSum, matrix[nr - 1][c]);
        }
        
        return minFallPSum;
    }
};
