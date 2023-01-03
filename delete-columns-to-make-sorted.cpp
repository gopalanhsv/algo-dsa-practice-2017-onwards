class Solution {
public:
    int
    minDeletionSize(vector<string>& strs) {
        if (strs.empty()) {
            return 0;
        }

        int nUnsortedCols = 0;
        // Number of string rows (different strings) and
        // columns(num chars within string)
        int nc = strs[0].size();
        int nr = strs.size();
        // Iterate in column major order (all rows in a col, then next col)
        // Iterate through the string chars from 1st to last sequentially
        for (int c = 0; c != nc; ++c) {
            // Iterate through all chars in the same position
            // in all strings and check if they are sorted
            int prevChar = strs[0][c];
            for (int r = 1; r != nr; ++r) {
                if (strs[r][c] < prevChar) {
                    ++nUnsortedCols;
                    break;
                }
                prevChar = strs[r][c];
            }
        }
        
        return nUnsortedCols;
    }
};
