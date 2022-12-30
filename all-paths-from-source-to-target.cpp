class Solution {
public:
    vector<vector<int>>
    allPathsSourceTarget(vector<vector<int>>& graph) {
        // Since input graph is a DAG with no self-loops, there is no need for
        // a visited vertex check as there wont be any cycles/loops
        int n = graph.size();
        _dstVertex = n - 1;
        
        // Find all paths from vertex 0 to vertex n - 1 via DFS with backtracking
        vector<int> pathV;
        dfs(graph, 0, pathV);
        
        return _pathsV;
    }
    
private:
    
    void
    dfs(vector<vector<int>>& graph, int currVertex, vector<int>& pathV) {
        // Add the current vertex to be explored to path vector
        pathV.emplace_back(currVertex);
        if (currVertex == _dstVertex) {
            
            // Path found from source to destination; Add it to path list
            _pathsV.emplace_back(pathV);
            
        } else {
        
            // Iterate over all neighbours of current current vertex
            // and do a DFS exploration from the neighbour
            auto & nbrV = graph[currVertex];
            for (auto & nv : nbrV) {
                dfs(graph, nv, pathV);
            }
        }
        
        // Backtrack by removing current vertex from path vector
        // in order to explore other paths
        pathV.pop_back();
    }
    
    // Data members
    vector<vector<int> > _pathsV;
    int _dstVertex;
};
