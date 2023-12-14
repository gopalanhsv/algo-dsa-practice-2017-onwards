// Num matrix rows => nr
// Num matrix cols => nc
// Time complexity : O(nr x nc)
// Space complexity : O(max(nr, nc)) excluding space for output matrix
class Solution {
public:
    vector<vector<int>>
    onesMinusZeros(vector<vector<int>>& grid) {
        // Num rows/cols
        auto nr = grid.size();
        auto nc = grid[0].size();
        
        // Only maintain the count of ones per row and col
        // (as number of zeros per row and col can be easily obtained
        // using the number of cols and rows respectively)
        // Table tracking the count of ones on a per row basis
        vector<int> rowOnesCntTbl(nr, 0);
        // Table tracking the count of ones on a per col basis
        vector<int> colOnesCntTbl(nc, 0);
        // Iterate over each grid cell and build the requisite tables
        for (auto r = 0; r != nr; ++r) {
            for (auto c = 0; c != nc; ++c) {
                rowOnesCntTbl[r] += grid[r][c];
                colOnesCntTbl[c] += grid[r][c];
            }
        }

        // Output difference matrix
        vector<vector<int> > outDiffV(nr, vector<int>(nc, 0));
        auto rowsPlusCols = nr + nc;
        // Iterate over each grid cell and build the output difference matrix
        for (auto r = 0; r != nr; ++r) {
            for (auto c = 0; c != nc; ++c) {
                // diff[r][c] 
                // = nRowOnes[r] + nColOnes[c] - nRowZeroes[r] - nColZeroes[c]
                // = nRowOnes[r] + nColOnes[c] - {nr - nRowOnes[r] - {nc - nColOnes[c]}}
                // = 2 * (nRowOnes[r] + nColOnes[c]) - nr - nc
                // = 2 * (nRowOnes[r] + nColOnes[c]) - (nr + nc)
                outDiffV[r][c] =
                    2 * (rowOnesCntTbl[r] + colOnesCntTbl[c]) - rowsPlusCols;
            }
        }
        
        return outDiffV;
    }
};
