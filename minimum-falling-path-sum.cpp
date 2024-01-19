// m => matrix.size(), n => matrix[0].size(); i.e. num matrix rows/cols

// DP Iterative with Input Modification
// Time complexity : O(m x n)
// Space complexity : O(1)

// DP Iterative
// Time complexity : O(m x n)
// Space complexity : O(m x n)

// DP Iterative Space optimized
// Time complexity : O(m x n)
// Space complexity : O(1)

class Solution {
public:
    int
    minFallingPathSum(vector<vector<int>>& matrix) {
        //return minPSumDPIterativeWithInputModification(matrix);
        //return minPSumDPIterative(matrix);
        return minPSumDPIterativeSpaceOptimized(matrix);
    }
    
private:
    
    int
    fallingPSumForSingleColMatrix(vector<vector<int>>& matrix, int nr) {
        // Falling path sum would be the column sum of all elements
        int minFallPSum = 0;
        for (auto r = 0; r != nr; ++r) {
            minFallPSum += matrix[r][0];
        }
        return minFallPSum;
    }
    
    int
    minPSumDPIterativeWithInputModification(vector<vector<int>>& matrix) {
        auto nr = matrix.size();
        auto nc = matrix[0].size();
        if (nc == 1) {
            // Base case of single col matrix
            return fallingPSumForSingleColMatrix(matrix, nr);
        }
        
        // For first row, each cell value in itself would be min path value to it
        // Iterate over the matrix cells in row major (top to bottom)
        // fashion; scanning elements from L->R in each row.
        
        // For each cell, compute the minimum value of path required to reach the cell
        // minPathVal(r, c) = minPathVal(r - 1, c - 1) + minPathVal(r - 1, c) + minPathVal(r - 1, c + 1)
        // The min value of path in the last row would the minimum falling path sum
        // The matrix itself is used as the DP/memo table store
        for (auto r = 1; r != nr; ++r) {
            int prevRow = r - 1;
            // Compute min falling path sum for first col '0'
            int c = 0;
            int prevRowMin = min(matrix[prevRow][c], matrix[prevRow][c + 1]);
            matrix[r][c] += prevRowMin;
            
            // Compute min falling path sum for cols [1, nc - 2]
            for (c = 1; c < nc - 1; ++c) {
                prevRowMin =
                    min(matrix[prevRow][c - 1], min(matrix[prevRow][c], matrix[prevRow][c + 1]));
                matrix[r][c] += prevRowMin;
            }
            
            // Compute min falling path sum for last col 'nc - 1'
            matrix[r][nc - 1] += min(matrix[prevRow][nc - 2], matrix[prevRow][nc - 1]);
        }
        
        // Iterate over last row elements and compute the min sum
        auto minFallPSum = matrix[nr - 1][0];
        for (auto c = 1; c < nc; ++c) {
            minFallPSum = min(minFallPSum, matrix[nr - 1][c]);
        }
        
        return minFallPSum;
    }
    
    int
    minPSumDPIterative(vector<vector<int>>& matrix) {
        // Num matrix rows/cols
        auto nr = matrix.size();
        auto nc = matrix[0].size();

        if (nc == 1) {
            // Base case of single col matrix
            return fallingPSumForSingleColMatrix(matrix, nr);
        }
        
        // Create a copy of the input matrix as the DP/memo table cache
        vector<vector<int> > dpTbl = matrix;
        // For first row, each cell value in itself would be min path value to it
        
        // For each cell, compute the minimum value of path required to reach the cell
        // minPathVal(r, c) = minPathVal(r - 1, c - 1) + minPathVal(r - 1, c) + minPathVal(r - 1, c + 1)
        // The min value of path in the last row would the minimum falling path sum
        // The matrix itself is used as the DP/memo table store        
        for (auto r = 1; r != nr; ++r) {
            int prevRow = r - 1;
            // Compute min falling path sum for first col '0'
            int c = 0;
            int prevRowMin = min(dpTbl[prevRow][c], dpTbl[prevRow][c + 1]);
            dpTbl[r][c] += prevRowMin;
            
            // Compute min falling path sum for cols [1, nc - 2]
            for (c = 1; c < nc - 1; ++c) {
                prevRowMin =
                    min(dpTbl[prevRow][c - 1], min(dpTbl[prevRow][c], dpTbl[prevRow][c + 1]));
                dpTbl[r][c] += prevRowMin;
            }
            
            // Compute min falling path sum for last col 'nc - 1'
            dpTbl[r][nc - 1] += min(dpTbl[prevRow][nc - 2], dpTbl[prevRow][nc - 1]);
        }

        // Iterate over last row elements and compute the min sum
        auto minFallPSum = dpTbl[nr - 1][0];
        for (auto c = 1; c < nc; ++c) {
            minFallPSum = min(minFallPSum, dpTbl[nr - 1][c]);
        }
        
        return minFallPSum;
    }
    
    int
    minPSumDPIterativeSpaceOptimized(vector<vector<int>>& matrix) {
        // Num matrix rows/cols
        auto nr = matrix.size();
        auto nc = matrix[0].size();

        if (nc == 1) {
            // Base case of single col matrix
            return fallingPSumForSingleColMatrix(matrix, nr);
        }
        
        // Create a copy of the input matrix as the DP/memo table cache
        vector<vector<int> > dpTbl(2, vector<int>(nc, 0));
        // For first row, each cell value in itself would be min path value to it
        dpTbl[0] = matrix[0];
        
        // For each cell, compute the minimum value of path required to reach the cell
        // minPathVal(r, c) = minPathVal(r - 1, c - 1) + minPathVal(r - 1, c) + minPathVal(r - 1, c + 1)
        // The min value of path in the last row would the minimum falling path sum
        // The matrix itself is used as the DP/memo table store        
        for (auto r = 1; r != nr; ++r) {
            int prevRow = (r - 1) & 0x1;
            // Compute min falling path sum for first col '0'
            int c = 0;
            int prevRowMin = min(dpTbl[prevRow][c], dpTbl[prevRow][c + 1]);
            dpTbl[(r & 0x1)][c] = matrix[r][c] + prevRowMin;
            
            // Compute min falling path sum for cols [1, nc - 2]
            for (c = 1; c < nc - 1; ++c) {
                prevRowMin =
                    min(dpTbl[prevRow][c - 1], min(dpTbl[prevRow][c], dpTbl[prevRow][c + 1]));
                dpTbl[(r & 0x1)][c] = matrix[r][c] + prevRowMin;
            }
            
            // Compute min falling path sum for last col 'nc - 1'
            dpTbl[(r & 0x1)][nc - 1] =
                matrix[r][c] + min(dpTbl[prevRow][nc - 2], dpTbl[prevRow][nc - 1]);
        }

        // Iterate over last row elements and compute the min sum
        auto minFallPSum = dpTbl[((nr - 1) & 0x1)][0];
        for (auto c = 1; c < nc; ++c) {
            minFallPSum = min(minFallPSum, dpTbl[((nr - 1) & 0x1)][c]);
        }
        
        return minFallPSum;
    }
};
