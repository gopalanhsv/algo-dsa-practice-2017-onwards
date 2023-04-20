// Time complexity : O(nrows x ncols)
// Space complexity : O(1)

class Solution {
public:
    vector<int>
    findColumnWidth(vector<vector<int>>& grid) {
        int nr = grid.size();
        int nc = grid[0].size();
    
        if (0 == nr) { 
            // Null grid
            return vector<int>();
        }
        
        vector<int> colWidthV(nc, 0);
        // Iterate over each column of matrix
        for (int c = 0; c != nc; ++c) {
            // Iterate over each element in current column (i.e all rows in column)
            for (int r = 0; r != nr; ++r) {
                auto elem = grid[r][c];
                // Determine current element width
                int currElemWidth = 0;
                if (elem <= 0) {
                    // -ve/0 element, make it +ve and increment element width
                    ++currElemWidth;
                    elem = -elem;
                }
                // Update element width by the number of digits
                while (elem > 0) {
                    ++currElemWidth;
                    elem /= 10;
                }
                // Update the max width of element seen so far for current col
                colWidthV[c] = max(colWidthV[c], currElemWidth);
            }
        }
        
        return colWidthV;
    }
};
