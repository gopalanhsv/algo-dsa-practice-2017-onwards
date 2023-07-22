// DP approach
// Time complexity : O(n x n x k)
// Space complexity : O(n x n x k)

// Space optimized DP approach
// Time complexity : O(n x n x k)
// Space complexity : O(n x n)

class Solution {
public:
    double
    knightProbability(int n, int k, int row, int column) {
        if (0 == k) {
            // Base case of no moves, knight stays on board
            return 1;
        }
        if (1 == n) {
            // Base case of move on a single unit board leads outside always
            return 0;
        }

        return knightProbabilityViaDPOptimized(n, k, row, column);
        //return knightProbabilityViaDP(n, k, row, column);
    }
    
private:
    
    double
    knightProbabilityViaDP(int n, int nMoves, int sRow, int sCol) {
        
        // 1. From a cell (r, c), the knight can make an equiprobable move
        // to any of the following 8 cells (valid cells only) 
        // (r + 2, c + 1), (r + 2, c - 1), (r - 2, c + 1), (r - 2, c - 1),
        // (r + 1, c + 2), (r + 1, c - 2), (r - 1, c + 2), (r - 1, c - 2)
        // In the reverse direction, the knight can reach cell(r, c) from
        // only one of the aforementioned 8 cell
        // 2. So probability of each of the moves from/to a cell is 1/8
        // 3. Let P(r, c, m) be the probability of reaching the cell (r, c)
        // in the 'm' th move
        // Since the cell (r, c) can be reached with a probabilty of 1/8
        // in the 'm'th move from any of the 8 (valid) cells as per pt #1, 
        // we get
        //  P(r, c, m) = 1/8 * 
        // [ P(r + 2, c + 1, m - 1) + P(r + 2, c - 1, m - 1) +
        //   P(r - 2, c + 1, m - 1) + P(r - 2, c - 1, m - 1) +
        //   P(r + 1, c + 2, m - 1) + P(r + 1, c - 2, m - 1) +
        //   P(r - 1, c + 2, m - 1) + P(r - 1, c - 2, m - 1) ]
        
        // Using the above equation, one can easily set up a DP based iterative
        // approach to compute the final result by summing up the probabilities
        // all the grid cells after all of the specified moves are executed

        // dpTbl[r][c][m] is the probability of reaching the cell (r, c)
        // in the 'm' th move
        vector<vector<vector<double> > >
            dpTbl(n, vector<vector<double> >(n, vector<double>(nMoves + 1, 0.0)));
        
        vector<pair<int, int> > srcCellOffsetsV = {
            {2, 1}, {2, -1}, {-2, 1}, {-2, -1},  
            {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
        };
        
        // Initially knight is at cell(sRow, sCol). 0 moves from here will
        // result in knight remaining on the board (probability == 1)
        dpTbl[sRow][sCol][0] = 1;
        // Probability of knight moving from a cell to another
        double singleMoveProb = 1.0 / 8;
        
        // Iterate over the moves sequentially
        for (int moveId = 1; moveId <= nMoves; ++moveId) {
            // Compute the probability for reaching each of the grid cells in move 'moveId'
            // from the 8 possible source cells
            // Iterate over each grid cell
            for (int r = 0; r != n; ++r) {
                for (int c = 0; c != n; ++c) {
                    // Iterate over the possible source cells from where cell (r, c)
                    // can be reached by the knight in move 'moveId'. The source cell
                    // should have been reached in previous move
                    // Compute the sum of reaching each of the source cells in
                    // previous move 'moveId - 1'
                    double srcCellProbSum = 0;
                    for (auto & srcCellOffset : srcCellOffsetsV) {
                        // Source cell coords
                        auto sX = r + srcCellOffset.first;
                        auto sY = c + srcCellOffset.second;
                        if ((sX >= 0) && (sY >= 0) && (sX < n) && (sY < n)) {
                            // Valid source cell
                            srcCellProbSum += dpTbl[sX][sY][moveId - 1];
                        }
                    }
                    
                    // Compute the probabilty of reaching  current cell (r, c) from
                    // the source cell in move 'moveId'
                    dpTbl[r][c][moveId] = srcCellProbSum * singleMoveProb;
                }
            }
        }
        
        // Total probability of remaining on the board at the end of 'nMoves'
        // is obtained by summing up the probability for reaching each of the
        // cells in the grid in move 'nMoves'
        double finalProb = 0;
        // Iterate over each grid cell for final move and add up the probabilities
        for (int r = 0; r != n; ++r) {
            for (int c = 0; c != n; ++c) {
                finalProb += dpTbl[r][c][nMoves];
            }
        }
        
        return finalProb;
    }
    
    double
    knightProbabilityViaDPOptimized(int n, int nMoves, int sRow, int sCol) {
        
        // 1. From a cell (r, c), the knight can make an equiprobable move
        // to any of the following 8 cells (valid cells only) 
        // (r + 2, c + 1), (r + 2, c - 1), (r - 2, c + 1), (r - 2, c - 1),
        // (r + 1, c + 2), (r + 1, c - 2), (r - 1, c + 2), (r - 1, c - 2)
        // In the reverse direction, the knight can reach cell(r, c) from
        // only one of the aforementioned 8 cell
        // 2. So probability of each of the moves from/to a cell is 1/8
        // 3. Let P(r, c, m) be the probability of reaching the cell (r, c)
        // in the 'm' th move
        // Since the cell (r, c) can be reached with a probabilty of 1/8
        // in the 'm'th move from any of the 8 (valid) cells as per pt #1, 
        // we get
        //  P(r, c, m) = 1/8 * 
        // [ P(r + 2, c + 1, m - 1) + P(r + 2, c - 1, m - 1) +
        //   P(r - 2, c + 1, m - 1) + P(r - 2, c - 1, m - 1) +
        //   P(r + 1, c + 2, m - 1) + P(r + 1, c - 2, m - 1) +
        //   P(r - 1, c + 2, m - 1) + P(r - 1, c - 2, m - 1) ]
        
        // Using the above equation, one can easily set up a DP based iterative
        // approach to compute the final result by summing up the probabilities
        // all the grid cells after all of the specified moves are executed

        // Since the probability for reaching a cell in current move depends only upon
        // the probability of reaching souroce cells in the immediate previous move,
        // one can save space by storing state of only 2 moves (instead of all)
        // and use modulo-2 division to compute each state from previous
        
        // dpTbl[r][c][m % 2] is the probability of reaching the cell (r, c)
        // in the 'm' th move
        vector<vector<vector<double> > >
            dpTbl(n, vector<vector<double> >(n, vector<double>(2, 0.0)));
        
        vector<pair<int, int> > srcCellOffsetsV = {
            {2, 1}, {2, -1}, {-2, 1}, {-2, -1},  
            {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
        };
        
        // Initially knight is at cell(sRow, sCol). 0 moves from here will
        // result in knight remaining on the board (probability == 1)
        dpTbl[sRow][sCol][0] = 1;
        // Probability of knight moving from a cell to another
        double singleMoveProb = 1.0 / 8;
        
        // Iterate over the moves sequentially
        for (int moveId = 1; moveId <= nMoves; ++moveId) {
            // Compute the probability for reaching each of the grid cells in move 'moveId'
            // from the 8 possible source cells
            // Iterate over each grid cell
            for (int r = 0; r != n; ++r) {
                for (int c = 0; c != n; ++c) {
                    // Iterate over the possible source cells from where cell (r, c)
                    // can be reached by the knight in move 'moveId'. The source cell
                    // should have been reached in previous move
                    // Compute the sum of reaching each of the source cells in
                    // previous move 'moveId - 1'
                    double srcCellProbSum = 0;
                    for (auto & srcCellOffset : srcCellOffsetsV) {
                        // Source cell coords
                        auto sX = r + srcCellOffset.first;
                        auto sY = c + srcCellOffset.second;
                        if ((sX >= 0) && (sY >= 0) && (sX < n) && (sY < n)) {
                            // Valid source cell
                            srcCellProbSum += dpTbl[sX][sY][(moveId - 1) & 0x1];
                        }
                    }
                    
                    // Compute the probabilty of reaching  current cell (r, c) from
                    // the source cell in move 'moveId'
                    dpTbl[r][c][(moveId & 0x1)] = srcCellProbSum * singleMoveProb;
                }
            }
        }
        
        // Total probability of remaining on the board at the end of 'nMoves'
        // is obtained by summing up the probability for reaching each of the
        // cells in the grid in move 'nMoves'
        double finalProb = 0;
        // Iterate over each grid cell for final move and add up the probabilities
        for (int r = 0; r != n; ++r) {
            for (int c = 0; c != n; ++c) {
                finalProb += dpTbl[r][c][(nMoves & 0x1)];
            }
        }
        
        return finalProb;
    }
    
};
