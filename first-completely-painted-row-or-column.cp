// Num rows => nr
// Num cols => nc
// Time complexity : O(nr x nc)
// Space complexity : O(max(nr, nc))

class Solution {
public:
    int
    firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
        // Num rows/cols
        int nr = mat.size();
        int nc = mat[0].size();
        
        int nGridCells = nr * nc;
        // Table mapping from grid 'mat' values to teh row + col indices where
        // these values are present (as each value is unique in grid 'mat')
        vector<pair<int, int> > valToRowColIdxTbl(nGridCells + 1);
        // Iterate over each grid cell and build the mapping between cell values
        // and cell position co-ords
        for (auto r = 0; r != nr; ++r) {
            for (auto c = 0; c != nc; ++c) {
                auto & cellVal = mat[r][c];
                valToRowColIdxTbl[cellVal] = {r, c};
            }
        }
        
        // Table tracking the number of painted cols per row
        vector<int> nPaintedColsTbl(nr, 0);
        // Table tracking the number of painted rows per col
        vector<int> nPaintedRowsTbl(nc, 0);
        // Simulate the painting process sequentially
        for (int i = 0; i != arr.size(); ++i) {
            // Value of cell in 'mat' which gets painted
            auto & cellVal = arr[i];
            // Row and col of cell in 'mat' which gets painted
            auto & r = valToRowColIdxTbl[cellVal].first;
            auto & c = valToRowColIdxTbl[cellVal].second;
            
            // Increment the number of rows which get painted at col 'c'
            if (++nPaintedRowsTbl[c] == nr) {
                // All rows in col 'c' are fully painted
                return i;
            }
            // Increment the number of cols which get painted at row 'r'
            if (++nPaintedColsTbl[r] == nc) {
                // All cols in row 'r' are fully painted
                return i;
            }
        }
        
        // No complete row/col gets fully painted. Error!
        return -1;
    }
};
