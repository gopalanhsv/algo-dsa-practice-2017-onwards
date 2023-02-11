class Solution {
    
    typedef enum _ColorT {
        RED = 0,
        BLUE = 1
    } ColorT;
    
public:
    vector<int>
    shortestAlternatingPaths(
        int n, vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {

        createGraph(red_edges, blue_edges);
        
        // Commence a BFS from vertex 0 and attempt to visit all reachable
        // vertices following only alternating color edges
        return alternatingPathsViaBfs(n);
    }
    
private:
    
    void
    createGraph(vector<vector<int>>& red_edges, vector<vector<int>>& blue_edges) {
        
        // Iterate through all red edges and populate the adjacency list table
        for (auto & re : red_edges) {
            auto s = re[0];
            auto d = re[1];
            _adjListTbl[s].emplace_back(pair<int, int>(d, RED));
        }
        
        // Iterate through all blue edges and populate the adjacency list table
        for (auto & be : blue_edges) {
            auto s = be[0];
            auto d = be[1];
            _adjListTbl[s].emplace_back(pair<int, int>(d, BLUE));
        }
    }
    
    vector<int>
    alternatingPathsViaBfs(int n) {
        
        // All shortest paths initialized to -1
        vector<int> shortestPathLenV(n, -1);
        vector<vector<bool> > visitedV(2, vector<bool>(n, false));
        
        // The second parameter below in BFS Q pair represents the edge color via which
        // the first parameter i.e. vertex is reached
        queue<pair<int, int> > bfsQ;
        typedef queue<pair<int, int> >::size_type qSzT;
        
        // Commence BFS
        // Enqueue vertex 0 to BFS Q (both red and blue colors enqueued aseco
        // this is start vertex and can be reachable from both colors initially)
        bfsQ.push(pair<int, int>(0, RED));
        bfsQ.push(pair<int, int>(0, BLUE));
        visitedV[RED][0] = true;
        visitedV[BLUE][0] = true;
        // The BFS level would also be the shortest path length
        int bfsLevel = 0; 
        int nVerticesVisited = 0;
        while (!bfsQ.empty()) {
            
            // Visit all vertices at current level
            qSzT currLvlSz = bfsQ.size();
            for (qSzT i = 0; i != currLvlSz; ++i) {
                
                // Dequeue vertex at front of BFS Q. Visit it and schedule
                // its unvisited neighbors for a BFS visit in next iteration
                // vcp => vertex color pair
                auto & vcp = bfsQ.front();
                int v = vcp.first;
                int color = vcp.second;
                bfsQ.pop();
                
                // Update the shortest path for above visited vertex
                if (shortestPathLenV[v] == -1) {
                    // Code for early termination
                    ++nVerticesVisited;
                    shortestPathLenV[v] = bfsLevel;
                    if (nVerticesVisited == n) {
                        return shortestPathLenV;
                    }
                }
                
                // Unvisited Neighbour vertices of above vertex reachable
                // by an edge of different color are scheduled for a BFS visit
                auto & nbrV = _adjListTbl[v];
                for (auto & vertexColorP : nbrV) {
                    // Nbr vertex and edge color
                    int nv = vertexColorP.first;
                    int eColor = vertexColorP.second;
                    if (eColor != color && !visitedV[eColor][nv]) {
                        bfsQ.push(pair<int, int>(nv, eColor));
                        visitedV[eColor][nv] = true;
                    }
                }
            }
            
            // Increment BFS level
            ++bfsLevel;
        }
        
        return shortestPathLenV;
    }
    
    // Data members
    
    // Graph adjacency list mapping each source vertex to the appropriate
    // tuple of destination vertex, edge color for each vertex
    unordered_map<int, vector<pair<int, int> > > _adjListTbl;
};
