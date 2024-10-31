// p => grid.size(), q => grid[0].size()
// DP Approach
// Time Complexity : O(pq)
// Space Complexity : O(pq)

class Solution {
public:
    int
    maxMoves(vector<vector<int>>& grid) {
        return maxMovesViaDP(grid);
    }
    
private:
    int
    maxMovesViaDP(vector<vector<int>>& grid) {
        int nMaxMoves = 0;
        auto nr = grid.size();
        auto nc = grid[0].size();

        // reachableCellV(r, c) indicates if cell (r, c) in the current 
        // column 'c' being examined can be reachable by any of 3 directional
        // cells in the preceeding column
        vector<vector<bool> > reachableCellV(nr, vector<bool>(nc, false));
        // All cells in first column are reachable
        for (auto r = 0; r < nr; ++r) {
            reachableCellV[r][0] = true;
        }
        // Iterate over each column sequentially from L->R
        for (auto c = 0; c < nc - 1; ++c) {
            // Flag capturing if any cell in next column is reachable from a
            /// cell in the current current
            bool nextColReachable = false;
            // Iterate over all rows in column 'c' sequentially from top to bottom
            for (auto r = 0; r < nr; ++r) {
                if (reachableCellV[r][c]) {
                    
                    // Cell (r, c) is reachable via a move from the preceeding
                    // column 'c - 1' cells
                    auto currCellVal = grid[r][c];                  
                    if ((r - 1 >= 0) && (grid[r - 1][c + 1] > currCellVal)) {
                        reachableCellV[r - 1][c + 1] = true;
                        nextColReachable = true;
                    }
                    if (grid[r][c + 1] > currCellVal) {
                        reachableCellV[r][c + 1] = true;
                        nextColReachable = true;
                    }
                    if ((r + 1 < nr) && (grid[r + 1][c + 1] > currCellVal)) {
                        reachableCellV[r + 1][c + 1] = true;
                        nextColReachable = true;
                    }
                }
            }
            if (!nextColReachable) {
                // Move halted from column c -> c + 1
                break;
            }
            // Move possible from column c -> c + 1
            ++nMaxMoves;
        }
            
        return nMaxMoves;
    }
};
