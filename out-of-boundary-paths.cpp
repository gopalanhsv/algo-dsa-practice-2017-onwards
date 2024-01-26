// k => maxMoves, m/n => num grid rows/cols
// DP Top Down Memoization Approach
// Time complexity : O(mnk)
// Space complexity : O(mnk)

const int moduloFactor = 1000000000 + 7;

class Solution {
public:
    int
    findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        // Init num grid rows/cols
        _nr = m;
        _nc = n;
        
        //return findPathsBruteForce(maxMove, startRow, startColumn);
        return findPathsTopDownMemoization(maxMove, startRow, startColumn);
    }
    
private:
    
    long
    findPathsBruteForceRec(int nMovesLeft, int r, int c) {        
        // Reached cell (r, c)

        if ((r < 0) || (c < 0) || (r >= _nr) || (c >= _nc)) {
            // Current cell (r, c) is out of grid => Path has crossed boundary
            return 1;
        }
        
        // Current cell (r, c) in grid
        if (nMovesLeft == 0) {
            // No moves left and still in grid => 0 out of boundary paths via this route
            return 0;
        }
        
        // One move used up coming to current cell
        --nMovesLeft;
        
        // Ball can move in 4 directions cell (r, c)
        // Compute the number of paths which can cross the grid boundary with at
        // most the given number of moves left commencing from current cell in the
        // up, down, left and right direction respectively
        
        // Using 'long' return type and one level of 'modulo divison here'
        long nPathsUp = findPathsBruteForceRec(nMovesLeft, r - 1, c) % moduloFactor;
        long nPathsDown = findPathsBruteForceRec(nMovesLeft, r + 1, c) % moduloFactor;
        long nPathsLeft = findPathsBruteForceRec(nMovesLeft, r, c - 1) % moduloFactor;
        long nPathsRight = findPathsBruteForceRec(nMovesLeft, r, c + 1) % moduloFactor;
        
        // Add up the count of possible all paths which cross the grid boundary
        // commencing from (r, c)
        return
            (((nPathsUp + nPathsDown) % moduloFactor) +
             ((nPathsLeft + nPathsRight) % moduloFactor)) % moduloFactor;
    }
    
    int
    findPathsBruteForce(int maxMove, int startRow, int startColumn) {
        // Recursively determine the number of paths via which ball can
        // cross grid boundary commencing at cell (startRow, startColumn)
        return findPathsBruteForceRec(maxMove, startRow, startColumn);
    }

    long
    findPathsTopDownMemoizationRec(int nMovesLeft, int r, int c) {   
        // Reached cell (r, c)
        
        if ((r < 0) || (c < 0) || (r >= _nr) || (c >= _nc)) {
            // Current cell (r, c) is out of grid => Path has crossed boundary
            return 1;
        }
        
        // Current cell (r, c) in grid
        
        // Check if out of boundary paths from current cell for specified
        // number of moves have been computed earlier and stored in cache
        if (_nPathsTbl[r][c][nMovesLeft] != -1) {
            return _nPathsTbl[r][c][nMovesLeft];
        }
        
        
        // Ball can move in 4 directions cell (r, c)
        // Compute the number of paths which can cross the grid boundary with at
        // most the given number of moves left commencing from current cell in the
        // up, down, left and right direction respectively
        
        // Using 'long' return type and one level of 'modulo divison here'
        long nPathsUp = findPathsTopDownMemoizationRec(nMovesLeft - 1, r - 1, c) % moduloFactor;
        long nPathsDown = findPathsTopDownMemoizationRec(nMovesLeft - 1, r + 1, c) % moduloFactor;
        long nPathsLeft = findPathsTopDownMemoizationRec(nMovesLeft - 1, r, c - 1) % moduloFactor;
        long nPathsRight = findPathsTopDownMemoizationRec(nMovesLeft - 1, r, c + 1) % moduloFactor;
        
        // Add up the count of possible all paths which cross the grid boundary
        // commencing from (r, c)
        long nPaths = (((nPathsUp + nPathsDown) % moduloFactor) + 
                      ((nPathsLeft + nPathsRight) % moduloFactor));
        
        // Update cache/memo table for given cell/num moves (r, c, nMovesLeft) tuple
        _nPathsTbl[r][c][nMovesLeft] = nPaths % moduloFactor;
        
        return _nPathsTbl[r][c][nMovesLeft];
    }
    
    int
    findPathsTopDownMemoization(int maxMove, int startRow, int startColumn) {
        
        // Initialize memo/cache table
        _nPathsTbl.resize(_nr);
        for (int r = 0; r < _nr; ++r) {
            _nPathsTbl[r].resize(_nc);
            for (int c = 0; c < _nc; ++c) {
                _nPathsTbl[r][c].resize(maxMove + 1, -1);
                // No moves left => 0 paths using this route.        
                _nPathsTbl[r][c][0] = 0;
            }
        }

        return findPathsTopDownMemoizationRec(maxMove, startRow, startColumn);
    }
    
    // Data members
    // Num rows and cols in grid
    int _nr;
    int _nc;
    
    // Memoization/cache table wherein
    // _nPathsTbl[i][j][k] is the number of paths which can cross the boundary
    // starting from cell(i, j) with at most 'k' moves
    vector<vector<vector<int> > > _nPathsTbl;
};
