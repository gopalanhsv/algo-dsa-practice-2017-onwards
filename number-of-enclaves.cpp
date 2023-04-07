// nr = num grid rows, nc = num grid cols
// Time complexity : O(nr x nc)
// Space complexity : O(nr x nc)

class Solution {
public:
    int
    numEnclaves(vector<vector<int>>& grid) {
        // Flood land cells of the grid located at grid boundary
        // and all land cells which are reachable from these cells
        // in 4 directions via DFS/BFS. From remaining land cells,
        // one cannot reach the boundary. That would be the number
        // of enclaves
        
        _nr = grid.size();
        _nc = grid[0].size();
        _nbrOffsetsV = {
            {0, 1}, {0, -1}, {1, 0}, {-1, 0}
        };
        
        // Flood fill land cells reachable from left and right grid boundaries
        for (int r = 0; r != _nr; ++r) {
            if (grid[r][0] == 1) {
                floodFillDFS(grid, r, 0);
            }
            if (grid[r][_nc - 1] == 1) {
                floodFillDFS(grid, r, _nc - 1);
            }
        }
        
        // Flood fill land cells reachable from top and bottom grid boundaries
        for (int c = 0; c != _nc; ++c) {
            if (grid[0][c] == 1) {
                floodFillDFS(grid, 0, c);
            }
            if (grid[_nr - 1][c] == 1) {
                floodFillDFS(grid, _nr - 1, c);
            }
        }
        
        // Count the remaining land cells/enclaves
        int nEnclaves = 0;
        for (int r = 0; r != _nr; ++r) {
            for (int c = 0; c != _nc; ++c) {
                nEnclaves += grid[r][c];
            }
        }
        
        return nEnclaves;
    }
    
private:
    
    void
    floodFillDFS(vector<vector<int>>& grid, int sr, int sc) {
        stack<pair<int, int> > dfsStk;
        // Add start cell to DFS stack and mark it as visited
        // by filling it with water
        dfsStk.push(pair<int, int>(sr, sc));
        grid[sr][sc] = 0;
        // Commence DFS
        while (!dfsStk.empty()) {
            // Visit and pop-off the at top of DFS stack
            // Fill it with water
            auto & v = dfsStk.top();
            int X = v.first;
            int Y = v.second;
            dfsStk.pop();
            
            // Explore neighbors of visited land cell
            for (auto & nbrOffs : _nbrOffsetsV) {
                int nX = X + nbrOffs.first;
                int nY = Y + nbrOffs.second;
                
                // Set up valid unvisited land cell neighbors for DFS
                // visit in the subsequent iterations
                if (nX >= 0 && nY >= 0 && nX < _nr && nY < _nc &&
                   grid[nX][nY] == 1) {
                    dfsStk.push(pair<int, int>(nX, nY));
                    grid[nX][nY] = 0;
                }
            }
        }
    }
    
    // Data members
    // Num rows/cols
    int _nr;
    int _nc;
    // 4 directional neighbour offsets from each grid cell
    vector<pair<int, int> > _nbrOffsetsV;
};
