// nr => num rows, nc => num cols in grid heights
// X => max diff between any 2 elements in heights
// Time complexity : O((nr x nc) logX )
// Space complexity : O(nr x nc)

class Solution {
    
public:
    int
    minimumEffortPath(vector<vector<int>>& heights) {
        _nr = heights.size();
        _nc = heights[0].size();
        // From a cell one can move either up/down/left/right
        _nbrOffsetsV = {
            {0, 1}, {0, -1}, {1, 0}, {-1, 0}
        };

        return minEffortPathViaBinarySearch(heights);
    }

private:

    int
    minEffortPathViaBinarySearch(vector<vector<int> >& heights) {
        
        // Min value of route effort from source to destination would be
        // when the route has a path s.t adjacent cells have same value
        int minRouteEffortVal = 0;
        // Max value of route effort from source to destination would be
        // when the route has a path s.t adjacent cells max difference in
        // their heights (can be taken as 10^6 or scan the grid and use
        // the diff between min and max valued heights)
        int maxRouteEffortVal = 1000000;
        
        // Exec a binary search in the range [minRouteEffortVal, maxRouteEffortVal] to find the
        // min effort required to travel from source (0, 0) to destination(_nr - 1, _nc - 1)
        int l = minRouteEffortVal;
        int r = maxRouteEffortVal;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (dfsRoutePossibleWithGivenEffort(heights, mid)) {
                // Route with an effort value of 'mid' would form the upper bound;
                // search for routes with lower effort values
                r = mid;
            } else {
                // Route with an effort value of 'mid' not feasible;
                // search for routes with higher effort values
                l = mid + 1;
            }
        }
        
        // Binary search converges at l == r. 'l' & 'r' move in a pincer movement
        // converging at a value of 'mid' which becomes the minimum possible value
        // of route effort for which there is a route from source to destination 
        // Range of route efforts for which a path exists from source to destination
        // is reduced gradually in a pincer move with l and r converging to same value
        // at the end of search
        return l;
    }

    bool
    bfsRoutePossibleWithGivenEffort(vector<vector<int>>& heights, int effortVal) {
        // Check via BFS if there exists a route from cell (0, 0) to (_nr - 1, _nc - 1)
        // with the given effort value constraint
        
        vector<vector<bool> > visitedV(_nr, vector<bool>(_nc, false));
        queue<pair<int, int> > bfsQ;
        typedef queue<pair<int, int> >::size_type qSzT;
        // Commence BFS from source cell
        bfsQ.push({0, 0});
        visitedV[0][0] = true;
        while (!bfsQ.empty()) {
            
            // Visit all cells at the current BFS level
            qSzT currLvlSz = bfsQ.size();
            for (int i = 0; i != currLvlSz; ++i) {
                
                // Dequeue and visit the cell at Q front 
                auto & cell = bfsQ.front();
                // Nbr coords
                int X = cell.first;
                int Y = cell.second;
                bfsQ.pop();
                
                if (X == _nr - 1 && Y == _nc - 1) {
                    // Reached the destination cell from source satisfying all route constraints
                    return  true;
                }
                
                // Set up all the immediate valid unvisited neighbour cells of dequeued cell
                // satisfying the route effort constraint for a BFS visit next BFS iteration
                int currCellHt = heights[X][Y];
                for (auto & nbrOffs : _nbrOffsetsV) {
                    auto nX = X + nbrOffs.first;
                    auto nY = Y + nbrOffs.second; 
                    if (nX >= 0 && nY >= 0 && nX < _nr && nY < _nc &&
                        !visitedV[nX][nY] &&
                        abs(heights[nX][nY] - currCellHt) <= effortVal) {
                        bfsQ.push({nX, nY});
                        visitedV[nX][nY] = true;
                    }
                }
            }
        }
        return false;
    }
    
    bool
    dfsRoutePossibleWithGivenEffort(vector<vector<int>>& heights, int effortVal) {
        
        // Check via DFS if there exists a route from cell (0, 0) to (_nr - 1, _nc - 1)
        // with the given effort value constraint
        vector<vector<bool> > visitedV(_nr, vector<bool>(_nc, false));
        stack<pair<int, int> > dfsStk;
        
        // Commence DFS from source cell
        dfsStk.push({0, 0});
        visitedV[0][0] = true;
        while (!dfsStk.empty()) {
            // Pop off and visit the cell at top of stack
            auto & cell = dfsStk.top();
            // Nbr coords
            int X = cell.first;
            int Y = cell.second;
            dfsStk.pop();
                
            if (X == _nr - 1 && Y == _nc - 1) {
                // Reached the destination cell from source satisfying all route constraints
                return  true;
            }
                
            // Set up all the immediate valid unvisited neighbour cells of dequeued cell satisfying
            // the route effort constraints for a DFS visit in the subsequent DFS iterations
            int currCellHt = heights[X][Y];
            for (auto & nbrOffs : _nbrOffsetsV) {
                auto nX = X + nbrOffs.first;
                auto nY = Y + nbrOffs.second;
                    
                if (nX >= 0 && nY >= 0 && nX < _nr && nY < _nc &&
                    !visitedV[nX][nY] &&
                    abs(heights[nX][nY] - currCellHt) <= effortVal) {
                    dfsStk.push({nX, nY});
                    visitedV[nX][nY] = true;
                }
            }
        }
        
        return false;
    }
    
    // Data members
    // Num rows and cols
    int _nr;
    int _nc;
    // 4 directional offsets from a cell to its immediate neighbours
    vector<pair<int, int> > _nbrOffsetsV;
};
