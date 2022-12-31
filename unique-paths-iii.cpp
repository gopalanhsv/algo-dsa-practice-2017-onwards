class Solution {
public:
    int
    uniquePathsIII(vector<vector<int>>& grid) {
        // Since each empty cell without obstacles has to be visited once from start
        // to end for each unique path avoiding obstacles, only way to execute this
        // is via BFS or DFS with backtracking
        // Will use the DFS with backtracking approach. To track the visited status
        // of each cell during the DFS traversal (since single cell should not be crossed
        // over multiple times in a path, a vector of bitsets or a single bitset can
        // can be used to track visited status
        
        // Init params
        _nRows = grid.size();
        _nCols = grid[0].size();
        _nUniquePaths = 0;
        _neighborOffsV = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
        // Tracks visit status of a cell (r, c) during DFS 
        // Bit value 1 at index r * _nCols + c => cell visited once 
        // Bit value 0 at index r * _nCols + c => cell unvisited
        // Skipping visited empty cells ensures that empty cells are
        // crossed only once per unique path
        bitset<400> visited(0); // since max row and max col is 20 each
        
        // Get source cell params and number of empty cells
        int srcRow, srcCol;
        for (int r = 0; r != _nRows; ++r) {
            for (int c = 0; c != _nCols; ++c) {
                if (1 == grid[r][c]) {
                    srcRow = r;
                    srcCol = c;
                } else if (0 == grid[r][c]) {
                    ++_nEmptyCells;
                } else if (-1 == grid[r][c]) {
                    // Mark obstacles as visited in order to skip cells
                    visited.set(bitsetIdx(r, c));
                }
            }    
        }
        
        
        // Commencing DFS with backtracking from source cell
        // and find all the unique paths with all empty cells
        // from source to destination
        visited[bitsetIdx(srcRow, srcCol)] = 1;
        uniquePathsDFSBacktracking(srcRow, srcCol, visited, 0, grid);
        
        return _nUniquePaths;
    }
    
private :
    
    inline int
    bitsetIdx(int r, int c) {
        return r * _nCols + c;
    }
    
    void
    uniquePathsDFSBacktracking(int r, int c, bitset<400>& visited,
                               int nEmptyCellsVisited,
                               vector<vector<int> > & grid) {
        
        // Not check for visit status here, as call is made only
        // after checking for unvisited status for cell at r, c
        if (2 == grid[r][c]) {
            // Reached destination
            // if number of empty cells are visited once on the way
            // is equal to the number of empty cells in grid, viola we
            // have a unique path
            if (nEmptyCellsVisited == _nEmptyCells) {
                ++_nUniquePaths;
            }
            return;
        }
        
        // Empty cell or source cell reached
        // Mark cell visited to restrict to single visit
        if (0 == grid[r][c]) {
            ++nEmptyCellsVisited;
            visited[bitsetIdx(r, c)] = 1;
        }
        
        // Attempt to visit all empty/non obstacle unvisited 
        // neighbours of this cell in order to reach destination
        
        for (auto & nOffs : _neighborOffsV) {
            
            // Neighbour coords
            int nX = r + nOffs[0], nY = c + nOffs[1];
            
            // Skip visited and invalid cells for path continuation
            if (nX < 0 || nY < 0 || nX >= _nRows || nY >= _nCols ||
                visited[bitsetIdx(nX, nY)]) {
                continue;
            }
            
            // Explore path via neighbour cell
            uniquePathsDFSBacktracking(
                nX, nY, visited, nEmptyCellsVisited, grid);
        }
        
        // Backtrack from current cell (if empty cell) by marking
        // is as unvisited so that another path from source to
        // destination can be found throught the same empty cell
        if (0 == grid[r][c]) {
            --nEmptyCellsVisited;
            visited[bitsetIdx(r, c)] = 0;
        }
    }
    
    // Data members
    // Grid params
    int _nRows;
    int _nCols;
    int _nEmptyCells;
    
    // Tracks the number of unique paths
    int _nUniquePaths;
    
    // Offsets to neighbor cells
    vector<vector<int> > _neighborOffsV;
};
