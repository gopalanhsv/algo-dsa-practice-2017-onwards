class Solution {
public:
    int
    minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        // Construct an undirected graph using the edges
        
        // Commence DFS from vertex 0. This will visit all the apples
        // which can be reached from vertex 0. On the DFS return/backtrack
        // path from vertices back towards vertex 0; keep track of
        // total number of edges on the path which lead to apple vertices
        // while ignoring edges on the path which don't lead to apple
        // vertices
        // Each such edge on the path leading to apple vertices has to be
        // traversed twice. Sot twice the number of such edges will give
        // the minimum time to collect each apple and return to vertex 0
        
        initGraph(n, edges);
        return minTime(hasApple);
    }
    
private:
    
    void
    initGraph(int n, vector<vector<int>>& edges) {
        // All vertices marked unvisited initially
        _visited.resize(n, false);
        
        // Iterate through all edges and build the graph adjacency list
        for (auto & e : edges) {
            // Edge source and destination endpoints
            auto & s = e[0];
            auto & d = e[1];
            // Add edge vertices to graph
            _graphAdjList[s].emplace_back(d);
            _graphAdjList[d].emplace_back(s);
        }
    }
    
    int
    dfs(int v, vector<bool>& hasAppleV) {
        
        // Mark this vertex as visited
        _visited[v] = true;
        
        // Neighbour vertices of current vertex
        auto & nvSet = _graphAdjList[v];
        
        // Explore unvisited neighbour vertices of current vertex
        // and find the total number edges in commencing from current
        // vertex which lead to vertices with apples
        int nEdgesLeadingToApples = 0;
        for (auto & nv : nvSet) {
            if (!_visited[nv]) {
                // From the neighbor vertex, determine count of unique edges
                // leading to unvisited vertices with apples 
                auto nEdgesLeadingToApplesFromNbr = dfs(nv, hasAppleV);
                // Add such edges to the number of edges leading to apples
                // from current vertex.
                nEdgesLeadingToApples += nEdgesLeadingToApplesFromNbr;
                if (nEdgesLeadingToApplesFromNbr > 0 || hasAppleV[nv]) {
                    // Include edge between current vertex and neighbour
                    // if either the neighbour vertex holds an apple OR
                    // other unvisited vertices with apples can be reached
                    // via the neighbout
                    ++nEdgesLeadingToApples;
                }
            }
        }
        
        return nEdgesLeadingToApples;
    }
    
    int
    minTime(vector<bool> & hasApple) {
        
        // Compute number of unique edges on paths from
        // vertex 0 to vertices with apples
        int minEdges = dfs(0, hasApple);
            
        // Twice the total minimum number of edges from
        // vertex 0 to apple vertices gives the minimum 
        // walk length from vertex 0 to pluck all apples
        return 2 * minEdges;
    }
    
    // Data members
    
    // Hash table/adjacency list table of graph
    unordered_map<int, vector<int> > _graphAdjList;
    // Tracks DFS visit status per graph vertex
    vector<bool> _visited;
};
