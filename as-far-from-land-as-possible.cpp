class Solution {
public:
    int
    maxDistance(vector<vector<int>>& grid) {
        if (grid.empty()) {
            return 0;
        }
        
        // Commence a BFS from all land cells. This will ensure that
        // at each BFS step 'x', unvisited water cells which can
        // be reached with the minimum Manhattan distance 'x' (as no
        // diagonal movement is allowed) from respective
        // land cells will get visited. So the univisited water cells
        // which get visited in the last BFS iteration level/step will
        // be the one(s) at a maximum distance from any of the land cells
        queue<pair<int, int> > bfsQ;
        typedef queue<pair<int, int> >::size_type qSzT;
        
        int nRows = grid.size();
        int nCols = grid[0].size();
        for (int r = 0; r != nRows; ++r) {
            for (int c = 0; c != nCols; ++c) {
                if (1 == grid[r][c]) { // BFS from each land cell
                    bfsQ.push({r, c});
                }
            }
        }
        
        // Allowable movement direction offsets from each cell
        // up/down/left/right
        vector<pair<int, int> > dirV = {
            {0, 1}, {0, -1}, {1, 0}, {-1, 0}  
        };
        
        int nBfsSteps = -1; 
        while (!bfsQ.empty()) {
            ++nBfsSteps;
            qSzT qSize = bfsQ.size(); // Q size for current level
            // Visit all nodes at curr level
            for (qSzT i = 0; i != qSize; ++i) {
                // Dequeue cell at Q front and get its coords
                auto & v = bfsQ.front();
                int X = v.first;
                int Y = v.second;
                bfsQ.pop();
                
                // Enqueue all the valid unvisited neighbour cells
                // to BFS Q for next level visit
                for (auto & dirOffs : dirV) {
                    int nX = X + dirOffs.first;
                    int nY = Y + dirOffs.second;
                    if (nX >= 0 && nY >= 0 && nX < nRows && nY < nCols &&
                        (grid[nX][nY] == 0)) {
                        bfsQ.push({nX, nY}); // Add neighbor cell to BFS Q
                        grid[nX][nY] = 3; // Mark as visited
                    }
                }
            }
        };
        
        // MOST IMPORTANT CHECK HERE : Dont forget
        return nBfsSteps <= 0 ? -1 : nBfsSteps;
    }
};
