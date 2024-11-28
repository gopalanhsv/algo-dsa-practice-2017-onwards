// p => grid.size(), q => grid[0].size()
// Time Complexity : O(pq)
// Space Complexity : O(pq)

class Solution {
public:
    int
    minimumObstacles(vector<vector<int>>& grid) {
        // Problem is modeled as a graph wherein each of the grid cells form
        // graph vertices; 4 directional movement from a cell to its (at most) 
        // 4 adjacent neighbors form the graph edges. The graph vertex modelling
        // an empty cell is assigned a cost of 0, that modelling an obstacle cell
        // is assigned a cost of 1. Edges are assigned a cost of 0.
        // The problem then reduces to finding the shortest cost path (i.e. min
        // number of cells with 1 on the path) between the vertices
        // representing the top left cell and bottom right cell.
        
        // One can use either Dijkstra or 0-1 BFS here as due to only 2 costs 0/1
        return minObstaclesViaBFS(grid);
    }
    
private:

    int
    minObstaclesViaBFS(vector<vector<int>>& grid) {
        // Num grid rows/cols
        auto nr = grid.size();
        auto nc = grid[0].size();
        // minDistV(r, c) tracks the min number of obstacles to reach cell(r, c) from cell(0, 0)
        // Init all cells to be a distance of infinity from cell (0, 0)
        vector<vector<int> > minDistV(nr, vector<int>(nc, numeric_limits<int>::max()));
        // Offsets for 4 directional movement from a cell
        vector<pair<int, int> > nbrOffsetV = {
            {0, 1}, {0, -1}, {1, 0}, {-1, 0}
        };

        // Commence BFS from cell (0, 0)
        deque<pair<int, int> > bfsQ;
        bfsQ.push_front({0, 0});
        minDistV[0][0] = grid[0][0];
        while (!bfsQ.empty()) {
            
            // Visit the cell at front of BFS Q
            auto & v = bfsQ.front();
            auto X = v.first;
            auto Y = v.second;
            bfsQ.pop_front();

            // Schedule the valid 4 directional neighbours of visited cell
            // for a 0-1 BFS traversal subsequently
            for (auto & nbrOffset : nbrOffsetV) {
                auto nX = X + nbrOffset.first;
                auto nY = Y + nbrOffset.second;
                if ((nX < 0) || (nY < 0) || (nX >= nr) || (nY >= nc)) {
                    // Skip invalid cells
                    continue;
                }
         
                if (minDistV[X][Y] + grid[nX][nY] < minDistV[nX][nY]) {
                    minDistV[nX][nY] = minDistV[X][Y] + grid[nX][nY];
                    if (0 == grid[nX][nY]) {
                        bfsQ.push_front({nX, nY});
                    } else {
                        bfsQ.push_back({nX, nY});
                    }
                }
            }
        }
        
        return minDistV[nr - 1][nc - 1];
    }
};
