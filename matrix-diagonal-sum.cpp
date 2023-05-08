// Time complexity : O(num matrix rows)
// Space complexity : O(1)

class Solution {
public:
    int
    diagonalSum(vector<vector<int>>& mat) {
        int diagonalSum = 0;
        // Number of rows and cols
        int n = mat.size();
        
        // Iterate over matrix rows. Add the cell values
        // of the primary and secondary diagonal for that
        // row to the sum
        for (int r = 0; r != n; ++r) {
            // Primary diagonal sum
            diagonalSum += mat[r][r];
            // Secondary diagonal sum
            if (r != n - 1 - r) {
                // Add the number on the secondary diagonal to the
                // sum only for cases where the primary & secondary
                // diaginal numbers are not in the same location
                diagonalSum += mat[r][n - 1 - r];
            }
        }
        
        return diagonalSum;
    }
};
