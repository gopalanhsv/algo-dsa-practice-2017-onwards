// nr => num grid rows
// nc => num grid cols
// Time complexity : O(nr x nc)
// Space complexity : O(nr x nc)

class Solution {
public:
    vector<vector<int>>
    updateMatrix(vector<vector<int>>& mat) {
        
        // Initialize
        init(mat);
        // Use simultaneous BFS from each of the 0 cells to
        // determine distances to nearest 0 for the 1 cells
        distanceToNearestZeroViaBFS(mat);
        return _shortestDistV;
    }
    
private:
    
    void
    init(vector<vector<int> >& grid) {
        _nRows = grid.size();
        _nCols = grid[0].size();

        _shortestDistV.resize(_nRows);
        for (int r = 0; r != _nRows; ++r) {
            _shortestDistV[r].resize(_nCols, numeric_limits<int>::max());
        }

        _nbrOffsetsV = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    }
    
    void
    distanceToNearestZeroViaBFS(vector<vector<int> >& grid) {
        
        // BFS traversal Q
        queue<pair<int, int> > bfsQ;
        typedef queue<pair<int, int> >::size_type qSzT;
        vector<vector<bool> > visited(_nRows, vector<bool>(_nCols, false));
        
        // Iterate over all grid points. All points with value 0 are added to
        // BFS Q and their shortest distance to 0 are marked as 0.
        // Other points (i.e. 1's) have shortest distance marked as +inf
        for (int r = 0; r != _nRows; ++r) {
            for (int c = 0; c != _nCols; ++c) {
                if (grid[r][c] == 0) {
                    _shortestDistV[r][c] = 0;
                    bfsQ.push({r, c});
                    visited[r][c] = true;
                }
            } 
        }
        
        // Commence simultaneous BFS traversal from each of the 0 cells.
        // The number of traversal hops at the first time a 1 cell gets 
        // hit during the traversal, would be the shortest distance from
        // the nearest 0 for the particular 1 cell
        int bfsLevel = 0;
        while (!bfsQ.empty()) {
            ++bfsLevel;
            // Visit all nodes at current BFS level 
            auto qSize = bfsQ.size();
            for (int i = 0; i != qSize; ++i) {
                // Pop off the vertex at head of BFS Q
                auto v = bfsQ.front();
                bfsQ.pop();
                // Schedule all unvisited neighbors of the popped off vertex
                // for a BFS visit in the next iteration
                int X = v.first;
                int Y = v.second;
                for (auto & nbrOffset : _nbrOffsetsV) {
                    // Neighbor vertex coords
                    int nX = X + nbrOffset.first;
                    int nY = Y + nbrOffset.second;
                    if (nX < 0 || nY < 0 || nX >= _nRows || nY >= _nCols || visited[nX][nY]) {
                        // Invalid/visited neighbor
                        continue;
                    }
                    // Unvisited neighbor (i.e a 1 yet to be visited) from nearest 0 hit
                    // Update its shortest distance
                    _shortestDistV[nX][nY] = bfsLevel;
                    // Schedule neighbor cell for a BFS visit in the next iteration
                    bfsQ.push({nX, nY});
                    visited[nX][nY] = true;
                }
            }
        }
    }

    // Data members
    // Number of matrix rows/cols
    int _nRows;
    int _nCols;
    // Output vector of shortest distances to nearest 0 for each cell
    vector<vector<int> > _shortestDistV;
    // 4 directional neighbor offsets from each cell
    vector<pair<int, int> > _nbrOffsetsV;
};
