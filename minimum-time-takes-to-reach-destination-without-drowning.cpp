// nr => num rows, nc => num cols
// Time complexity : O(nr x nc)
// Space complexity : O(nr x nc)
class Solution {
public:
    int
    minimumSeconds(vector<vector<string>>& land) {
        init(land);
        
        // Execute a BFS traversal from each of the flooded cells simultaneously
        // to determine the time at which each cell in the grid gets flooded
        floodViaBfs(land);
        
        // Execute a BFS traversal from start cell to destination following the path
        // which does not get flooded during traversal time ticks to get the minimum
        // time to hit teh destination cell
        return spLenViaBfs(land);
    }
    
private:
    
    void
    init(vector<vector<string>>& land) {
        // Num grid rows & cols
        _nr = land.size();
        _nc = land[0].size();
        // Movement offset from a cell to its neighbour
        _nbrOffsetsV = {
            {0, -1}, {0, 1}, {-1, 0}, {1, 0}  
        };
    }
    
    void
    floodViaBfs(vector<vector<string>>& land) {
        queue<pair<int, int> > bfsQ;
        vector<vector<bool> > visitedV(_nr, vector<bool>(_nc, false));
        // All cells are temporarily marked as to be flooded at +infinity initially
        _cellFloodingTimeTbl.resize(_nr, vector<int>(_nc, numeric_limits<int>::max()));
        
        // Iterate over each land cell
        for (auto r = 0; r != _nr; ++r) {
            for (auto c = 0; c != _nc; ++c) {
                auto & cellVal = land[r][c];
                if (("X" == cellVal) || ("D" == cellVal)) {
                    // Stone cells marked as visited (as these wont be flooded)
                    // Destination cell marked as visited (as it wont be flooded)
                    visitedV[r][c] = true;
                } else if ("*" == cellVal) {
                    // Flooded cells added to BFS Q and marked as visited
                    visitedV[r][c] = true;
                    bfsQ.push({r, c});
                }
            }
        }
        
        // Commence BFS and populate the time required to flood each empty cell
        // of the grid for the first time
        auto currTime = 0;
        while (!bfsQ.empty()) {
        
            // Visit all the cells which are scheduled to be flooded at the current time instance 'currTime'
            auto qSz = bfsQ.size();
            for (auto i = 0; i != qSz; ++i) {
                // Visit and dequeue the cell at front of BFS Q
                auto & cell = bfsQ.front();
                // Cell coords
                auto X = cell.first;
                auto Y = cell.second;
                bfsQ.pop();
                // Flood the cell
                _cellFloodingTimeTbl[X][Y] = currTime;
                // Visit all the valid unvisited/non-flooded adjacent empty cells/neighbours of
                // dequeued cell and schedule them for a BFS visit (flooding) in the next iteration
                for (auto & nbrOffset : _nbrOffsetsV) {
                    // Neighbour cell co-ords
                    auto nX = X + nbrOffset.first;
                    auto nY = Y + nbrOffset.second;
                    
                    if ((nX >= 0) && (nY >= 0) && (nX < _nr) && (nY < _nc) && !visitedV[nX][nY]) {
                        // Valid unflooded empty neighbor cell (nX, nY) scheduled for flooding
                        // in next BFS iteration
                        bfsQ.push({nX, nY});
                        visitedV[nX][nY] = true;
                    }
                }
            }
            
            // Advance time tick for next iteration
            ++currTime;
        }
    }
    
    int
    spLenViaBfs(vector<vector<string>>& land) {
        queue<pair<int, int> > bfsQ;
        vector<vector<bool> > visitedV(_nr, vector<bool>(_nc, false));        
        // Iterate over each cell
        for (auto r = 0; r != _nr; ++r) {
            for (auto c = 0; c != _nc; ++c) {
                auto & cellVal = land[r][c];
                if ("X" == cellVal) {
                    // Stone cells marked as visited (as these wont be explored)
                    visitedV[r][c] = true;
                } else if ("S" == cellVal) {
                    // Start cell added to BFS Q and marked as visited
                    visitedV[r][c] = true;
                    bfsQ.push({r, c});
                }
            }
        }
        
        // Commence BFS
        auto currTime = 0;
        while (!bfsQ.empty()) {
        
            // Visit all the cells which are scheduled to be explored at the current time instance 'currTime'
            auto qSz = bfsQ.size();
            for (auto i = 0; i != qSz; ++i) {
                // Visit and dequeue the cell at front of BFS Q
                auto & cell = bfsQ.front();
                // Cell coords
                auto X = cell.first;
                auto Y = cell.second;
                bfsQ.pop();
                
                if (_cellFloodingTimeTbl[X][Y] <= currTime) {
                    // Cell (X, Y) cannot be visited as it is flooded by the
                    // time exploration traversal reaches it
                    continue;
                }
                
                if (land[X][Y] == "D") {
                    // Hit the destination
                    return currTime;
                }
    
                // Schedule all the valid unvisited/non-flooded adjacent empty/destination cells/neighbours of
                // dequeued cell and schedule them for a BFS exploration in the next iteration
                for (auto & nbrOffset : _nbrOffsetsV) {
                    // Neighbour cell co-ords
                    auto nX = X + nbrOffset.first;
                    auto nY = Y + nbrOffset.second;
                    
                    if ((nX >= 0) && (nY >= 0) && (nX < _nr) && (nY < _nc) && !visitedV[nX][nY]) {
                        // Valid unvisited empty neighbor cell (nX, nY) scheduled for exploration
                        // in next BFS iteration
                        bfsQ.push({nX, nY});
                        visitedV[nX][nY] = true;
                    }
                }
            }
            
            // Advance time tick for next iteration
            ++currTime;
        }
        
        // Not possible to reach destination cell
        return -1;
    }
    
    // Data members
    // Num rows and cols
    int _nr;
    int _nc;
    // Allowable movement direction offsets from a cell to adjacent cells
    vector<pair<int, int> > _nbrOffsetsV;
    // _cellFloodingTimeTbl[r][c] is the earliest time at which a cell gets flooded
    vector<vector<int> > _cellFloodingTimeTbl;
};
