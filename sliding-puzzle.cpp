// p => board.size(), q => board[0].size()
// Time Complexity : 
// Total of !(pq) states possible. From each state in BFS - a max of 4 states get explored
// => 4!(pq) iterations => TC is O(!(pq))
// Space Complexity : O(!(pq))

class Solution {
public:
    int
    slidingPuzzle(vector<vector<int>>& board) {
        // Problem is modeled as graph wherein graph vertices represent the board
        // states and graph edges represent the direct transitions from a particular
        // board state to the next possible state(s). So each move is modeled by a
        // transition between vertices, i.e. edge
        
        // Then the problem reduces to finding the minimum number of edges between
        // the initial board state and the final required board state; which is easily
        // achievable via BFS

        // Each board state consists of a 2 x 3 array of numerals 0-5. This is
        // reduced to a string of length 6; e.g. the board state [[1, 2, 3], [4, 0, 5]]
        // is reduced to string representation "123405"
        init(board);

        // Exec BFS to determine min moves between initial and final state
        return doBFS();
    }
    
private:

    void
    init(vector<vector<int>>& board) {

        for (auto & rowV : board) {
            for (auto & tileLabel : rowV) {
                _startState += to_string(tileLabel);
            }
        }

        // Build the transition table for each location of 0 (as only
        // 0 can be swapped/moved)
        _transitionTbl = {
            {1, 3}, // 0 at (0, 0) can be swapped with elem at (0, 1), (1, 0) 
            {0, 2, 4}, // 0 at (0, 1) can be swapped with elem at (0, 0), (0, 2), (1, 1) 
            {1, 5}, // 0 at (0, 2) can be swapped with elem at (0, 1), (1, 2) 
            {0, 4}, // 0 at (1, 0) can be swapped with elem at (1, 1), (0, 0)
            {1, 3, 5}, // 0 at (1, 1) can be swapped with elem at (1, 0), (1, 2), (0, 1) 
            {2, 4} // 0 at (1, 2) can be swapped with elem at (0, 2), (1, 1) 
        };
    }

    int
    doBFS() {
        // The final state representing solved puzzle is [[1, 2, 3], [4, 5, 0]]
        // i.e. string "123450"
        string finalState("123450");
        
        queue<string> bfsQ;
        unordered_set<string> visitedV;
        // Commence BFS
        bfsQ.push(_startState);
        visitedV.insert(_startState);

        int nHops = 0;
        while (!bfsQ.empty()) {
            auto currLvlSz = bfsQ.size();
            // Visit all the vertices at the current level
            for (auto i = 0; i != currLvlSz; ++i) {
                // Dequeue and visit the vertex at front of Q
                auto currState = bfsQ.front();
                bfsQ.pop();
                
                if (currState == finalState) {
                    // Reached the final vertex 
                    return nHops;
                }
                
                // Schedule all the unvisited neighbours of current vertex
                // (i.e. those vertices which can be reached via swapping 0)
                // for a BFS traversal in the subsequent iteration
                // Location of 0 in current state
                auto currZeroIdx = currState.find('0');
                // Possible next locations of 0 from current
                auto & nextZeroIdxV = _transitionTbl[currZeroIdx];
                // Generate all possible next vertices
                for (auto & nextZeroIdx : nextZeroIdxV) {
                    // Generate next possible state by swapping current 0 with
                    // element in the next possible 0 locations
                    auto nextState = currState;
                    swap(nextState[nextZeroIdx], nextState[currZeroIdx]);
                    
                    // Schedule the next state for BFS visit if not visited yet
                    if (visitedV.find(nextState) == visitedV.end()) {
                        bfsQ.push(nextState);
                        visitedV.insert(nextState);
                    }
                }
            }
            
            // Done with all transitions at current level
            ++nHops;
        }
        
        // No path possible from initial to final state => board unsolvable
        return -1;
    }
    
    // Data members
    string _startState;

    // Table capturing feasible transitions for 0 (as only 0 can be swapped
    // with its board neighbours), for each location of 0 in the state.
    // Transitions are for string representation
    vector<vector<int> > _transitionTbl;    
};
