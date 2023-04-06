// nr = grid rows; nc = grid cols
// Time complexity
// O(nr x nc)
// Space complexity
// O(nr x nc)

// 4 directional neighbour offsets
vector<pair<int, int> > nbrOffsetsV = {
    {0, 1}, {0, -1}, {1, 0}, {-1, 0}  
};

class Solution {
public:
    int
    closedIsland(vector<vector<int>>& grid) {
    
        _nr = grid.size();
        _nc = grid[0].size();
        
        // If any of cells at the boundary row (i.e top/bottom row)
        // or boundary col(left/right col) is a 'land', run a dfs
        // commencing from these cells to mark all connected land
        // cells to these as water cells. This is because the land
        // attached to grid boundaries is not 'closed' and should
        // be treated as water cell
        for (int c = 0; c < _nc; ++c) {
            if (grid[0][c] == 0) {
                // First row
                fillWaterDfs(0, c, grid);
            }
            if (grid[_nr - 1][c] == 0) {
                // Last row
                fillWaterDfs(_nr - 1, c, grid);
            }
        }
        for (int r = 0; r < _nr; ++r) {
            if (grid[r][0] == 0) {
                // First col
                fillWaterDfs(r, 0, grid);
            }
            if (grid[r][_nc - 1] == 0) {
                // Last col
                fillWaterDfs(r, _nc - 1, grid);
            }
        }
        
        // Now iterate through non-boundary cells of the grid. From each
        // unvisited land cell, commence a DFS/flood fill and mark
        // all the connected land cells as visited (change them to water)
        // All these connected land cells which are visited in a
        // DFS/flood fill iteration form a single island/connected component
        // Do the above for all unvisited land cells
        int nClosedIslands = 0;
        for (int r = 1; r < _nr - 1; ++r) {
            for (int c = 1; c < _nc - 1; ++c) {
                if (grid[r][c] == 0) {
                    ++nClosedIslands;
                    fillWaterDfs(r, c, grid);
                }
            }
        }
        
        return nClosedIslands;
    }
    
private:
    
    void
    fillWaterDfs(int r, int c, vector<vector<int> >& grid) {

        // Add start cell to DFS stack
        _dfsStk.push(pair<int, int>(r, c));
        // Fill cell with water (doubles up as visited flag too)
        grid[r][c] = 1;
        while (!_dfsStk.empty()) {
            // Pop cell at top of stack
            auto & v = _dfsStk.top();
            int X = v.first;
            int Y = v.second;
            _dfsStk.pop();

            // Schedule all valid land neighbours of popped off cell
            // for DFS processing in subsequent iterations and fill
            // them with water to mark cell as visited
            for (auto & nbrOffs : nbrOffsetsV) {
                int nX = X + nbrOffs.first;
                int nY = Y + nbrOffs.second;
                
                if (nX >= 0 && nY >= 0 && nX < _nr && nY < _nc && grid[nX][nY] == 0) {
                    _dfsStk.push(pair<int, int>(nX, nY));
                    grid[nX][nY] = 1;
                }
            }
        }
    }
    
    // Data members
    
    // Num rows, cols
    int _nr;
    int _nc;
    stack<pair<int, int> > _dfsStk;
};
