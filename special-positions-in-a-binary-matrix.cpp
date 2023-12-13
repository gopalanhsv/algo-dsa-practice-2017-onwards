// nr => num rows, nc => num cols
// Time complexity : O(nr x nc)
// Space complexity : O(min(nr, nc))

class Solution {
public:
    int
    numSpecial(vector<vector<int>>& mat) {
        auto nr = mat.size();
        auto nc = mat[0].size();
        // Find all rows with a single 1 by
        // traversing matrix in row major fashion
        vector<bool> singleOneRowsV(nr, false);
        for (auto r = 0; r != nr; ++r) {
            auto nRowOnes = 0;
            for (auto c = 0; c != nc; ++c) {
                nRowOnes += mat[r][c];
                if (nRowOnes > 1) {
                    break;
                }
            }
            singleOneRowsV[r] = (nRowOnes == 1);
        }

        // Traverse matrix in column major fashion
        auto nSpecialPositions = 0;
        for (auto c = 0; c != nc; ++c) {
            // Count the number of ones in the current column 'c'
            // and the row id of the last row in current column
            // with a one
            auto oneRowIdx = -1;
            auto nColOnes = 0;
            for (auto r = 0; r != nr; ++r) {
                if (mat[r][c] == 1) {
                    nColOnes += mat[r][c];
                    oneRowIdx = r;
                }
            }
            if ((nColOnes == 1) && singleOneRowsV[oneRowIdx]) {
                // Current column has a single one and it
                // is in a row with a single one too
                ++nSpecialPositions;           
            }
        } 
        
        return nSpecialPositions;
    }
};
