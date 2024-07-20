// p => rowSum.size(), q => colSum.size()
// Time complexity : O(pq)
// Space complexity : O(1)

class Solution {
public:
    vector<vector<int>>
    restoreMatrix(vector<int>& rowSum, vector<int>& colSum) {
        // Number of rows and columns
        auto nr = rowSum.size();
        auto nc = colSum.size();
        
        // Output matrix construction
        vector<vector<int> > outV(nr, vector<int>(nc, 0));

#if 0
        // Construct the output matrix in row major fashion
        // Iterate over the matrix in row major fashion
        for (auto r = 0; r != nr; ++r) {
            auto & rSum = rowSum[r];
            for (auto c = 0; c != nc; ++c) {
                // Adopt the greedy method of setting the element value at (r, c) to
                // be the minimum of the current value of remaining row, column sum.
                // Adjust the remainder values of both the row and column sums of
                // current (r, c) to account for this new element
                auto & cSum = colSum[c];
                if (rSum < colSum[c]) {
                    outV[r][c] = rSum;
                    cSum -= rSum;
                    rSum = 0;
                } else {
                    outV[r][c] = cSum;
                    rSum -= cSum;
                    cSum = 0;
                }       
            }
        }
#else
        // Construct the output matrix in col major fashion
        // Iterate over the matrix in column major fashion
        for (auto c = 0; c != nc; ++c) {
            auto & cSum = colSum[c];
            for (auto r = 0; r != nr; ++r) {
                // Adopt the greedy method of setting the element value at (r, c) to
                // be the minimum of the current value of remaining row, column sum.
                // Adjust the remainder values of both the row and column sums of
                // current (r, c) to account for this new element
                auto & rSum = rowSum[r];
                if (rSum < colSum[c]) {
                    outV[r][c] = rSum;
                    cSum -= rSum;
                    rSum = 0;
                } else {
                    outV[r][c] = cSum;
                    rSum -= cSum;
                    cSum = 0;
                }       
            }
        }
#endif
        return outV;
    }
};
