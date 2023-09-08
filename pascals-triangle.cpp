// n => numRows
// Time complexity : O(n ^ 2)
// Space complexity : O(n ^ 2) if output included. O(n) othwerise
class Solution {
public:
    vector<vector<int>>
    generate(int numRows) {
        vector<vector<int> > pascalTriangleV;
        pascalTriangleV.resize(numRows);
        
        // Construct each row of pascal triangle sequentially from top to bottom
        for (int r = 0; r != numRows; ++r) {
            // Row 'r' will have 'r + 1' columns
            pascalTriangleV[r].resize(r + 1);
            // Fill in each column of the current row
            for (int c = 0; c != r + 1; ++c) {
                // PT(r, c) = 1 if in first or last column of a row
                // PT(r, c) = PT(r - 1, c - 1) + PT(r - 1, c) otherwise
                if (c == 0 || c == r) {
                    pascalTriangleV[r][c] = 1;
                } else {
                    pascalTriangleV[r][c] =
                        pascalTriangleV[r - 1][c - 1] + pascalTriangleV[r - 1][c];
                }
            }
        }
        
        return pascalTriangleV;
    }
};
