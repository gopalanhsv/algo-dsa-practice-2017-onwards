// nr => grid rows, nc => grid cols
// Time complexity : O(nr x nc)
// Space complexity : O(nr x nc) / max BFS Q len

class Solution {
public:
    int
    shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        
        // Shortest path length is computed via a BFS traversal commencing
        // from source cell and terminating at destination cell; with the
        // traversal path restricted along the cells with value 0 at each hop
        
        // Num rows & cols
        int nr = grid.size();
        int nc = grid[0].size();
        
        if (grid[0][0] == 1 || grid[nr - 1][nc - 1] == 1) {
            // Source/destination cell not in traversal path
            return -1;
        }
        
        // 8 directional neighbour offsets for the BFS traversal
        vector<int> XNbrOffsetsV = {-1, -1, -1, 0, 0, 1, 1, 1};
        vector<int> YNbrOffsetsV = {-1, 0, 1, -1, 1, -1, 0, 1};
        
        // Commence BFS from source cell(0, 0)
        queue<int> bfsQX;
        queue<int> bfsQY;
        typedef queue<int>::size_type qSzT;
        
        int pathLen = 0;
        bfsQX.push(0);
        bfsQY.push(0);
        // Grid itself is used to mark a cell as visited by setting to 1
        grid[0][0] = 1;
        
        while (!bfsQX.empty()) {
            
            // Increment path length as we are moving to the next cell
            ++pathLen;
            
            // Dequeue and visit all the cells at the current level. Setup their
            // appropriate neighbours for a BFS visit in succeeding iterations
            qSzT qSz = bfsQX.size();
            for (int i = 0; i != qSz; ++i) {
                // Dequeue and visit the cell at front of Q
                auto X = bfsQX.front();
                bfsQX.pop();
                auto Y = bfsQY.front();
                bfsQY.pop();
            
                if (X == nr - 1 && Y == nc - 1) {
                    // Destination hit
                    return pathLen;
                }
                
                // Setup all the unvisited valid 8-directional neighbour cells of
                // dequeued cells for a BFS visit in next iteration
                for (int i = 0; i != 8; ++i) {
                    // Neighbour cell coords
                    int nX = X + XNbrOffsetsV[i];
                    int nY = Y + YNbrOffsetsV[i];
                    
                    if (nX >= 0 && nX < nr && nY >= 0 && nY < nc && grid[nX][nY] == 0) {
                        bfsQX.push(nX);
                        bfsQY.push(nY);
                        // Mark neighbour cell as visit to avoid multiple enqueuing
                        grid[nX][nY] = 1;
                    }
                }
            }
        }
        
        // No clear path from source to destination
        return -1;
    }
};
