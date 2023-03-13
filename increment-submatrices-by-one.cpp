// Time complexity
// O(qxn + nxn) 
// q => number of queries, n => maxtrix row/col size
// Space complexity
// O(n x n), n => matrix row/col size


class Solution {
public:
    vector<vector<int>>
    rangeAddQueries(int n, vector<vector<int>>& queries) {
        
        // Initialize the original matrix with all zeros
        vector<vector<int> > matrixV(n, vector<int>(n, 0));
        
        // Iterate and process the queries sequentially
        for (auto & query : queries) {
            
            // Current query params defining the submatrix range
            // whose contents should be incremented by 1
            auto & topLeftRow = query[0];
            auto & topLeftCol = query[1];
            auto & bottomRightRow = query[2];
            auto & bottomRightCol = query[3];
            
            // Top and bottom rows of the current submatrix range
            auto & rangeStartTop = topLeftRow;
            auto & rangeEndBottom = bottomRightRow;
            // Left and (one col beyond the) right cols of the
            // current submatrix range
            auto & rangeStartLeft = topLeftCol;
            auto rangeEndRight = bottomRightCol + 1;
            // Iterate over each row in the submatrix range
            for (int r = rangeStartTop; r <= rangeEndBottom; ++r) {
                // Mark the column location where submatrix range begins
                // (Delta of +1 should be applied to prefix sum from this col)
                matrixV[r][rangeStartLeft] += 1;
                // Mark the column location where submatrix range ends
                // (Delta of +1 should not be applied to prefix sum from this col)
                if (rangeEndRight < n) {
                    matrixV[r][rangeEndRight] -= 1;   
                }
            }
        }
        
        // Iterate over the matrix cells sequentially in row major order
        for (int r = 0; r != n; ++r) {
            // Apply the appropriate deltas for submatrix ranges which
            // belong ot this column
            auto & rowV = matrixV[r];
            for (int c = 1; c != n; ++c) {
                // Apply deltas via prefix sum
                rowV[c] += rowV[c - 1];
            }
        }
        
        return matrixV;
    }
};
