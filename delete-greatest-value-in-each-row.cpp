class Solution {
public:
    int
    deleteGreatestValue(vector<vector<int>>& grid) {
        // Sort each row of the matrix in non-increasing order
        for (auto & rowV : grid) {
            sort(rowV.begin(), rowV.end(), greater<int>());
        }
        
        // Num rows & cols
        int nr = grid.size();
        int nc = grid[0].size();

        // All elements in each row of the matrix are now arranged
        // s.t the elements in each row to be selected for deletion
        // in an iteration are grouped in the same column
        // Iterate over the matrix in column major fashion
        int maxSum = 0;
        for (int c = 0; c != nc; ++c) {
            // Determine maximum element being deleted in the
            // current iteration  (wil the max element in current column)
            int maxElem = grid[0][c];
            for (int r = 1; r != nr; ++r) {
                maxElem = max(maxElem, grid[r][c]);
            }
            maxSum += maxElem;
        }
        
        return maxSum;
    }
};
