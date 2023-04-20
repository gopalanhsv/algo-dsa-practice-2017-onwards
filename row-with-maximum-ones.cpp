// Time complexity : O(nrows x ncols)
// Space complexity : O(1)

class Solution {
public:
    vector<int>
    rowAndMaximumOnes(vector<vector<int>>& mat) {
        // Number of rows/cols
        int nr = mat.size();
        int nc = mat[0].size();
        
        int maxOnesCnt = 0;
        int maxOnesRowIdx = 0;
        // Iterate over each row
        for (int r = 0; r != nr; ++r) {
            // Count the number of ones in current row
            int currRowOnesCnt = 0;
            for (int c = 0; c != nc; ++c) {
                currRowOnesCnt += mat[r][c];
            }
            
            // Update the max coount of ones & respective row
            if (currRowOnesCnt > maxOnesCnt) {
                maxOnesCnt = currRowOnesCnt;
                maxOnesRowIdx = r;
            }
        }
        
        return {maxOnesRowIdx, maxOnesCnt};
    }
};
