// p => grid.size(), q => grid[0].size()
// Time complexity : O(pq)
// Space complexity : O(pq)

class Solution {
public:
    typedef enum {
        WATER = 0,
        LAND = 1,
        VISITED = 2
    } GridValT;
    
    int
    countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        if (grid2.empty()) {
            return 0;
        }
        
        // Initialize number of rows/cols and 4-directional neighbour offsets
        _nr = grid2.size();
        _nc = grid2[0].size();
        _nbrOffsetsV = {
            {0, 1}, {0, -1}, {1, 0}, {-1, 0}  
        };
        
        int nSubIslands = 0;
        // Visit each of the grid2 cells
        for (auto r = 0; r != _nr; ++r) {
            for (auto c = 0; c != _nc; ++c) {
                // From each unvisited 'land' grid cell in 'grid2', explore the connected
                // land cells forming the island in 'grid2'. Check if the island in 'grid2'
                // is a sub-island of corresponding region in 'grid1'
                if (GridValT::LAND == grid2[r][c]) {
                    // Island explored via BFS and all constituent cells are marked visited
                    if (isSubIslandAfterExploration(grid1, grid2, r, c)) {
                        ++nSubIslands;
                    }
                }
            }
        }
        
        return nSubIslands;
    }
    

    
private:
    
    bool
    isSubIslandAfterExploration(
        vector<vector<int>>& grid1, vector<vector<int>>& grid2, int startRow, int startCol) {

        queue<pair<int, int> > bfsQ;
        bool isSubIsland = true;
        
        // Commence BFS from the start 'land' cell
        bfsQ.push({startRow, startCol});
        grid2[startRow][startCol] = VISITED;
        
        // Visit entire island to which start cell belongs and mark each cell as VISITED
        while (!bfsQ.empty()) {
            // Dequeue and visit the cell at front of BFS Q
            auto & v = bfsQ.front();
            int X = v.first, Y = v.second;
            bfsQ.pop();
            if (GridValT::WATER == grid1[X][Y]) {
                isSubIsland = false;
            }
            
            // Examine each of the 4-directional neighbours of the above visited
            // cell and schedule the unvisited land cells for a BFS visit in
            // subsequent iteration
            for (auto & nbrOffset : _nbrOffsetsV) {
                // Neighbour coords
                auto nX = X + nbrOffset.first;
                auto nY = Y + nbrOffset.second;
                
                if (nX >= 0 && nX < _nr &&
                    nY >= 0 && nY < _nc && grid2[nX][nY] == GridValT::LAND) {
                    bfsQ.push({nX, nY});
                    grid2[nX][nY] = GridValT::VISITED;
                }
            }
        }
        
        return isSubIsland;
    }

    // Data members
    int _nr;
    int _nc;
    
    // 4 directional neighbour offset from each grid point
    vector<pair<int, int> > _nbrOffsetsV;

};
