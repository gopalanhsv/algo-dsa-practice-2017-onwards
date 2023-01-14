class Solution {
public:
    typedef enum {
        WATER = '0',
        LAND = '1',
        VISITED = '2'
    } GridValT;
    
    int
    numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) {
            return 0;
        }
        
        // Initialize number of rows/cols and 4-directional neighbour offsets
        _nr = grid.size();
        _nc = grid[0].size();
        _nbrOffsetsV = {
            {0, 1}, {0, -1}, {1, 0}, {-1, 0}  
        };
        
        int nIslands = 0;
        // Visit each of the grid cells
        for (int r = 0; r != _nr; ++r) {
            for (int c = 0; c != _nc; ++c) {
                // From each unvisited 'land' grid cell, explore the surrounding
                // unvisited land cells till 'water' or grid extremities are hit
                // via BFS. This ensures that the entire island (to which the
                // initial land cell belongs get covered by BFS visit)
                if (GridValT::LAND == grid[r][c]) {
                    // Island explored via BFS and all constituent cells are
                    // marked visited
                    exploreIslandCompletely(grid, r, c);
                    ++nIslands;
                }
            }
        }
        
        return nIslands;
    }
    
private:
    
    void
    exploreIslandCompletely(vector<vector<char>>& grid, int startRow, int startCol) {
        queue<pair<int, int> > bfsQ;
        typedef queue<pair<int, int> >::size_type qSzT;
        
        // Commence BFS from the start 'land' cell
        bfsQ.push({startRow, startCol});
        grid[startRow][startCol] = VISITED;
        
        // Visit entire island to which start cell belongs
        // and mark each cell as VISITED
        while (!bfsQ.empty()) {
            // Dequeue and visit the cell at front of BFS Q
            auto & v = bfsQ.front();
            int X = v.first, Y = v.second;
            bfsQ.pop();
            
            // Examine each of the 4-directional neighbours of the above visited
            // cell and schedule the unvisited land cells for a BFS visit in
            // subsequent iteration
            for (auto & nbrOffset : _nbrOffsetsV) {
                // Neighbour coords
                int nX = X + nbrOffset.first;
                int nY = Y + nbrOffset.second;
                
                if (nX >= 0 && nX < _nr &&
                    nY >= 0 && nY < _nc && grid[nX][nY] == GridValT::LAND) {
                    bfsQ.push({nX, nY});
                    grid[nX][nY] = GridValT::VISITED;
                }
            }
        }
    }

    // Data members
    int _nr;
    int _nc;
    
    // 4 directional neighbour offset from each grid point
    vector<pair<int, int> > _nbrOffsetsV;
};
