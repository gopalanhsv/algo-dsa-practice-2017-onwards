class Solution {
public:
    int
    snakesAndLadders(vector<vector<int>>& board) {
        // Number of board rows and cols
        _n = board.size();

        // Problem reduces to a simple BFS traversal as follows:-
        // 1. Commence from the cell 1 at bottom left (n - 1, 0)
        //    by adding it to BFS Q
        // 2. Visit all the cells queued in the BFS Q for the
        //    current iteration
        // 2(a) Determine 6 possible cells to move to from current
        //    cell. If any of the 6 cells have a snake/ladder; the
        //    next cell is choosen as the snake/ladder destination
        //    instead of the cell itself. These 6 cells if
        //    not yet visited earlier, are scheduled for a BFS visit
        //    in the next iteration by tacking them on to the BFS Q
        // 3. Go back to step 2 till the destination cell with label
        //    (n * n) gets visited/no more cells are there to visit
        
        // The least number of moves to reach the destination from origin
        // would be the number of BFS iterations/steps to first hit the
        // destination
        
        int nMoves = 0;
        queue<int> bfsQ;
        typedef queue<int>::size_type qSzT;
        vector<bool> visitedV(_n * _n + 1, false);
        int destinationSqr = _n * _n;
        
        // Commence BFS from origin square
        bfsQ.push(1);
        visitedV[1] = false;
        while (!bfsQ.empty()) {
            
            // Visit all squares scheduled for a visit in the current iteration/move
            qSzT currLvlSz = bfsQ.size();
            for (qSzT i = 0; i != currLvlSz; ++i) {
                
                // Dequeue & visit the square at BFS Q front
                auto curr = bfsQ.front();
                bfsQ.pop();
                
                if (curr == destinationSqr) {
                    // Reached the destination square
                    return nMoves;
                }
                
                // Schedule all the unvisited squares which can be visited
                // from the current square in a single move for a BFS
                // traversal in the next iteration
                int startSqr = curr + 1;
                int endSqr = min(curr + 6, destinationSqr);
                for (int nextSqr = startSqr; nextSqr <= endSqr; ++nextSqr) {
                    // Account for snake/ladder jump at the next square
                    auto destSqr = adjustForSnakeLadders(nextSqr, board);
                    // Move to next square/associated snake/ladder square
                    if (!visitedV[destSqr]) {
                        // Mark destination square as visited
                        visitedV[destSqr] = true;
                        // Enqueue the square to BFS Q
                        bfsQ.push(destSqr);
                    }
                }
            }
            
            // Increment number of moves
            ++nMoves;
        }
        
        // Not possible to reach destination
        return -1;
    }
    
private:
    
    // Data members
    // Number of rows/cols
    int _n;
    
    inline int
    adjustForSnakeLadders(int next, vector<vector<int> >& board) {
        
        // Jump to snake/ladder at cell 'next' if available
        
        // Row for location of cell with label 'next'
        int r = _n - 1 - ((next - 1) / _n);
        
        // Column for location of cell with label 'next'
        // Odd numbered rows (from bottom to top) are numbered R to L
        // Even numbered rows (from bottom to top) are numbered L to R
        int c = (next - 1) % _n;
        if (1 == ((_n - 1 - r) & 0x1)) {
            c = _n - 1 - c;
        }
        
        if (-1 == board[r][c]) {
            // No snake/ladder at cell with label 'next'
            return next;
        }
        
        // Snake/ladder at cell with label 'next'
        return board[r][c];
    }
    
};
