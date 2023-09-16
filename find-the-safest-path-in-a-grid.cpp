// nr => num rows, nc => num cols
// Time complexity : O(nr x nc) + O((nr x nc)log(nr + nc))
// Space complexity : O(nr x nc)
class Solution {
public:
    int
    maximumSafenessFactor(vector<vector<int>>& grid) {
        
        // Initialize
        init(grid);
        
        if ((1 == grid[0][0]) || (1 == grid[_nr - 1][_nc - 1])) {
            // Base case of either the start/ends having a thief
            return 0;
        }
        
        // Compute the manhattan distance from each cell to the nearest thief via BFS
        cellSafenessFactorViaBfs(grid);
        
        // Determine the maximum possible path safeness factor via binary search
        return maxPathSafenessFactorViaBinarySearch(grid);
        
    }
    
private:

    void
    init(vector<vector<int>>& grid) {
        _nr = grid.size();
        _nc = grid[0].size();
        _nbrOffsetsV = {
            {0, 1}, {0, -1}, {1, 0}, {-1, 0}
        };
    }
    
    void
    cellSafenessFactorViaBfs(vector<vector<int>>& grid) {
        
        // Commence a simultaneous BFS traversal from each of the cells in
        // which thieves are places. The BFS level when the traversal first
        // visits a cell would be the manhattance distance to teh closest thief
        _safenessFactorTbl.resize(_nr, vector<int>(_nc, numeric_limits<int>::max()));
        queue<pair<int, int> > bfsQ;
        typedef queue<pair<int, int> >::size_type qSzT;
        vector<vector<bool> > visitedV(_nr, vector<bool>(_nc, false));
        // Add all the thieves to the BFS Q
        for (auto r = 0; r != _nr; ++r) {
            for (auto c = 0; c != _nc; ++c) {
                if (1 == grid[r][c]) {
                    visitedV[r][c] = true;
                    bfsQ.push({r, c});
                }
            }
        }
        // Commence BFS
        int currSafenessFactor = 0;
        while (!bfsQ.empty()) {
            auto currLvlSz = bfsQ.size();
            // Visit all the cells at the current level and update the
            // distance to the nearest thief
            for (auto i = 0; i != currLvlSz; ++i) {
                // Dequeue cell at front of BFS Q and visit it
                auto & cell = bfsQ.front();
                // Cell co-ords
                auto X = cell.first;
                auto Y = cell.second;
                bfsQ.pop();
                // Update cell safeness factor
                _safenessFactorTbl[X][Y] = currSafenessFactor;
                // Setup all the unvisited neighbors of the dequeued cell
                // for a BFS visit in the subsequent iteration
                for (auto & nbrOffset : _nbrOffsetsV) {
                    auto nX = X + nbrOffset.first;
                    auto nY = Y + nbrOffset.second;
                    
                    if ((nX >= 0) && (nY >= 0) && (nX < _nr) && (nY < _nc) &&
                        !visitedV[nX][nY]) {
                        bfsQ.push({nX, nY});
                        visitedV[nX][nY] = true;
                    }
                }    
            }
            ++currSafenessFactor;
        }
    }
    
    bool
    pathPresentWithSafenessFactor(vector<vector<int>>& grid, int minSafenessFactor) {

        // Determine if a path is possible from source to destination only via
        // cells with the specified minimum safeness factor
        // Destination cell co-ords
        auto dstX = _nr - 1;
        auto dstY = _nc - 1;
        if ((_safenessFactorTbl[0][0] < minSafenessFactor) ||
            (_safenessFactorTbl[dstX][dstY] < minSafenessFactor)) {
            // Path termination points break the safeness constraint => path impossible
            return false;
        }
        
        // Commence a BFS traversal from source cell to destination
        vector<vector<bool> > visitedV(_nr, vector<bool>(_nc, false));
        queue<pair<int, int> > bfsQ;
        bfsQ.push({0, 0});
        visitedV[0][0] = true;

        while (!bfsQ.empty()) {
            auto currLvlSz = bfsQ.size();
            // Visit all the cells in the BFS Q at the current level
            for (auto i = 0; i != currLvlSz; ++i) {
                // Dequeue and visit the cell at BFS Q front
                auto & cell = bfsQ.front();
                auto X = cell.first;
                auto Y = cell.second;
                bfsQ.pop();
                
                if ((X == dstX) && (Y == dstY)) {
                    // Hit destination from source => path exists with required safeness
                    return true;
                }
                
                // Schedule all the unvisited neighour cells of dequeued cell which satisfy
                // the path minimum safeness constraint for a BFS visit in the succeeding iteration
                for (auto & nbrOffset : _nbrOffsetsV) {
                    auto nX = X + nbrOffset.first;
                    auto nY = Y + nbrOffset.second;
                    
                    if ((nX >= 0) && (nY >= 0) && (nX <= dstX) && (nY <= dstY) &&
                        !visitedV[nX][nY] && (_safenessFactorTbl[nX][nY] >= minSafenessFactor)) {
                        bfsQ.push({nX, nY});
                        visitedV[nX][nY] = true;
                    }
                }
            }
        }
        
        return false;
    }
    
    int
    maxPathSafenessFactorViaBinarySearch(vector<vector<int>>& grid) {
        // Mininum possible safeness for a path from source to destination
        // would be when the path passes over a cell with a thief
        int minPossiblePathSF = 0;
        // Maximum possible safeness for a path from source to destination
        // would be when the path hugs the leftmost col and bottom rows with
        // a single thief at upper right cell
        int maxPossiblePathSF = _nr + _nc;
        
        // Execute a binary search for existence path with maximum possible
        // safeness in the range [lo, hi]
        
        int lo = minPossiblePathSF;
        int hi = maxPossiblePathSF;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2 + 1;
            if (pathPresentWithSafenessFactor(grid, mid)) {
                // 'mid' is now the lower bound on maximum safeness factor
                // Search for paths with higher safeness factor
                lo = mid;
            } else {
                // 'mid' is an beyond the upper bound on maximum safeness factor
                // Search for paths with lower safeness factor
                hi = mid - 1;
            }
        }
        
        // 'lo' and 'hi' converge in a pincer movement to the maximum safeness factor
        // which allows a path from source to destination
        return lo;
    }
    
    // Data members
    // Num rows and cols
    int _nr;
    int _nc;
    // _safenessFactorTbl[r][c] is the manhattan distance from cell (r, c) to nearest thief
    vector<vector<int> > _safenessFactorTbl;
    // 4 directional movement offsets from each cell
    vector<pair<int, int> > _nbrOffsetsV;
};
