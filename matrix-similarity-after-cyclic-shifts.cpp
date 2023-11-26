// R => num rows, C => num cols
// Time complexity : O(R x C)
// Space complexity : O(1)

class Solution {
public:
    bool
    areSimilar(vector<vector<int>>& mat, int k) {
        int nr = mat.size();
        int nc = mat[0].size();
        k = k % nc;
        // Iterate over each element in row-major fashion
        for (auto r = 0; r != nr; ++r) {
            // Examine each element in the current row from left to right col
            for (auto c = 0; c != nc; ++c) {
                // Determine the new column index of element mat[r][c]
                // after accounting for cyclic shift
                auto newCol = 0;
                if (0 == (r & 0x1)) {
                    // Even, left shift by 'k' (+nc to account for -ve vals)
                    newCol = c - k + nc;
                } else {
                    // Even, right shift by 'k'
                    newCol = c + k;
                }
                // Normalize the new col position to [0, nc - 1]
                newCol %= nc;
                
                // Element at new col position should identical to that at old col
                // position in same row for shift to have no effect on matrix val
                if (mat[r][c] != mat[r][newCol]) {
                    // Shifting results in unequal matrices
                    return  false;
                }
            }
        }
        // Shifting results in an identical matrix
        return true;
    }
};
