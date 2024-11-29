// p => grid.size(), q => grid[0].size()
// Time Complexity : O(pqlog(pq))
// Space Complexity : O(pq)

class Solution {
public:
    int
    minimumTime(vector<vector<int>>& grid) {
        // Problem is modelled as a graph wherein grid cells form graph vertices
        // while movement between 4 directional adjacent cells form the graph
        // edges with each edge cost being 1 (i.e. 1sec)
        // The problem then reduces to a variant of finding the shortest path
        // in a graph (commencing from the vertex representing the top left cell
        // and terminating at the vertex representing the bottom right cell)

        // (1) Every new second there should be a move from a cell to its adjacent cell
        // (2) A move to a cell with value 'x' is allowed only at time >= 'x'
        // (3) A move from a cell to its 4 directional adjacent neighbor takes 1 sec
        
        // From (1) and (2) it is apparent that if one is in a cell c1 at time 't' and
        // wants to visit an adjacent cell c2 with value 'X' > t + 1; then one has to
        // spend the waiting time till 'X' hopping between cell c1 and adjacent cell
        // from where one arrived to c1. Each hop round trip takes 2 sec
        // (-1 in X - 1 - t accounts for hop time from c1 to c2)
        // => if (X - 1 - t) is odd, then waiting time = X - 1 - t + 1, 
        // => if (X - 1 - t) is even, then waiting time = X - 1 - t
        
        if (0 != grid[0][0]) {
            // Base case of not being allowed in (0, 0) at t = 0 itself
            return -1;
        }
        auto nr = grid.size();
        auto nc = grid[0].size();
        // Cases of not being able to proceed from cell (0, 0) onwards
        if ((nc > 0) && (nr > 0) && (grid[0][1] > 1) && (grid[1][0] > 1)) {
            return -1;
        } else if ((nc == 0) && (nr > 0) && (grid[1][0] > 1)) {
            return -1;
        } else if ((nc > 0) && (nr == 0) && (grid[0][1] > 1)) {
            return -1;
        }
        // Cell visit parameters
        typedef struct _CellVisitInfoT {
            int vTime; // Cell visit time
            int r;
            int c;
        } CellVisitInfoT;
        struct CellVisitInfoCmpObj {
            bool
            operator()(const CellVisitInfoT & c1, const CellVisitInfoT & c2) {
                return c1.vTime > c2.vTime;
            }
        };
        vector<pair<int, int> > nbrOffsetV = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}
        };
        // Dijkstra data structures
        priority_queue<CellVisitInfoT, vector<CellVisitInfoT>, CellVisitInfoCmpObj> spfQ;
        vector<vector<bool> > visitedV(nr, vector<bool>(nc, false));
        // Commence Dijkstra from cell (0, 0) at time t = 0
        spfQ.push({0, 0, 0});
        visitedV[0][0] = true;
        while (!spfQ.empty()) {
            // Visit the cell at top of Dijkstra priority queue
            auto [cellVisitTime, X, Y] = spfQ.top();
            spfQ.pop();
            
            if ((nr - 1 == X) && (nc - 1 == Y)) {
                // Reached destination
                return cellVisitTime;
            }
            
            // Schedule all the unvisited neighbors of current cell being visited
            // for an SPF visit
            for (auto & nbrOffset : nbrOffsetV) {
                auto nX = X + nbrOffset.first;
                auto nY = Y + nbrOffset.second;
                if ((nX >= 0) && (nX < nr) && (nY >= 0) && (nY < nc) && !visitedV[nX][nY]) {
                    // Compute wait time required for cell (nX, nY) visit from (X, Y)
                    int waitTime = 0;
                    int timeDiff = grid[nX][nY] - 1 - cellVisitTime;
                    if (timeDiff > 0) {
                        waitTime = ((timeDiff % 2) == 0) ? timeDiff : timeDiff + 1;
                    }
                    int nbrVisitTime = cellVisitTime + waitTime + 1;
                    // Schedule neighbor for an SPF visit
                    spfQ.push({nbrVisitTime, nX, nY});
                    visitedV[nX][nY] = true;
                }
            }
        }
        
        return -1;
    }
};
