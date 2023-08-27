// n => arr.size()
// DFS & BFS
// Time complexity : O(n)
// Space complexity : O(n)

class Solution {
public:
    bool
    canReach(vector<int>& arr, int start) {
        _arrSz = arr.size();
        if ((start < 0) || (start > _arrSz)) {
            // Start location beyond array bounds
            return false;
        }
        
        // Use DFS/BFS to explore all reachable locations commencing
        // from 'start' till an index with a value of '0' is hit
        //return canReachViaDFS(arr, start);
        return canReachViaBFS(arr, start);
    }
    
private:
    
    bool
    indexWithVal0ReachableDfsHelper(vector<int>& arr, int currIdx) {
        if ((currIdx < 0) || (currIdx >= _arrSz)) {
            // Current location is beyond array bounds and hence an index with
            // value 0 is unreachable from current location
            return false;
        }

        // Value at current location 'currIdx'
        auto & currIdxVal = arr[currIdx];
        if (0 == currIdxVal) {
            // Reached current location with value 0
            return true;
        }
        
        if (_visitedV[currIdx]) {
            // Current index was explored earlier. Prevent
            // self-loops by halting the exploration here
            return false;
        } 
        // Mark current position as visited to prevent self-loops
        _visitedV[currIdx] = true;
        
        // Candidate positions reachable from current position
        auto nextIdx1 = currIdx + arr[currIdx];
        auto nextIdx2 = currIdx - arr[currIdx];
        // Explore via DFS if 0 is reachable via any of the candidate positions
        return 
            (indexWithVal0ReachableDfsHelper(arr, nextIdx1) ||
             indexWithVal0ReachableDfsHelper(arr, nextIdx2));
    }
    
    bool
    canReachViaDFS(vector<int>& arr, int start) {
        _visitedV.resize(_arrSz, false);
        return indexWithVal0ReachableDfsHelper(arr, start);
    }
    
    bool
    canReachViaBFS(vector<int>& arr, int start) {
        
        _visitedV.resize(_arrSz, false);
        
        queue<int> bfsQ;
        // Commence BFS exploration from 'start' location
        bfsQ.push(start);
        _visitedV[start] = true;
        while (!bfsQ.empty()) {
            auto currLvlSz = bfsQ.size();
            // Visit each of the array locations at the current level (i.e at
            // the same number of hops from start location)
            for (auto i = 0; i != currLvlSz; ++i) {
                
                // Dequeue and visit the array index at start of BFS Q
                auto currIdx = bfsQ.front();
                bfsQ.pop();
                
                if (0 == arr[currIdx]) {
                    // O val element hit
                    return true;
                }
                
                // Set up the valid unvisited indices which can be reached from the
                // current position for a BFS traversal in the subsequent iteration
                auto nextIdx1 =  currIdx + arr[currIdx];
                auto nextIdx2 =  currIdx - arr[currIdx];
                if ((nextIdx1 >= 0) && (nextIdx1 < _arrSz) && !_visitedV[nextIdx1]) {
                    bfsQ.push(nextIdx1);
                    _visitedV[nextIdx1] = true;
                }
                if ((nextIdx2 >= 0) && (nextIdx2 < _arrSz) && !_visitedV[nextIdx2]) {
                    bfsQ.push(nextIdx2);
                    _visitedV[nextIdx2] = true;
                }
            }
        }
        
        return false;
    }

    // Data members
    // Array size
    int _arrSz;
    // Tracks visited indices during BFS/DFS
    vector<bool> _visitedV;
};
