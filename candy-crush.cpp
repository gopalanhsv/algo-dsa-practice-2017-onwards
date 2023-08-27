// nr => num rows, nc => num cols
// Time complexity : O((nr x nc) ^ 2)
// Space complexity : O(1)
class Solution {
public:
    vector<vector<int>>
    candyCrush(vector<vector<int>>& board) {
        
        // Num rows & cols
        _nr = board.size();
        _nc = board[0].size();
        
        bool candiesCrushed = true;
        // Loop as long as candies are crushed/removed
        while (candiesCrushed) {
        
            // Mark all sets of 3 or more candies which are adjacent
            // vertically for crushing (mark as -ve)
            verticalCrush(board);
            // Mark all sets of 3 or more candies which are adjacent
            // horizontally for crushing (mark as -ve)
            horizontalCrush(board);
            
            // Crush/remove the candies (marked in the 2 steps above)
            // and drop (any) candies which lie directly above the removed candies
            candiesCrushed = dropCandies(board);
        }
        
        return board;
    }
    
private:
    
    void
    verticalColCrush(vector<vector<int>>& board, int col) {
        // Iterate over each row in the current column 'col' from
        // top to bottom sequentially
        for (int lo = 0; lo < _nr; ++lo) {
            auto candyVal = abs(board[lo][col]);
            
            if (candyVal != 0) {
                
                // Find/count if there are set of 3 or more candies
                // vertically adjacent in column 'col' in row range [lo, hi]
                int sameCandyCnt = 1;
                int hi = lo + 1;
                while (hi < _nr) {
                    auto cellVal = abs(board[hi][col]);
                    
                    if (cellVal != candyVal) {
                        break;
                    }
                    ++sameCandyCnt;
                    ++hi;
                }
            
                if (sameCandyCnt >= 3) {
                    // Same candies in row range [lo, hi - 1]
                    // Mark them for crushing in 'crush' phase (as -ve)
                    while (lo < hi) {
                        if (board[lo][col] > 0) {
                            board[lo][col] = -board[lo][col];
                        }
                        ++lo;
                    }
                    // Mark that current column has candies to be crushed
                    _dirtyColsSet.insert(col);
                    // Adjust 'lo' as range [lo, hi - 1] are same candies for crushing.
                    // Next loop should start with value of lo = 'hi' and ++lo 
                    // prior to next iteration of outer loop
                    lo = hi - 1;
                }
            }
        }
    }
    
    void
    verticalCrush(vector<vector<int>>& board) {
        // Iterate over each column of the board
        for (int c = 0; c < _nc ; ++c) {
            // Mark all sets of 3 or more candies which are adjacent
            // vertically in the current column for crushing
            verticalColCrush(board, c);
        }
    }   
    
    void
    horizontalRowCrush(vector<vector<int>>& board, int row) {
        // Iterate over each column in the current row 'row' from
        // left to right sequentially
        for (int lo = 0; lo < _nc; ++lo) {
            auto candyVal = abs(board[row][lo]);
            
            if (candyVal != 0) {
                // Find/count if there are set of 3 or more candies
                // horizontally adjacent in row 'row' in col range [lo, hi]
                int sameCandyCnt = 1;
                int hi = lo + 1;
                while (hi < _nc) {
                    auto cellVal = abs(board[row][hi]);
                    if (cellVal != candyVal) {
                        break;
                    }
                    ++sameCandyCnt;
                    ++hi;
                }
            
                if (sameCandyCnt >= 3) {
                    // Same candies in column range [lo, hi - 1]
                    // Mark them for crushing in 'crush' phase (as -ve)
                    while (lo < hi) {
                        if (board[row][lo] > 0) {
                            board[row][lo] = -board[row][lo];
                        }
                        // Mark that current column has candies to be crushed
                        _dirtyColsSet.insert(lo);
                        ++lo;
                    }
                    // Adjust 'lo' as range [lo, hi - 1] are same candies for crushing.
                    // Next loop should start with value of lo = 'hi' and ++lo 
                    // prior to next iteration of outer loop
                    lo = hi - 1;
                }
            }
            
        }
    }
    
    void
    horizontalCrush(vector<vector<int>>& board) {
        // Iterate over each row of the board
        for (int r = 0; r < _nr ; ++r) {
            // Mark all sets of 3 or more candies which are adjacent
            // horizontally in the current row for crushing
            horizontalRowCrush(board, r);
        }
    }
    
    bool
    dropCandies(vector<vector<int>>& board) {
        
        // Iterate over each column having candies marked for crushing
        for (auto & col : _dirtyColsSet) {
            // Move from bottom to top row in the current column removing
            // the candies marked for crushing and moving retained candies
            // to the holes created by removed candies
            int wrRow = _nr - 1;
            for (int r = wrRow; r >= 0; --r) {
                if (board[r][col] > 0) {
                    board[wrRow--][col] = board[r][col];
                }
            }
            // Eliminate all empty spaces at column top accounting
            // for candies which moved downwards
            for (int r = wrRow; r >= 0; --r) {
                board[r][col] = 0;
            }
        }
        
        bool candiesDroppedInThisIteration = (_dirtyColsSet.size() != 0);
        // Clear the hash table tracking cols whose candies have been
        // crushed in current iteration
        _dirtyColsSet.clear();
        
        return candiesDroppedInThisIteration;
    }
    
    
    
    // Data members
    
    // Num rows and cols in the board
    int _nr, _nc;
    // Hash table tracking columns in which there are candies to be
    // removed (post crush) in each iteration
    unordered_set<int> _dirtyColsSet;
};
