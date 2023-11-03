// X = max elevation in grid
// nr, nc => num grid rows, cols
// Time complexity : O((nr x nc)logX)
// Space complexity : O(nr x nc)

class Solution {
public:
    int
    swimInWater(vector<vector<int>>& grid) {
        
        // Num rows and cols
        _n = grid.size(); 
        _nbrOffsetsV = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}  
        };
        
        return leastTimeToSwimViaBinarySearch(grid);
    }
    
private:
    
    int
    leastTimeToSwimViaBinarySearch(vector<vector<int>>& grid) {
        // Minimum time at which destination cell can be reached
        // from source would be 0 (when all cells at same elevation)
        int minTime = 0;
        // Maximum time at which destination cell can be reached
        // from source would be the elevation of point with maximum
        // value 'x', because at time 'x' all cells will be at same
        // elevation and one can quickly swim across from source to destination
        int maxTime = 0;
        for (int r = 0; r != _n; ++r) {
            for (int c = 0; c != _n; ++c) {
                maxTime = max(maxTime, grid[r][c]);
            }
        }
        
        // Execute a binary search in the closed range of possible 
        // times [minTime, maxTime] to find the minimum time 'x' s.t 
        // at time 'x' it is possible to swim from source cell (0, 0)
        // to destination cell (_n - 1, _n - 1). At time 'x' water depth
        // at all places is 'x'
        int l = minTime, r = maxTime;
        while (l < r) {
            int mid = l + (r - l) / 2;
            //if (possibleToSwimTillDestinationViaBFS(grid, mid)) {
            if (possibleToSwimTillDestinationViaDFS(grid, mid)) {
                // Possible to reach destination from source with a 
                // water level of 'mid'. Check if destination
                // reachable with lower water levels/time
                r = mid;
            } else {
                // Impossible to reach destination from source with a 
                // water level of 'mid'. Check if destination reachable
                // with higher water levels/time
                l = mid + 1;
            }
        }
        
        // Search ends when l == r with l & r converging in a pincer
        // movement; and r being the min water level at which it is
        // possible to reach destination from source
        return l;
    }
    
    bool
    possibleToSwimTillDestinationViaBFS(vector<vector<int> > & grid, int waterLevel) {
        
        // Check via BFS if there is path from source cell (0, 0) to destination
        // cell (_n - 1, _n - 1) when the water level everywhere is as specified
        // (at time 'waterLevel')
        
        if (grid[0][0] > waterLevel) {
            // Start point is at a much higher elevation than current water
            // level, so cannot commence swimming
            return false;
        }
        
        queue<pair<int, int> > bfsQ;
        typedef queue<pair<int, int> >::size_type qSzT;
        vector<vector<bool> > visitedV(_n, vector<bool>(_n, false));
        // Add source to BFS Q and commence BFS
        bfsQ.push(pair<int, int>(0, 0));
        visitedV[0][0] = true;
        while (!bfsQ.empty()) {
            // Visit all cells in BFS queue at the current level
            qSzT currLvlSz = bfsQ.size();
            for (qSzT i = 0; i != currLvlSz; ++i) {
                // Dequeue the cell at front of BFS Q
                auto & cell = bfsQ.front();
                int X = cell.first;
                int Y = cell.second;
                bfsQ.pop();
                
                if (X == _n - 1 && Y == _n - 1) {
                    // Managed to reach destination cell
                    return true;
                }
                
                // From the cell visited above, visit all unvisited
                // neighbors in 4 directions which can be reached 
                // at the given water level
                for (auto & nbrOffs : _nbrOffsetsV) {
                    // Neighbour cell coords
                    int nX = X + nbrOffs.first;
                    int nY = Y + nbrOffs.second;
                    // Only valid unvisited neighbours which are filled
                    // with water at this time (i.e have elevation l.e given
                    // water level)
                    if (nX >= 0 && nY >= 0 && nX < _n && nY < _n &&
                        !visitedV[nX][nY] && grid[nX][nY] <= waterLevel) {
                        bfsQ.push(pair<int, int>(nX, nY));
                        visitedV[nX][nY] = true;
                    }
                }
            }
        }
        
        // Not possible to swim from source to destination at given water level
        return false;
    }
    
    bool
    possibleToSwimTillDestinationViaDFS(vector<vector<int> > & grid, int waterLevel) {
        
        // Check via DFS if there is path from source cell (0, 0) to destination
        // cell (_n - 1, _n - 1) when the water level everywhere is as specified
        // (at time 'waterLevel')
        
        if (grid[0][0] > waterLevel) {
            // Start point is at a much higher elevation than current water
            // level, so cannot commence swimming
            return false;
        }
        
        stack<pair<int, int> > dfsStk;
        vector<vector<bool> > visitedV(_n, vector<bool>(_n, false));
        // Add source to DFS stack and commence DFS
        dfsStk.push(pair<int, int>(0, 0));
        visitedV[0][0] = true;
        while (!dfsStk.empty()) {
            // Visit cell at top of DFS stack and pop it off
            auto & cell = dfsStk.top();
            int X = cell.first;
            int Y = cell.second;
            dfsStk.pop();
                
            if (X == _n - 1 && Y == _n - 1) {
                // Managed to reach destination cell
                return true;
            }
                
            // From the cell visited above, visit all unvisited
            // neighbors in 4 directions which can be reached 
            // at the given water level
            for (auto & nbrOffs : _nbrOffsetsV) {
                // Neighbour cell coords
                int nX = X + nbrOffs.first;
                int nY = Y + nbrOffs.second;
                // Only valid unvisited neighbours which are filled
                // with water at this time (i.e have elevation l.e given
                // water level)
                if (nX >= 0 && nY >= 0 && nX < _n && nY < _n &&
                    !visitedV[nX][nY] && grid[nX][nY] <= waterLevel) {
                    dfsStk.push(pair<int, int>(nX, nY));
                    visitedV[nX][nY] = true;
                }
            }
        }
        
        // Not possible to swim from source to destination at given water level
        return false;
    }
    
    // Data
    // Num rows and cols
    int _n;
    // 4 direction neighbor offsets from any grid cell
    vector<pair<int, int> > _nbrOffsetsV;
};
