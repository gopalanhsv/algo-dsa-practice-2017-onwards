// nr/nc => Num matrix rows/cols
// Time complexity : O(nr x nc)
// Space complexity : O(1)
class Solution {
public:
    vector<vector<int>>
    transpose(vector<vector<int>>& matrix) {
        
        int nr = matrix.size();
        if (0 == nr) {
            // Empty matrix has no transpose
            return matrix;
        }
        
        int nc = matrix[0].size();
        if ((1 == nr) && (1 == nc)) {
            // Single element matrix transpose is identical to it
            return matrix;
        }
        
        // Contruct transposed matrix
        vector<vector<int> > tMatrix(nc, vector<int>(nr));
        // Iterate over the matrix in a row major fashion;
        // and fill the transposed matrix in column major fashion
        for (int r = 0; r != nr; ++r) {
            for (int c = 0; c != nc; ++c) {
                tMatrix[c][r] = matrix[r][c];
            }
        }
        
        return tMatrix;
    }
};
